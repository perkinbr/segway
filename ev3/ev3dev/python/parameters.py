class Gains:
    # For every radian (57 degrees) we lean forward,            apply this amount of duty cycle.
    GyroAngle                  = 6000
    # For every radian/s we fall forward,                       apply this amount of duty cycle.
    GyroRate                   = 95   
    # For every radian we are ahead of the reference,           apply this amount of duty cycle
    MotorAngle                 = 10
    # For every radian/s drive faster than the reference value, apply this amount of duty cycle
    MotorAngularSpeed          = 2.5
    # For every radian x s of accumulated motor angle,          apply this amount of duty cycle
    MotorAngleErrorAccumulated = 2     


class Power:
    voltageNominal = 8.0
    frictionOffsetNominal = 2

class Timing:
    #Timing settings for the program
    loopTimeMiliSec             = 11                    # Time of each loop, measured in miliseconds.
    motorAngleHistoryLength     = 5                     # Number of previous motor angle samples we keep track of.
    gyroDriftCompensationFactor = 0.05      