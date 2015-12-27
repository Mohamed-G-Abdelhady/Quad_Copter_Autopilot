void RLS()
{


  //assign Y and Phi;
Y_2 = Y_1 ;
Y_1 = Y;

U_2 = U_1;
U_1 = U;
  
Phi[0] = U_1; Phi[1] = U_2; Phi[2] = -1*Y_1; Phi[3] = -1*Y_2; 
//take sensor reading and output measure

  U = delta_ROLL;
  Y = ROLL;
  
//Computations

float Operation_1[n];
Matrix.Multiply((float*) Phi, (float*) P_1,  1,  n,  n, (float*) Operation_1);
float Operation_2;
Matrix.Multiply((float*) Operation_1, (float*) Phi,  1,  n,  1, (float*) &Operation_2);
float sc = 1/(1 + Operation_2);
Matrix.Multiply((float*) P_1, (float*) Phi,  n,  n,  1, (float*) K);
Matrix.Scale((float*) K,  n,  1, sc);  // here we got gain vector K

float Operation_3[n][n];
Matrix.Multiply((float*) K, (float*) Phi,  n,  1,  n, (float*) Operation_3);
float Operation_4[n][n];
Matrix.Multiply((float*) Operation_3, (float*) P_1 ,  n,  n,  n, (float*) Operation_4);
Matrix.Subtract((float*) P_1, (float*) Operation_4,  n,  n, (float*) P);  // here we got Matrix P

Matrix.Multiply((float*) Phi, (float*) Theta_1 ,  1,  n,  1, (float*) &Yn);
Matrix.Scale((float*) K,  n,  1,(Y-Yn)); 
Matrix.Add((float*) Theta_1 , (float*) K , n , 1 , (float*) Theta); //here we got Parameters vector Theta

// update Theta_1 and P_1
Matrix.Copy((float*)Theta, n, 1, (float*)Theta_1);
Matrix.Copy((float*)P, n, n, (float*)P_1);

b0 = abs(Theta[0]);
b1 = abs(Theta[1]);
a1 = Theta[2];
a2 = Theta[3];

}
