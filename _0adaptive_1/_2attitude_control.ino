
 void attitude_control(){ 

//adaption()
    error_PITCH = (set_PITCH *M_PI/180  - PITCH );     //error calcualation
    eP_k0 = error_PITCH;

B_P = 0.0000262; 

r1_P = -0.2921;
s0_P = 0.0821/B_P;
s1_P = -0.0788/B_P;
uP_k0 = -r1_P * uP_k1 + s0_P*eP_k0 + s1_P*eP_k1;

eP_k1 = eP_k0;
uP_k1 = uP_k0;
// end of adaption

ki = 50;                                      //integral PITCH
   PITCH_integral = PITCH_integral + (error_PITCH * dt) ;            //numerical integration
       
    limit_iPITCH = 100 ;                                               //saturation 
    if      (abs(PITCH_integral)*ki <= limit_iPITCH)      { u2_PITCH = PITCH_integral*ki ;}        
    else if (    PITCH_integral *ki > limit_iPITCH )      {u2_PITCH = limit_iPITCH ;   PITCH_integral=limit_iPITCH/ki;}                                                                             
    else                                                  {u2_PITCH = - limit_iPITCH ; PITCH_integral= - limit_iPITCH/ki;} 
     //end of integral PITCH

  
    delta_PITCH = 0.58*uP_k0 + u2_PITCH ;  // (Paction + Iaction) on error  +  velocity feedback(deriviative on system state - angle)
    
 //end of PITCH control 
 

//ROLL control 

//adaption
    error_ROLL = (set_ROLL *M_PI/180  - ROLL );     //error calcualation
    eR_k0 = error_ROLL;

B_R = 0.0000262; 

r1_R = -0.2921;
s0_R = 0.0821/B_R;
s1_R = -0.0788/B_R;
uR_k0 = -r1_R * uR_k1 + s0_R*eR_k0 + s1_R*eR_k1;

eR_k1 = eR_k0;
uR_k1 = uR_k0;
// end of adaption

ki = 50;                                      //integral ROLL
   ROLL_integral = ROLL_integral + (error_ROLL * dt) ;            //numerical integration
       
    limit_iROLL = 100 ;                                               //saturation 
    if      (abs(ROLL_integral)*ki <= limit_iROLL)      { u2_ROLL = ROLL_integral*ki ;}        
    else if (    ROLL_integral *ki > limit_iROLL )      {u2_ROLL = limit_iROLL ;   ROLL_integral=limit_iROLL/ki;}                                                                             
    else                                                  {u2_ROLL = - limit_iROLL ; ROLL_integral= - limit_iROLL/ki;} 
     //end of integral ROLL

  
    delta_ROLL = 0.58*uR_k0 + u2_ROLL ;  // (Paction + Iaction) on error  +  velocity feedback(deriviative on system state - angle)
    
 //end of ROLL control 
 
 
 
 //yaw control
//adaption()
    error_yaw = (set_yaw *M_PI/180  - yaw );     //error calcualation
 //   if(error_yaw >  180 *M_PI/180) error_yaw = error_yaw - 360*M_PI/180;  if(error_yaw < -180 *M_PI/180) error_yaw = error_yaw + 360*M_PI/180;
    eY_k0 = error_yaw;

B_Y = 0.0000009; 

r1_Y = -0.2921;
s0_Y = 0.0821/B_Y;
s1_Y = -0.0788/B_Y;
uY_k0 = -r1_Y * uY_k1 + s0_Y*eY_k0 + s1_Y*eY_k1;

eY_k1 = eY_k0;
uY_k1 = uY_k0;
// end of adaption


  
    delta_yaw = 0.58*uY_k0  ;  // (Paction + Iaction) on error  +  velocity feedback(deriviative on system state - angle)
    if(delta_yaw > 120)
 //end of yaw control 
                           
                           

  

 }
 

