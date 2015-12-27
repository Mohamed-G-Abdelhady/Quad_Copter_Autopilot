int hovering = 1400;      // nominal Duty that can hover the quad
int heating  = 1320;      // (heating is the limit between hovering and stand still)
// sample time deifintions
 
float dt = 0.02; // sampling time
//altitude definitions 
unsigned int u = 0.0;
int k = 1;
float z ;
float v_est , v_est_old = 0.0 , z_acc_imu = 0.0 , z_deriv_sonar = 0.0 , z_k = 0.0 , a; 
float error_z , set_z = 0.75 ;     
float u1_z , z_integral = 0.0 , limit_iz = 120 , neg_limit_iz = -60;
float delta_z , u2_z ;  

//proportional definitions
float error_ROLL = 0.0 , u1_ROLL =0.0;
float error_PITCH = 0.0 , u1_PITCH =0.0 ;
float ROLL , PITCH ;
float error_yaw = 0.0 , u1_yaw =0.0;
float yaw ;

//derivaticeAngles and derivativePosition
float  yaw_derivative;
float PITCH_derivative , ROLL_derivative;
float  PITCH_K1 = 0.0 , PITCH_K2 = 0.0 , ROLL_K1 = 0.0 , ROLL_K2 = 0.0 , yaw_K1 = 0.0;
int i= 0 , ir = 0 , ip = 0 ;

//integral derivative
float PITCH_integral = 0.0 , ROLL_integral = 0.0; 
float limit_iPITCH = 0.0 , limit_iROLL = 0.0;
float u2_PITCH = 0.0 , u2_ROLL = 0.0;
float yaw_integral = 0.0 , limit_iyaw , u2_yaw;

float kp,kd,ki;  //gains 


float delta_ROLL = 0 , delta_PITCH = 0 , delta_yaw = 0;   //action

int f1=1;
int  off=1 ;



// MOTOR DEFINATION 

#include <Servo.h> 
Servo myservo1;
Servo myservo2;
Servo myservo3;
Servo myservo4;

float  Duty = 1000.0 ;   


int Duty1 =1000 ;
int Duty2 =1000;
int Duty3 =1000;
int Duty4 =1000;

//END OF THE  MOTOR DEFINATION


//    xbee DEFINATION 

float set_ROLL = 0.0 ,set_yaw = 0.0 , set_PITCH = 0.0 ;  // IN DEGREES
int x = 0 , j1 = 0 , j2 = 0;
float k1 = 120 , k2 = 60 , k3 = 0;


// END OF THE  xbee DEFINATION 


//   IMU definiations 
#include "Wire.h"
#include "I2Cdev.h"

#include "MPU6050_6Axis_MotionApps20.h"
MPU6050 mpu;

bool blinkState = false;
bool dmpReady = false;  // set true if DMP init was successful
uint8_t mpuIntStatus;   // holds actual interrupt status byte from MPU
uint8_t devStatus;      // return status after each device operation (0 = success, !0 = error)
uint16_t packetSize;    // expected DMP packet size (default is 42 bytes)
uint16_t fifoCount;     // count of all bytes currently in FIFO
uint8_t fifoBuffer[64]; // FIFO storage buffer
Quaternion q;           // [w, x, y, z]         quaternion container
VectorInt16 aa;         // [x, y, z]            accel sensor measurements
VectorInt16 aaReal;     // [x, y, z]            gravity-free accel sensor measurements
VectorFloat gravity;    // [x, y, z]            gravity vector
float ypr[3];           // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector
uint8_t teapotPacket[14] = {'$', 0x02, 0,0, 0,0, 0,0, 0,0, 0x00, 0x00, '\r', '\n' };
volatile bool mpuInterrupt = false;     // indicates whether MPU interrupt pin has gone high
void dmpDataReady() { mpuInterrupt = true; }

//  END OF IMU definiations : 





