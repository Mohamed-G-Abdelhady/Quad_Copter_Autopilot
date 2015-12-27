clc ;
clear all ;
close all ;
s = serial('COM29');
set(s, 'InputBufferSize', 1024);
set(s, 'FlowControl', 'none');
set(s, 'BaudRate', 9600);
set(s, 'Parity', 'none');
set(s, 'DataBits', 8);
set(s, 'StopBit', 1);
set(s, 'Timeout',1000);
o = 'open';
c = 'closed';
status = s.Status;
if (strcmp(o, status)  == 1)
fclose(s);
fopen(s);
else
fopen(s);
end

joy1 = vrjoystick(1);
A = caps(joy1);

c = ',';
e = '#';
while true
y1 = num2str(axis(joy1, 1)*255);
x1 = num2str(axis(joy1, 2)*255);
x2 = num2str(axis(joy1, 3)*255);
y2 = num2str(axis(joy1, 4)*255);
 
 b1 = num2str(button(joy1, 1));
% b2 = num2str(button(joy1, 2));
% b3 = num2str(button(joy1, 3));
% b4 = num2str(button(joy1, 4));

   
output = [ x1 c y1 c x2 c y2 c b1 c e]
fwrite(s, output);
pause(0.01);
end

