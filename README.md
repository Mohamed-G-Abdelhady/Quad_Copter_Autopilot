# Quad_Copter_Autopilot
Quad Copter Autopilot coded on Arduino board with off-shelf sensors

These codes test different types of controllers equations flying Quad-Copter. Research was on modelling and analysis dynamics of Quad-Copter using simulation software, then Design and implement control algorithm on embedded system. I succeeded to have a flying model with good performance. this Video for the Model in the middle of the project: https://www.youtube.com/watch?v=lZMHRFjNgng 

File: RLS_QUAD_Control is using machine learning technique called "Recursive Least Squares" or "linear Regression" performed real time to estimate the Quad Copter parameters from sensors readings. the results of applying this code to our model is published on     “Attitude and altitude stabilization of quad rotor using parameter estimation and self-tuning controller”
    AIAA Atmospheric Flight Mechanics Conference-June 2015 in Dallas, Texas, U.S.A. http://arc.aiaa.org/doi/abs/10.2514/6.2015-2392


Hardware:
- Arduino mega
- mpu6050 
- Xbee
- Flight Joystick
- Arduino Uno
- Unltrasonic sensor

