
 void attitude_control(){ 

    
 kp = 180;
 kd = 70;
 ki = 50; 
                                      
//PITCH control 
    error_PITCH = (set_PITCH *M_PI/180  - PITCH );     //error calcualation
   int p = 15,d = 10;    
  // use different gains along error spectrum
         if(abs(error_PITCH)<15*M_PI/180)     {kp = kp       ; kd = kd      ;}
    else if(abs(error_PITCH)<25*M_PI/180)     {kp = kp - p   ; kd = kd - d  ;}
    else if(abs(error_PITCH)<55*M_PI/180)     {kp = kp - 2*p ; kd = kd - 2*d;}
    else                                      {kp = kp - 3*p ; kd = kd - 3*d;}
   
    u1_PITCH = kp * error_PITCH ;            //p action
                                             //integral PITCH
   PITCH_integral = PITCH_integral + (error_PITCH * dt) ;            //numerical integration
       
    limit_iPITCH = 100 ;                                               //saturation 
    if      (abs(PITCH_integral)*ki <= limit_iPITCH)      { u2_PITCH = PITCH_integral*ki ;}        
    else if (    PITCH_integral *ki > limit_iPITCH )      {u2_PITCH = limit_iPITCH ;   PITCH_integral=limit_iPITCH/ki;}                                                                             
    else                                                  {u2_PITCH = - limit_iPITCH ; PITCH_integral= - limit_iPITCH/ki;} 
     //end of integral PITCH

  
    delta_PITCH =  u1_PITCH  + u2_PITCH - kd* PITCH_derivative ;  // (Paction + Iaction) on error  +  velocity feedback(deriviative on system state - angle)
    
 //end of PITCH control 
 

//ROLL control 
    error_ROLL = (set_ROLL *M_PI/180  - ROLL );    //error calcualation
     p = 15,d = 10;    
  // use different gains along error spectrum
         if(abs(error_ROLL)<15*M_PI/180)     {kp = kp       ; kd = kd      ;}
    else if(abs(error_ROLL)<25*M_PI/180)     {kp = kp - p   ; kd = kd - d  ;}
    else if(abs(error_ROLL)<55*M_PI/180)     {kp = kp - 2*p ; kd = kd - 2*d;}
    else                                      {kp = kp - 3*p ; kd = kd - 3*d;}
    

    u1_ROLL = kp * error_ROLL ;            //p action
                                           //integral ROLL
   ROLL_integral = ROLL_integral + (error_ROLL * dt) ;            //numerical integration
       
    limit_iROLL = 100;                                               //saturation 
    if      (abs(ROLL_integral)*ki <= limit_iROLL)      { u2_ROLL = ROLL_integral*ki ;}        
    else if (    ROLL_integral *ki > limit_iROLL )      {u2_ROLL = limit_iROLL ;   ROLL_integral=limit_iROLL/ki;}                                                                             
    else                                                  {u2_ROLL = - limit_iROLL ; ROLL_integral= - limit_iROLL/ki;} 
     //end of integral ROLL

    
    delta_ROLL =  u1_ROLL  + u2_ROLL - kd* ROLL_derivative ;  // (Paction + Iaction) on error  +  velocity feedback(deriviative on system state - angle)
    
 //end of ROLL control 
 
 
//yaw control 
    error_yaw = (set_yaw *M_PI/180 - yaw );    //error calcualation
    // if(error_yaw >  180 *M_PI/180) error_yaw = error_yaw - 360*M_PI/180;  if(error_yaw < -180 *M_PI/180) error_yaw = error_yaw + 360*M_PI/180;
     kp =  400; //180
     kd =  200; //140
     ki = 0;

    u1_yaw = kp * error_yaw ;            //p action
                                           //integral yaw
   yaw_integral = yaw_integral + (error_yaw * dt) ;            //numerical integration
//  if(abs(error_yaw)>30*M_PI/180)  {ki = 0; yaw_integral = 0;}   //limit integral action on small range
       
    limit_iyaw = 60;                                               //saturation 
    if      (abs(yaw_integral)*ki <= limit_iyaw)      {u2_yaw = yaw_integral*ki ;}        
    else if (    yaw_integral *ki > limit_iyaw )      {u2_yaw = limit_iyaw ;   yaw_integral=limit_iyaw/ki;}                                                                             
    else                                              {u2_yaw = - limit_iyaw ; yaw_integral= - limit_iyaw/ki;} 
     //end of integral yaw

    
    delta_yaw =  u1_yaw  + u2_yaw - kd* yaw_derivative ;  // (Paction + Iaction) on error  +  velocity feedback(deriviative on system state - angle)
    if(delta_yaw > 200)  delta_yaw = 200;
    if(delta_yaw < -200) delta_yaw = -200;
    
 //end of yaw control 
                           
                           
                           

  

 }
 

