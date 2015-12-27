void allocation()
{
// control allocation

   //set Dury nominal before calling allocation() function in main loop

    // PITCH allocation 
    Duty2 =  Duty - delta_PITCH/2 + delta_yaw/4 + delta_z/4;
    Duty4 =  Duty + delta_PITCH/2 + delta_yaw/4 + delta_z/4 ;
    //  ROLL allocation
    Duty1 =  Duty + delta_ROLL/2 - delta_yaw/4 + delta_z/4;
    Duty3 =  Duty - delta_ROLL/2 - delta_yaw/4 + delta_z/4;
    
    
    //constrain
    if (Duty2 <1200   ) Duty2=1200 ;
    if( Duty2 > 1900  ) Duty2 = 1900;

    if (  Duty4 <1200   ) Duty4=1200;
    if(  Duty4 > 1900  ) Duty4 = 1900;

    if (  Duty1 <1200   ) Duty1=1200;
    if( Duty1 > 1900  )Duty1 = 1900;

    if ( Duty3 <1200  ) Duty3=1200; 
    if( Duty3 > 1900 )Duty3 = 1900;

// end of control allocation 

}
