void xbee()

{
    
       
  //  off = '0';   EMERGENCY SHUT DOWN
  // off = '1';    HEATING
  // off = '2';    POWER OFF
  // off = '4';    TAKE OFF
  // off = '5';    LANDING
      
for(unsigned long start = millis() ; millis() - start <= 3 ;) 
{
if (Serial1.available()>0)
    {
     int inChar = Serial1.read();
     data += (char)inChar; 
       
      if (inChar == '#') 
       {
         analysis(data);
         data = "";
         
         float U = 2.0 , L = 0.5;
        set_ROLL  = map(x1 , -255 , 255 , -10 , 10);           if(abs(set_ROLL) <= 2 )   set_ROLL = 0;  if(set_ROLL < -10) set_ROLL = -10;   if(set_ROLL > 10) set_ROLL = 10;
        set_PITCH = map((y1 + 1.989) , -255 , 255 , 10 , -10); if(abs(set_PITCH) <= 2 ) set_PITCH = 0; if(set_PITCH < -10) set_PITCH = -10; if(set_PITCH > 10) set_PITCH = 10;
        float yyaw =  map((axial + 1.989) , -255 , 255 , -50 , 50  ) ; 
        set_yaw = yyaw + yaw*180/M_PI; if(abs( yyaw) <= 3) set_yaw = 0; 
        set_z = (-ver + 255.0) * (U - L) / 510.0 + L ;          if(set_z < 0.5) set_z = 0.5; if(set_z > 2) set_z = 2; 
        if(b7 == 1)  off = '0';
        if(b5 == 1 ) off = '1';
        if(b6 == 1 ) off = '2';
        if(b3 == 1 ) off = '4';
        if(b4 == 1 ) off = '5';
       
        if(b1 == 1) Duty = Duty + 1;
        if(b2 == 1) Duty = Duty - 1;
       }}
}

/* if(x > 50)
 {
   Serial1.print(' ');   Serial1.print('P'); Serial1.print(' ');   Serial1.print(set_PITCH);
   Serial1.print(' ');   Serial1.print('R'); Serial1.print(' ');   Serial1.print(set_ROLL);
   Serial1.print(' ');   Serial1.print('Y'); Serial1.print(' ');   Serial1.print(set_yaw);
   Serial1.print(' ');   Serial1.print('Z'); Serial1.print(' ');   Serial1.print(set_z); 
   Serial1.print(' ');   Serial1.print('D'); Serial1.print(' ');   Serial1.print(Duty); 
   Serial1.println();  
   x = 0; 
 }
 else  x++;
 */
}


/*
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



 */
 
      