void setup() {

  //  IMU setup 
  Wire.begin();
  TWBR = 24; // 400kHz I2C clock (200kHz if CPU is 8MHz)
  Serial.begin(115200);    
  while (!Serial); // wait for Leonardo enumeration, others continue immediately
  Serial.println(F("Initializing I2C devices..."));
  mpu.initialize();
  Serial.println(F("Testing device connections..."));
  Serial.println(mpu.testConnection() ? F("MPU6050 connection successful") : F("MPU6050 connection failed"));
  Serial.println(F("\nSend any character to begin DMP programming and demo: "));
  while (Serial.available() && Serial.read()); // empty buffer
  while (!Serial.available());                 // wait for data
  while (Serial.available() && Serial.read()); // empty buffer again
  Serial.println(F("Initializing DMP..."));
  devStatus = mpu.dmpInitialize();

  mpu.setXGyroOffset(-9);
  mpu.setYGyroOffset(-5);
  mpu.setZGyroOffset(-24);
 	 	   

 if (devStatus == 0) {
        // turn on the DMP, now that it's ready
        Serial.println(F("Enabling DMP..."));
        mpu.setDMPEnabled(true);
        Serial.println(F("Enabling interrupt detection (Arduino external interrupt 0)..."));
        attachInterrupt(0, dmpDataReady, RISING);
        mpuIntStatus = mpu.getIntStatus();
        Serial.println(F("DMP ready! Waiting for first interrupt..."));
        dmpReady = true;
        packetSize = mpu.dmpGetFIFOPacketSize();
    } else {
        Serial.print(F("DMP Initialization failed (code "));
        Serial.print(devStatus);
        Serial.println(F(")"));
    }

  // END OF THE IMU setup 



  //  MOTOR setup 
  myservo1.attach(8);   //roll
  myservo2.attach(9);   //pitch
  myservo3.attach(10);  
  myservo4.attach(11);
  myservo1.writeMicroseconds(1000);
  myservo2.writeMicroseconds(1000);
  myservo3.writeMicroseconds(1000);
  myservo4.writeMicroseconds(1000);

  // END OF THE MOTOR setup 
  
   //  xbee setup 
  
Serial1.begin(9600);

  //  END OF THE xbee setup 
  
   //sonar setup 
Serial2.begin(9600);    

}


