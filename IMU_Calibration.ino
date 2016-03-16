% calculate the Accel and Gyro of the IMU
% hold the IMU still in a horizontal attitude till the offsets converge to contsant values Then use them to 
% update the offsets in your code
%    obj.setXAccelOffset(ax_offset);
%    obj.setYAccelOffset(ay_offset);
%    obj.setZAccelOffset(az_offset);
%    obj.setXGyroOffset(gx_offset);
%    obj.setYGyroOffset(gy_offset);
%    obj.setZGyroOffset(gz_offset);

#include "I2Cdev.h"
#include "MPU6050.h"
#include "Wire.h"

MPU6050 accelgyro;

int16_t ax, ay, az;
int16_t gx, gy, gz;
float accelx = 0 , accely = 0 , accelz = 0 , gyrox = 0 , gyroy = 0 , gyroz = 0;
float Iax = 0 , Iay = 0 , Iaz = 0 , Igx = 0 ,Igy = 0 , Igz = 0;
float accelx_old;
void setup() {
    
    Wire.begin();
    Serial.begin(115200);
    Serial.println("Initializing I2C devices...");
    accelgyro.initialize();
    Serial.println("Testing device connections...");
    Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");

    accelgyro.setXAccelOffset(0);
    accelgyro.setYAccelOffset(0);
    accelgyro.setZAccelOffset(0);
    accelgyro.setXGyroOffset(0);
    accelgyro.setYGyroOffset(0);
    accelgyro.setZGyroOffset(0);

}

void loop() {

    accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
accelx = 0.98*accelx + 0.02*ax;   
accely = 0.98*accely + 0.02*ay;
accelz = 0.98*accelz + 0.02*az;
gyrox =  0.98*gyrox + 0.02*gx;
gyroy =  0.98*gyroy + 0.02*gy;
gyroz =  0.98*gyroz + 0.02*gz;


Iax = Iax - accelx*0.01;
Iay = Iay - accely*0.01;
Iaz = Iaz + (16384-accelz)*0.01;
Igx = Igx - gyrox*0.01;
Igy = Igy - gyroy*0.01;
Igz = Igz - gyroz*0.01;



float  ax_offset=-accelx +  Iax ;
float  ay_offset=-accely +  Iay ;
float  az_offset=(16384-accelz) + Iaz;

float  gx_offset=-gyrox/4 + Igx;
float  gy_offset=-gyroy/4 + Igy;
float  gz_offset=-gyroz/4 + Igz;

accelx_old = accelx;
        Serial.print("offsets :\t");
        Serial.print(ax_offset); Serial.print("\t");
        Serial.print(ay_offset); Serial.print("\t");
        Serial.print(az_offset); Serial.print("\t");
        Serial.print(gx_offset); Serial.print("\t");
        Serial.print(gy_offset); Serial.print("\t");
        Serial.print(gz_offset);  Serial.print("\t");
        
        
    accelgyro.setXAccelOffset(ax_offset);
    accelgyro.setYAccelOffset(ay_offset);
    accelgyro.setZAccelOffset(az_offset);
    accelgyro.setXGyroOffset(gx_offset);
    accelgyro.setYGyroOffset(gy_offset);
    accelgyro.setZGyroOffset(gz_offset);
        
                Serial.print("a/g:\t");
        Serial.print(ax); Serial.print("\t");
        Serial.print(ay); Serial.print("\t");
        Serial.print(az); Serial.print("\t");
        Serial.print(gx); Serial.print("\t");
        Serial.print(gy); Serial.print("\t");
        Serial.println(gz);
   
}
