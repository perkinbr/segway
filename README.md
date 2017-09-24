# Segway
This repository will hold code for robots balancing on two wheels, made with various robotics platforms.

This code will eventually supersede all of the programs for balancing robots currently available on [Robotsquare] (http://robotsquare.com). If you're not sure how to use this code, please refer to the existing code and associated tutorials for now.

## Currently available platforms

- LEGO MINDSTORMS EV3 (ev3dev/Python):
  - [Building instructions] (http://robotsquare.com/2014/06/23/tutorial-building-balanc3r/)
  - Add a Touch Sensor to Port 1. I added it just like the Gyro, but on the other side of the brick. This will be the program's safe stop button.
  - Run the program like any other ev3dev Python program
     - Transfer and [segway.py](https://github.com/laurensvalk/segway/raw/master/ev3/ev3dev/python/segway.py) and [parameters.py](https://github.com/laurensvalk/segway/raw/master/ev3/ev3dev/python/parameters.py) to your EV3, and put them in the same directory.
     - To turn them into executable scripts, run:
        - chmod +x segway.py
     - Now you can run the program: ./segway.py   
     - Or, use the [VS Code IDE](https://github.com/ev3dev/vscode-ev3dev-browser) for convenience.
     - Wait until you see something on the display/command line
     - Hold segway up right with its resting wheels on the ground and press the Touch Sensor
     - Press the Touch Sensor again to stop. Then again to restart, if you like.

- VEX IQ (RobotC):
  - [Building instructions] (http://robotsquare.com/2016/04/06/tutorial-segway-iq/)
  - [Video] (https://www.youtube.com/watch?v=1P7SWxnKF_A)
  - Instructions for running this program are included in the code.

## Work in progress

- LEGO MINDSTORMS EV3 (EV3-G):  Currently available in legacy segway code
- LEGO MINDSTORMS EV3 (RobotC): Awaiting some gyro issues with RobotC
- LEGO MINDSTORMS NXT (RobotC): Currently available in legacy segway code
- LEGO MINDSTORMS NXT (NXT-G):  Currently available in legacy segway code