void loop()
{

  // IMU main loop
  if (!dmpReady) return;

  while (!mpuInterrupt && fifoCount < packetSize) { }
  mpuInterrupt = false;
  mpuIntStatus = mpu.getIntStatus();

  fifoCount = mpu.getFIFOCount();
  if ((mpuIntStatus & 0x10) || fifoCount == 1024) 
  {
    mpu.resetFIFO();
    Serial.println(F("FIFO overflow!"));
  } else if (mpuIntStatus & 0x02) 
  { 
    while (fifoCount < packetSize) fifoCount = mpu.getFIFOCount();
    mpu.getFIFOBytes(fifoBuffer, packetSize);
    fifoCount -= packetSize;

    mpu.dmpGetQuaternion(&q, fifoBuffer);
    mpu.dmpGetAccel(&aa, fifoBuffer);
    mpu.dmpGetGravity(&gravity, &q);
    mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);
    mpu.dmpGetLinearAccel(&aaReal, &aa, &gravity);
    PITCH =  ypr[1]  - 5.65*M_PI/180 ;   //    PITCH in radian
    ROLL =   ypr[2]  - 1.9*M_PI/180 ;    //    ROLL in radian
    yaw = ypr[0];
    z_acc_imu = (aaReal.z - 50) / 16384.0 * 9.81 ;  // sensitivity 16384 LSB/g  to cm/sec^2 ---->  (LSB / 16384) * 981 
    
  
      //begin to read angles before control loop so,that control algorithm begin on right initial conditions   
   if(i<1) {PITCH_K1 = PITCH; PITCH_K2 = PITCH; 
            ROLL_K1 = ROLL;   ROLL_K2 = ROLL;}  else i=5; i++;    //estimate initial conditions 
   derivativeAngles();      //run filter of angles and derivatives 
  }
  // END OF THE  IMU main loop 
    
    
      //z and z_derivative
     derivative_z(); 

  

  // determine motors (PWM) Duty1 Duty3 Duty2 Duty4
    if (Serial.available())
  {
    off = Serial.read();
  }
  
    // by serial or xbee  
 
 xbee();

  //=============================================================================
  //===========
  
  if( f1 == '0' | off == '0' ){ 
    Duty = 1000;
    Duty1= 1000;
    Duty3 =1000;
    Duty2= 1000;
    Duty4 =1000;

    Serial.print("zero");
  f1=  '0' ;
  }
  
  //=============================================================================
  if (f1=='1'|off == '1')
  {
if (Duty < heating) // increase from 1000 to heating (heating is the limit between hovering and stand still)
 {      Duty = Duty + 5;
 
         Duty1= Duty;
         Duty3 =Duty;
         Duty2= Duty;
         Duty4 =Duty;
          Serial.print("heating ");
}
 else Serial.print(" done heating ");
f1='1'; 
  }
  //===========
 if ( f1 =='2'|off == '2')  // decrease from heating to 1000 (heating is the limit between hovering and stand still) to zero
 {       
    if(Duty > heating) {Serial.print("\t warning : landing first");}
    else{ 
               if (Duty > 1000)
            {    Duty = Duty-2;
       
                Duty1= Duty;
                Duty3 =Duty;
                Duty2= Duty;
                Duty4 =Duty;
                Serial.print("powering off");
            }
            else Serial.print("done power off "); 
        }   
         
f1 ='2';
}

  //===========
 if (Duty > heating & off != '0') f1 = '4';  //unexpected inputs so,we have to control above hovering limit 
// take off and landing
// from heating to hovering and vice versa
  if(  f1 == '4'|| off == '4'  || off == '5'  ) // 4 for take off ,5 for landing
  {   f1 ='4' ;
    if(Duty < heating){Serial.print("\t warning : heating frist!!");}
    else{
      
    if (off == '4') // tack off from  heating to hovering 
    {
 if (Duty < hovering) {Duty=Duty + 1.5;  Serial.print("takeoff"); }   //.1 is equal to (delta_Duty*.01/required time to take off) 
//else Serial.print("hovering");
    }
    
    
    
    
       if (off == '5') // land but till get to heating (heating is the limit between hovering and stand still)
    { 
 if (Duty > heating) {Duty=Duty - 1.5;  Serial.print("landing"); }  //.1 is equal to (hovering - heating)*.01/required time to take off)       
 else Serial.print("done landing");
    }

 
    
    //keep this sequence:    Duty = ;  set_PITCH ,set_ROLL  attitude_control();  allocation();    
   

         //determine set_PITCH ,set_ROLL and Duty
    z_control();    
    attitude_control();                                                   //determine (delta_PITCH , delta_ROLL)
    allocation();                                                         // allocate (delta_PITCH , delta_ROLL , delta_z)
    
   




    }
   
  }  

  // ========================= end of determine motors (PWM) Duty1 Duty3 Duty2 Duty4  =============<<<<<<<<<<<<

Serial.print('\t');          Serial.print(180/M_PI*PITCH); 
Serial.print('\t');          Serial.print(180/M_PI*ROLL);                             
Serial.print('\t');          Serial.print(180/M_PI*yaw);
Serial.print('\t');          Serial.print(z);
Serial.print('\n'); 


  // ================================= MOTOR  main loop =================>>>>>
  myservo1.writeMicroseconds(Duty1);
  myservo2.writeMicroseconds(Duty2);
  myservo3.writeMicroseconds(Duty3);
  myservo4.writeMicroseconds(Duty4);
  // ================================= END OF THR MOTOR  main loop =================<<<<<<<<<<

}
