close all
clear all
clc
load('uy.mat')

%%definitions
% u is the input vector
% y is the output vector
% the transfer function to identify is:
%  c
% ----
% s^2 

% in the discrete form: z transform with zero order hold approximation:
% y         b0 z^-1 + b1 z^-2
% -- = ------------------------
% u     1 + a1 z^-1 + a2 z^-2
%
% then finally y = a1 [-y(z^-1)] + a2 [-y(z^-2)] + b0 u(z^-1) + b1 u(z^-2)
%              y = a1 phi_1      + a2 phi_2      + b0 phi_3   + b1 phi_4 + c1 * e(z^-1) + c2 * e(z^-2) + c3 * e(z^-3) + c4 * e(z^-4) + c5 * e(z^-5) + c6 * e(z^-6)  ;
%              y = a1 phi_1      + a2 phi_2      + B (phi_3 + phi_4)     + c1 * e(z^-1) + c2 * e(z^-2) + c3 * e(z^-3) + c4 * e(z^-4) + c5 * e(z^-5) + c6 * e(z^-6)  ;
para1 = 10;
para2 = 9;
n = para2; % number of parameters  para1  % a1 a2 b0 b1 c1 c2 c3 c4 c5 c6 or para2  % a1 a2 B c1 c2 c3 c4 c5 c6
L = length(u);
dt = 0.02;
time = 0:dt:dt*(L-1);
%% Extended least squares estimator

%Initialization 
Theta_1 = zeros(n , 1);    % nx1 vector contains parameters to be estimated 
P_1 = 1e4*eye(n);          % nxn identity matrix
e(1) = 0; e(2) = 0; e(3) = 0; e(4) = 0; e(5) = 0; e(6) = 0;
%Online Loop
i = 0;
for i = 7:L

    % assign input vector and output vector
 Yr = y(i);    % system real output at sample time i
 if(n == para1 ) Phi = [-y(i-1) ; -y(i-2) ; u(i-1) ; u(i-2) ; e(i-1) ; e(i-2) ; e(i-3) ; e(i-4) ; e(i-5) ; e(i-6) ]; else Phi = [-y(i-1) ; -y(i-2) ; u(i-1)+u(i-2) ; e(i-1) ; e(i-2) ; e(i-3) ;  e(i-4) ; e(i-5) ; e(i-6)]; end % system variables

 %computations
 K = P_1 * Phi / [1 + Phi'*P_1*Phi]; % gain vector
 P = [eye(n) - K*Phi']*P_1;
 Ym =  Phi'*Theta_1;  % estimated output
 e(i) = Yr - Ym;   % predicted error
 Theta = Theta_1 + K*[e(i)]; 
 
 %Update
 Theta_1 = Theta;
 P_1 = P;
 
ym(i) = Ym;  


 if(n == para1 ) a1(i) = Theta(1); a2(i) = Theta(2); b0(i) = Theta(3); b1(i) = Theta(4); c1(i) = Theta(5); c2(i) = Theta(6); c3(i) = Theta(7); c4(i) = Theta(8); c5(i) = Theta(9); c6(i) = Theta(10);
yf(i) = [-y(i-1) ; -y(i-2) ; u(i-1) ; u(i-2) ]'*Theta(1:4,1);
 else            a1(i) = Theta(1); a2(i) = Theta(2); B(i) = Theta(3);  c1(i) = Theta(4); c2(i) = Theta(5); c3(i) = Theta(6); c4(i) = Theta(7); c5(i) = Theta(8); c6(i) = Theta(9);
yf(i) = [-y(i-1) ; -y(i-2) ; u(i-1)+u(i-2) ]'*Theta(1:3,1);
 end
 
end

%% outputs
 if(n == para1 ) 
plot(time , a1, time , a2) 
xlabel('time (second)')
legend('a1','a2');
title('ELS')
grid
 figure 
plot(time, b0 , time , b1) 
xlabel('time (second)')
axis([0 , 0.02*L,-10e-4 , 10e-4])
legend('b0','b1');
title('ELS')
grid
 figure 
plot(time, c1 , time , c2 , time , c3 , time , c4 , time , c5 , time , c6 ) 
xlabel('time (second)')
legend('c1','c2' ,'c3', 'c4', 'c5', 'c6');
title('ELS')
grid
figure
plot(time,  ym , time , y , time , yf) 
xlabel('time (second)')
legend('ym','y' , 'yf');
title('ELS')
grid
 else        
plot(time , a1, time , a2) 
title('Plotting parameters a1 & a2 with time (ELS)')
xlabel('time (second)')
legend('a1','a2');
grid

 figure 
plot(time, B) 
title('Plotting parameter B with time (ELS)')
xlabel('time (second)')
legend('B');
axis([0 , 0.02*L,-10e-6 , 10e-6])
grid
 figure 
plot(time, c1 , time , c2 , time , c3 , time , c4 , time , c5 , time , c6 ) 
xlabel('time (second)')
legend('c1','c2' ,'c3', 'c4', 'c5', 'c6');
title('ELS')
grid
figure
plot(time,  ym*180/pi , time , y*180/pi)% , time , yf*180/pi) 
xlabel('time (second)')
ylabel('Angle in degree')
legend('Estimate model','Real model');
title('comparison between Real model and estimate model (ELS)')
grid


 end
 


