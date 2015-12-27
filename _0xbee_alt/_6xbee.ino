void xbee()

{

    
       
  //  off = '0';   EMERGENCY SHUT DOWN
  // off = '1';    HEATING
  // off = '2';    POWER OFF
  // off = '4';    TAKE OFF
  // off = '5';    LANDING
      
 
    if (Serial1.available())
  {
    off = Serial1.read();
  }

float set = 5;
  //drive roll pitch
  if(off == 'a') {set_PITCH = 0; off = 'H';}
  else
  {
         if(off == 'q') {set_PITCH =  set; j1 = 0; off = 'H';}
    else if(off == 'z') {set_PITCH = -set; j1 = 0; off = 'H';}
    else if(j1 == 30)    {set_PITCH = 0; j1 = 29;  }
    j1++;
  }
  
  
     if(off == 's') {set_ROLL = 0; off = 'H';}
  else
  {
         if(off == 'w') {set_ROLL =  set; j2 = 0; off = 'H';}
    else if(off == 'x') {set_ROLL = -set; j2 = 0; off = 'H';}
    else if(j2 == 30)    {set_ROLL = 0;  j2 = 29; } 
    j2++;
  } 
 
 if(off == 'e' )  {set_yaw = set_yaw + 5;  off = 'H';} if(off == 'c' )  {set_yaw = set_yaw - 5;  off = 'H';}  if(off == 'd' )  {set_yaw =0;  off = 'H';}  //drice yaw 
 if(set_yaw >= 180) set_yaw =180; if(set_yaw < -180) set_yaw = -180; 
  
 if(off == 'r' )  {set_z = set_z + 0.1;  off = 'H';} if(off == 'v' )  {set_z = set_z - 0.1;  off = 'H';} if(off == 'f' )  {set_z = 1;  off = 'H';}   //drice z
 if(set_z >= 2) set_z =2; if(set_z < 0.5) set_z = 0.5; 
  
 if(off == '9' )  {Duty = Duty + 2;  off = 'H';} if(off == '3' )  {Duty = Duty - 2;  off = 'H';}   // nominal control
 if(Duty > hovering + 150) Duty = hovering + 150; if(Duty < hovering - 200) Duty = hovering - 200; 
 
 if(x > 5)
 {
   Serial1.print(' ');   Serial1.print('P'); Serial1.print(' ');   Serial1.print(set_PITCH);
   Serial1.print(' ');   Serial1.print('R'); Serial1.print(' ');   Serial1.print(set_ROLL);
   Serial1.print(' ');   Serial1.print('Y'); Serial1.print(' ');   Serial1.print(set_yaw);
   Serial1.print(' ');   Serial1.print('Z'); Serial1.print(' ');   Serial1.print(set_z); 
   Serial1.print(' ');   Serial1.print('D'); Serial1.print(' ');   Serial1.print(Duty); 
   Serial1.print(' ');   Serial1.print('Y'); Serial1.print(' ');   Serial1.print(yaw*180 / M_PI); 

   Serial1.println();  
   x = 0; 
 }
 else  x++;
 
      
}
