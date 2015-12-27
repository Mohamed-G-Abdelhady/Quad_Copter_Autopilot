   void derivative_z()
   {
   if(Serial2.available()> 0) 
  { h = Serial2.read();   z = h / 100.0;
   z_deriv_sonar = (z - z_k) / (k*dt);   z_k = z ;
   k = 1;
  }
  else k++;

a = 0.15;                                                           // delay time = dt (1 - a) / a 
v_est = (1 - a)*(v_est_old - z_acc_imu * dt) + a * z_deriv_sonar;  // complementary filter (HPF_velocity from IMU  + LPF_velocity from sonar)
v_est_old = v_est;
  //end of sonar 
  
  }
