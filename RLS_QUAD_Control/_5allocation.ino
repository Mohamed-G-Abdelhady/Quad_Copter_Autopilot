void allocation()
{
// control allocation

   //set Dury nominal before calling allocation() function in main loop

    //  ROLL allocation
    Duty1 =  Duty + delta_ROLL/2 +80;
    Duty3 =  Duty - delta_ROLL/2 ;
    
    
    //constrain

    if (  Duty1 <1100   ) Duty1=1100;
    if( Duty1 > 1700  )Duty1 = 1700;

    if ( Duty3 <1100  ) Duty3=1100; 
    if( Duty3 > 1700 )Duty3 = 1700;

// end of control allocation 

}
