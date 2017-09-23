// This is a crazy experiment on an RCX segway with the HiTechnic Gyro sensor. Turns out it works. More later, maybe!


// ln -s /dev/usb/legousbtower1 /dev/usb/legousbtower0 ## Apparently nqc looks for legousbtower0 hardcoded. Symlink fixes this.
// sudo chmod 666 /dev/usb/legousbtower1 ## Allow it to be used
// nqc -TSwan -Susb -d swantest.c -run ## Compile, download, run
// nqc -Susb -datalog # get the datalog

task main()
{
    // Sensor and hardware setup
    //~ SetSensor(SENSOR_3,SENSOR_ROTATION);
    //~ SetSensor(SENSOR_1,SENSOR_ROTATION);    
    //~ SetSensorType(SENSOR_2,SENSOR_TYPE_NONE); 
    #define approxOffset 585 // Need to make offset dynamic...

    ClearSensor(SENSOR_1);
    ClearSensor(SENSOR_3);   
    //~ CreateDatalog(255);
    
    SetFloatDuringInactivePWM(false);
    SetMotorPowerSigned(MTR_C, 0);
    SetMotorPowerSigned(MTR_A, 0);
    SelectDisplay(DISPLAY_SENSOR_1);
    SetSensorType(SENSOR_1,SENSOR_TYPE_ROTATION);
    SetSensorType(SENSOR_3,SENSOR_TYPE_ROTATION);    

    
    ////////////////////////////////////////////////////////////////////////
    //
    // Definitions and Initialization variables
    //
    ////////////////////////////////////////////////////////////////////////    
                    
               
    //Timing settings for the program
    #define loopTimeMiliSec 20                    // Time of each loop, measured in miliseconds.
    #define loopTime10MiliSec loopTimeMiliSec/10
    #define motorAngleHistoryLength 5             // Number of previous motor angles we keep track of.

    // The rate at which we'll update the gyro offset
    #define gyroDriftCompensationRate 1

    // State feedback control gains (aka the magic numbers)
    #define gainGyroAngle                  45  // For every radian (57 degrees) we lean forward,            apply this amount of duty cycle.
    #define gainGyroRate                   10  // For every radian/s we fall forward,                       apply this amount of duty cycle.
    #define gainMotorAngle                 200     // For every radian we are ahead of the reference,           apply this amount of duty cycle
    #define gainMotorAngularSpeed          500     // For every radian/s drive faster than the reference value, apply this amount of duty cycle
    #define gainMotorAngleErrorAccumulated 0     // For every radian x s of accumulated motor angle,          apply this amount of duty cycle

    int i = 0;

    // Variables representing physical signals (more info on these in the docs)
    int motorAngle                 = 0; // The angle of the motor, converted to radians (2*pi radians equals 360 degrees).
    int motorAngleHistory[motorAngleHistoryLength];
    
    for(i = 0; i < motorAngleHistoryLength; i++){motorAngleHistory[i] = 0;}
    
    int motorAngleReference        = 0; // The reference angle of the motor. The robot will attempt to drive forward or backward, such that its measured position equals this reference (or close enough).
    int motorAngleError            = 0; // The error: the deviation of the measured motor angle from the reference. The robot attempts to make this zero, by driving toward the reference.
    int motorAngleErrorAccumulated = 0; // We add up all of the motor angle error in time. If this value gets out of hand, we can use it to drive the robot back to the reference position a bit quicker.
    int motorAngularSpeed          = 0; // The motor speed, estimated by how far the motor has turned in a given amount of time
    int motorAngularSpeedError     = 0; // The error: the deviation of the motor speed from the reference speed.
    int motorDutyCycle             = 0; // The 'voltage' signal we send to the motor. We calulate a new value each time, just right to keep the robot upright.
    int gyroRate                   = 0; // The angular rate of the robot (how fast it is falling forward or backward), measured in radians per second.
    int gyroEstimatedAngle         = 0; // The gyro doesn't measure the angle of the robot, but we can estimate this angle by keeping track of the gyroRate value in time
    int gyroOffset                 = 0; // Over time, the gyro rate value can drift. This causes the sensor to think it is moving even when it is perfectly still. We keep track of this offset.

    int speed = 0;
    int steering = 0;
    int motorAngleIndex = 0;
    
    //SetUserDisplay(motorAngularSpeedError, 0);    
        
    ////////////////////////////////////////////////////////////////////////
    //
    // Calibrate Gyro
    //
    ////////////////////////////////////////////////////////////////////////    
          
    Wait(100);       
    PlaySound(SOUND_DOUBLE_BEEP);
             
    #define resolution 16
    #define calibrations 50
    for(i = 0; i < calibrations; i++)
    {
        gyroOffset += (SENSOR_2 - approxOffset)*resolution;
        Wait(2);
    }
    gyroOffset /= calibrations;

    PlaySound(SOUND_UP);


    while(true)
    {
        
        ////////////////////////////////////////////////////////////////
        //
        //  Driving and Steering. Modify this section as you like to
        //  make your segway go anywhere!
        //
        ////////////////////////////////////////////////////////////////
     
        // Read e.g. your PS2 controller here. Be sure you don't drag the loop too long
        
        // Or just balance in place:
        speed    = 0; 
        steering = 0;

        ////////////////////////////////////////////////////////////////
        //  Reading the Gyro.
        ////////////////////////////////////////////////////////////////

        gyroRate = (SENSOR_2 - approxOffset)*resolution - gyroOffset;

        ////////////////////////////////////////////////////////////////
        //  Reading the Motor Position
        ////////////////////////////////////////////////////////////////

        motorAngle = -SENSOR_3;
        motorAngleReference = 0; //implement driving later...        
        motorAngleError = motorAngle - motorAngleReference;    
        
        ////////////////////////////////////////////////////////////////
        //  Computing Motor Speed
        ////////////////////////////////////////////////////////////////
        
        motorAngularSpeed = (motorAngle - motorAngleHistory[motorAngleIndex]);
        motorAngularSpeedError = motorAngularSpeed;
        motorAngleHistory[motorAngleIndex] = motorAngle;

        ////////////////////////////////////////////////////////////////
        //  Computing the motor duty cycle value
        ////////////////////////////////////////////////////////////////

        motorDutyCycle =(gainGyroAngle  * gyroEstimatedAngle
                       + (gainGyroRate   * gyroRate)/8
                       + gainMotorAngle * motorAngleError
                       + gainMotorAngularSpeed * motorAngularSpeedError
                       + gainMotorAngleErrorAccumulated * motorAngleErrorAccumulated);    
        
        motorDutyCycle = motorDutyCycle + sign(motorDutyCycle)*5;
        
        SetMotorPowerSigned(MTR_A, motorDutyCycle/100 + steering);
        SetMotorPowerSigned(MTR_C, motorDutyCycle/100 - steering);
        
        ////////////////////////////////////////////////////////////////
        //  Update angle estimate and Gyro Offset Estimate
        ////////////////////////////////////////////////////////////////

        gyroEstimatedAngle = gyroEstimatedAngle + gyroRate/resolution;
        gyroOffset = 0;

        //AddToDatalog(motorAngularSpeed);
        
        ////////////////////////////////////////////////////////////////
        //  Update Accumulated Motor Error
        ////////////////////////////////////////////////////////////////

        motorAngleErrorAccumulated = motorAngleErrorAccumulated + motorAngleError;
        motorAngleIndex = (motorAngleIndex + 1) % motorAngleHistoryLength; 
        
        ////////////////////////////////////////////////////////////////
        // Wait
        ////////////////////////////////////////////////////////////////
        Wait(loopTime10MiliSec);
    }   
    SetMotorPowerSigned(MTR_A, 0);
    SetMotorPowerSigned(MTR_C, 0);
    PlaySound(SOUND_DOWN);
}
