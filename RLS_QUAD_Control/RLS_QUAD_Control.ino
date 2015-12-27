// the transfer function to identify is:
//  a1 s + a2 
// ----------------
// s^2 + b1 s + b2

// in the discrete form: z transform with zero order hold approximation:
// y         b0 z^-1 + b1 z^-2
// -- = ------------------------
// u     1 + a1 z^-1 + a2 z^-2
//
// then finally y = b0 u(z^-1) + b1 u(z^-2) - a1 y(z^-1) - a2 y(z^-2)
//              y = b0 phi[0]  + b1 phi[1]  + a1 phi[2]  + a2 phi[3]


//Definitions for RLS algorithm

#include <MatrixMath.h>

const int n = 4 ; // no estimated parameters 


float Theta[n]; // parameters vectore
float Theta_1[n];
float b0 , b1 , a1 , a2;

float P[n][n];  // to be initalized as a Diagonal Matrix
float P_1[n][n];
float dia = 1e4;

float K[n]; // gains vector

float Phi[n]; // system features (variables) vector


float Y;
float Y_1 = 0, Y_2 = 0; //system real output
float U , U_1 = 0 , U_2 = 0; // system Input
float Yn;           //system estimated output = (phi)T * Theta
 int I = 0, J = 0;
 
 

int hovering = 1250;      // nominal Duty that can hover the quad
int heating  = 1200;      // (heating is the limit between hovering and stand still)
// sample time deifintions
 
float dt = 0.02; // sampling time
float t_old = 0.0;
unsigned int t = 0;
//proportional definitions
float error_ROLL = 0.0 , error_ROLL_k1 = 0.0, u1_ROLL =0.0 , u1_ROLL_k1 =0.0;
float ROLL; //radian 
float set_ROLL = 0.0 ; //degree

//derivaticeAngles and derivativePosition
float ROLL_derivative;
float  ROLL_K1 = 0.0 ;
float A[3][3];
float C[3];
float Poles[3];
float pole_1 =  -2.593 , pole_2 = -17 , pole_3 = -30;

//integral derivative
float ROLL_integral = 0.0; 
float limit_iROLL = 0.0;
float u2_ROLL = 0.0;

float kp,kd,ki;  //gains 


float delta_ROLL = 0 ; //action

int f1=1;
int  off=1 ;



// MOTOR DEFINATION 

#include <Servo.h> 
Servo myservo1;
Servo myservo3;

float  Duty = 1000.0 ;   


int Duty1 =1000 ;
int Duty3 =1000;


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
  
    //initialize Theta_1 and P_1
Theta_1[0] = 0.0001510047; 
Theta_1[1] = -0.0001510047; 
Theta_1[2] = -2; 
Theta_1[3] = 1; 

for(I=0 ; I<n ; I++)
{
for(J=0 ; J<n ; J++)
{ if(I == J) P_1[I][J] = dia; else  P_1[I][J] = 0; }
}

pinMode(A14 , INPUT);

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
  myservo1.attach(9);   //roll
  myservo3.attach(10);  

  myservo1.writeMicroseconds(1000);
  myservo3.writeMicroseconds(1000);

  // END OF THE MOTOR setup 
  
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
    ROLL =   ypr[2]  - 1.9*M_PI/180 ;    //    ROLL in radian
    
  ROLL_derivative = (ROLL - ROLL_K1) / dt; 
  ROLL_K1 = ROLL;
   
  }
  // END OF THE  IMU main loop 

  

  // determine motors (PWM) Duty1 Duty3 Duty2 Duty4
    if (Serial.available())
  {
    off = Serial.read();
  }

set_ROLL = map(analogRead(A14) , 0 , 1023 , -30 , 30);
if(set_ROLL > 20) set_ROLL = 30;
else if(set_ROLL < -20) set_ROLL = -30;
else set_ROLL = 0;

  //=============================================================================
  //===========
  
  if( f1 == '0' | off == '0' ){ 
    Duty = 1000;
    Duty1= 1000;
    Duty3 =1000;

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
                                                                  // take delta_ROLL and ROLL to get THeta and Yn
    attitude_control();                                                   //determine (delta_PITCH , delta_ROLL)
    allocation();                                                         // allocate (delta_PITCH , delta_ROLL , delta_z)
   RLS();  
   





    }
   
  }  

  // ========================= end of determine motors (PWM) Duty1 Duty3 Duty2 Duty4  =============<<<<<<<<<<<<

Serial.print(set_ROLL); 
Serial.print('\t');          Serial.print(ROLL*180/M_PI); 
Serial.print('\t');
Serial.print('\t');          Serial.print(Yn*180/M_PI);
Serial.print('\t'); 
Serial.print('\t');          Serial.print(delta_ROLL);
Serial.print('\t');
Serial.print('\t');          Serial.print(b0,10);
Serial.print('\t');          Serial.print(b1,10);
Serial.print('\t');          Serial.print(a1,10);
Serial.print('\t');          Serial.print(a2,10);
Serial.print('\n'); 

  // ================================= MOTOR  main loop =================>>>>>
 myservo1.writeMicroseconds(Duty1);
 myservo3.writeMicroseconds(Duty3);
  // ================================= END OF THR MOTOR  main loop =================<<<<<<<<<<

}
