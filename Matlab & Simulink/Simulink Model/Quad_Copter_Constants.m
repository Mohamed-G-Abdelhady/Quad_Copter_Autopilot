clear all
close all
clc

m=1.1;                  %Kg     
i_yy=8.978e-3;          %Kg.m2  moment of inertia (y- axis)
i_xx=i_yy;              %Kg.m2  moment of inertia (x- axis) 
i_zz=.01648;            %Kg.m2  moment of inertia (z- axis) 
i_r=1.28e-4;            %Kg.m2  rotor inertia 
g=9.81;                 %m.s-2 
k=9.595e-6;             %N.s2/rad2 thrust constant of the motor
b=1.24e-7;              %N.s2/rad2  torque  constant of the motor
l=.25;                  %m    length between the motor center  and the body  c.g.


