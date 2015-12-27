 //filter angles(pitch,roll) and its rates 
void derivativeAngles()
{
  
//pitch
if(abs(PITCH - PITCH_K1) < 0.14 | ip >= 4 )      //0.07 = 4deg is the maximum change in the angle within sample time
{
PITCH_derivative = (PITCH - PITCH_K1) / dt; 
ip = 0;
}
else if(ip < 4 )                   //angle change is impossible to be greater than 4 deg.
{                       //so,we cancel current angle PITCH and use two previous angles PITCH_K1,PITCH_K2 and derivative to estimate current angle PITCH
PITCH_derivative = (PITCH_K1 - PITCH_K2) / dt;    //derivative of previous sample time
PITCH = 2 * PITCH_K1 - PITCH_K2;          // this expression is equal to : PITCH =  PITCH_K1 + PITCH_derivative * dt;
ip += 1;
Serial.println("filterP");
}
PITCH_K2 = PITCH_K1;
PITCH_K1 = PITCH;

 
//roll 
if(abs(ROLL - ROLL_K1) < 0.14 | ir >= 4)      //0.07 = 4deg is the maximum change in the angle within sample time
{
ROLL_derivative = (ROLL - ROLL_K1) / dt; 
ir = 0;
}
else if(ir < 4)                     //angle change is impossible to be greater than 5 deg.
{                       //so,we cancel current angle ROLL and use two previous angles ROLL_K1,ROLL_K2 and derivative to estimate current angle ROLL
ROLL_derivative = (ROLL_K1 - ROLL_K2) / dt;    //derivative of previous sample time
ROLL = 2 * ROLL_K1 - ROLL_K2;          // this expression is equal to : ROLL =  ROLL_K1 + ROLL_derivative * dt;
ir += 1;
Serial.println("filterR");
}
ROLL_K2 = ROLL_K1;
ROLL_K1 = ROLL;






//yaw 
if(abs(yaw) > 90*M_PI / 180) 
{
 if(yaw_K1 > 0 && yaw < 0 )  yaw_derivative = (yaw - yaw_K1 + 2*M_PI) / dt;
 else if(yaw_K1 < 0 && yaw > 0 )  yaw_derivative = (yaw - yaw_K1 - 2*M_PI) / dt;
 else yaw_derivative = (yaw - yaw_K1) / dt;
 
}
else  yaw_derivative = (yaw - yaw_K1) / dt; 
yaw_K1 = yaw;

}


