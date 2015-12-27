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
%              y = a1 phi_1      + a2 phi_2      + b0 phi_3   + b1 phi_4 
%              y = a1 phi_1      + a2 phi_2      + B (phi_3 + phi_4) 
n = 3; % number of parameters  4 % a1 a2 b0 b1 or 3 % a1 a2 B 
L = length(u);
dt = 0.02;
time = 0:dt:dt*(L-1);
%% Extended least squares estimator

%Initialization 
Theta_1 = zeros(n , 1);    % nx1 vector contains parameters to be estimated 
P_1 = 1e4*eye(n);          % nxn identity matrix

%Online Loop
i = 0;
for i = 3:L

    % assign input vector and output vector
 Yr = y(i);    % system real output at sample time i
 if(n == 4 ) Phi = [-y(i-1) ; -y(i-2) ; u(i-1) ; u(i-2) ]; else Phi = [-y(i-1) ; -y(i-2) ; u(i-1)+u(i-2) ]; end % system variables

 %computations
 K = P_1 * Phi / [1 + Phi'*P_1*Phi]; % gain vector
 P = [eye(n) - K*Phi']*P_1;
 Ym =  Phi'*Theta_1;  % estimated output
 Theta = Theta_1 + K*[Yr - Ym]; 
 
 %Update
 Theta_1 = Theta;
 P_1 = P;
 
ym(i) = Ym;  

 if(n == 4 ) a1(i) = Theta(1); a2(i) = Theta(2); b0(i) = Theta(3); b1(i) = Theta(4);  
 else        a1(i) = Theta(1); a2(i) = Theta(2); B(i) = Theta(3);  
 end
 
end

%% outputs
 if(n == 4 ) 
plot(time , a1, time , a2) 
legend('a1','a2');
title('RLS')
grid
 figure 
plot(time, b0 , time , b1) 
axis([0 , 0.02*L,-10e-4 , 10e-4])
legend('b0','b1');
title('RLS')
grid
figure
plot(time,  ym , time , y) 
legend('ym','y');
title('RLS')
grid
 else        
plot(time , a1, time , a2) 
title('Plotting parameters a1 & a2 with time (RLS)')
legend('a1','a2');
xlabel('time (second)')
grid
 figure 
plot(time, B) 
xlabel('time (second)')
legend('B');
axis([0 , 0.02*L,-10e-6 , 10e-6])
title('Plotting parameter B with time (RLS)')
print('RLSB', '-dpng', '-r600'); %<-Save as PNG with 600 DPI
grid
figure
plot(time,  ym , time , y) 
legend('ym','y');
title('RLS')
grid


 end
 


