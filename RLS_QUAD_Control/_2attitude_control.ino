
 void attitude_control(){ 

    

 
//ROLL control 
   error_ROLL_k1 = error_ROLL;
    error_ROLL = (set_ROLL *M_PI/180  - ROLL );    //error calcualation
/*
// if(t < 1500)
//{ 
  a1 = -2; a2 = 1 ; b0 = 0.0001510047; b1 = 0.0001510047;
//t=t+1;
//}
/*
if(b0 <  0.0001510047) b0 =  0.0001510047;
if(b1 <  0.0001510047) b1 =  0.0001510047;

  Poles[0] = -(exp(dt*pole_1) + exp(dt*pole_2) + exp(dt*pole_3)) - a1;
  Poles[1] =  exp(dt*(pole_1 + pole_2)) + exp(dt*(pole_3 + pole_2)) + exp(dt*(pole_1 + pole_3)) - a2;
  Poles[2] =  -1*exp(dt*(pole_1 + pole_2 + pole_3));
  
  A[0][0] =  1; A[0][1] = b0; A[0][2] = 0;
  A[1][0] = a1; A[1][1] = b1; A[1][2] = b0;
  A[2][0] = a2; A[2][1] =  0; A[2][2] = b1;
  
Matrix.Invert((float*)A, 3);
Matrix.Multiply((float*)A, (float*)Poles, 3, 3, 1, (float*)C); 
u1_ROLL_k1 = u1_ROLL;
u1_ROLL = -1*C[0]*u1_ROLL_k1 + C[1] * error_ROLL + C[2] * error_ROLL_k1;
*/

 kp = 180;
 kd = 70;
    int  p = 15,d = 10;    
  // use different gains along error spectrum
         if(abs(error_ROLL)<15*M_PI/180)     {kp = kp       ; kd = kd      ;}
    else if(abs(error_ROLL)<25*M_PI/180)     {kp = kp - p   ; kd = kd - d  ;}
    else if(abs(error_ROLL)<55*M_PI/180)     {kp = kp - 2*p ; kd = kd - 2*d;}
    else                                      {kp = kp - 3*p ; kd = kd - 3*d;}
    u1_ROLL = kp * error_ROLL - kd * ROLL_derivative ;            //p action


       ki = 50;                                      //integral ROLL
   ROLL_integral = ROLL_integral + (error_ROLL * dt) ;            //numerical integration
       
    limit_iROLL = 100;                                               //saturation 
    if      (abs(ROLL_integral)*ki <= limit_iROLL)      { u2_ROLL = ROLL_integral*ki ;}        
    else if (    ROLL_integral *ki > limit_iROLL )      {u2_ROLL = limit_iROLL ;   ROLL_integral=limit_iROLL/ki;}                                                                             
    else                                                  {u2_ROLL = - limit_iROLL ; ROLL_integral= - limit_iROLL/ki;} 
     //end of integral ROLL

    
    delta_ROLL =  u1_ROLL  + u2_ROLL ;  // 5(Paction + Iaction) on error  +  velocity feedback(deriviative on system state - angle)
    
 //end of ROLL control 
 
 
 
 }
 
/*
*/
