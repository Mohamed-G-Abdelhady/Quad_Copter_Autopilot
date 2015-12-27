void analysis(String data)
{
        int c1 = data.indexOf(',');
        int c2 = data.indexOf(',', c1+1);
        int c3 = data.indexOf(',', c2+1);
        int c4 = data.indexOf(',', c3+1);
        int c5 = data.indexOf(',', c4+1);
        int c6 = data.indexOf(',', c5+1);
        int c7 = data.indexOf(',', c6+1);
        int c8 = data.indexOf(',', c7+1);
        int c9 = data.indexOf(',', c8+1);
        int c10 = data.indexOf(',', c9+1);
        int c11 = data.indexOf(',', c10+1);
        int c12 = data.indexOf(',', c11+1);
        int c13 = data.indexOf(',', c12+1);
        int c14 = data.indexOf(',', 13+1);
        int c15 = data.indexOf(',', c14+1);
        int c16 = data.indexOf(',', c15+1);
       
        d1 = data.substring(0,c1+1);
        d2 = data.substring(c1+1,c2+1);
        d3 = data.substring(c2+1,c3+1);
        d4 = data.substring(c3+1,c4+1);
        d5 = data.substring(c4+1,c5+1);
        d6 = data.substring(c5+1,c6+1);
        d7 = data.substring(c6+1,c7+1);
        d8 = data.substring(c7+1,c8+1);
        d9 = data.substring(c8+1,c9+1);
        d10 = data.substring(c9+1,c10+1);
        d11 = data.substring(c10+1,c11+1);
        d12 = data.substring(c11+1,c12+1);
        d13 = data.substring(c12+1,c13+1);
        d14 = data.substring(c13+1,c14+1);
        d15 = data.substring(c14+1,c15+1);
        d16 = data.substring(c15+1,c16+1);

  
        char value1[d1.length()];
        d1.toCharArray(value1, d1.length());
  
        char value2[d2.length()];
        d2.toCharArray(value2, d2.length());   
          
        char value3[d3.length()];
        d3.toCharArray(value3, d3.length());
  
        char value4[d4.length()];
        d4.toCharArray(value4, d4.length());
            
        char value5[d5.length()];
        d5.toCharArray(value5, d5.length());
  
        char value6[d6.length()];
        d6.toCharArray(value6, d6.length());   
          
        char value7[d7.length()];
        d7.toCharArray(value7, d7.length());
        
         char value8[d8.length()];
        d8.toCharArray(value8, d8.length());
  
        char value9[d9.length()];
        d9.toCharArray(value9, d9.length());   
          
        char value10[d10.length()];
        d10.toCharArray(value10, d10.length());
  
        char value11[d11.length()];
        d11.toCharArray(value11, d11.length());
            
        char value12[d12.length()];
        d12.toCharArray(value12, d12.length());
  
        char value13[d13.length()];
        d13.toCharArray(value13, d13.length());   
          
        char value14[d14.length()];
        d14.toCharArray(value14, d14.length());
        
        char value15[d15.length()];
        d15.toCharArray(value15, d15.length());
  
        char value16[d16.length()];
        d16.toCharArray(value16, d16.length());   

 
  
         x1 = atof(value1);  
         y1 = atof(value2); 
         axial = atof(value3);  
         ver = atof(value4); 
         b1 = atof(value5);  
         b2 = atof(value6);
         b3 = atof(value7); 
         b4 = atof(value8);  
         b5 = atof(value9);
         b6 = atof(value10); 
         b7 = atof(value11);  
         b8 = atof(value12);
         b9 = atof(value13); 
         b10 = atof(value14);  
         b11 = atof(value15);
         b12 = atof(value16);
       
         
}
