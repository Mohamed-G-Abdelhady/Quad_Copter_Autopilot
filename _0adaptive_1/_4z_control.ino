void z_control()
{
kp = 160;   // 160
kd = 60;  // 80
ki = 0;
//error calcualation   

error_z = (set_z   - z );     
//p action
u1_z = kp * error_z ;            
//integral z
   z_integral = z_integral + (error_z * dt) ;            //numerical integration  
    limit_iz = 120 ;                                               //saturation.
    neg_limit_iz = -120;
    if      (z_integral*ki <= limit_iz && z_integral*ki >= neg_limit_iz)     {u2_z = z_integral*ki ;}        
    else if ( z_integral*ki > limit_iz )                                     {u2_z = limit_iz ;   z_integral=limit_iz/ki;}                                                                             
    else                                                                     {u2_z = neg_limit_iz ; z_integral= neg_limit_iz/ki;} 
//end of integral z
     
  delta_z =  u1_z  + u2_z - kd* v_est ;  // (Paction + Iaction) on error  +  velocity feedback(deriviative on system state - z)
  if(delta_z < -160) delta_z = -160;
  if(delta_z >  160) delta_z = 160;
 //end of z control 
 

}


