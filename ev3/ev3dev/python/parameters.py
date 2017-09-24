class Gains:
    # For every radian (57 degrees) we lean forward,          apply this amount of duty cycle.
    GyroAngle                  = 6000
    # For every radian/s we fall forward,                       apply this amount of duty cycle.
    GyroRate                   = 120   
    # For every radian we are ahead of the reference,           apply this amount of duty cycle
    MotorAngle                 = 12
    # For every radian/s drive faster than the reference value, apply this amount of duty cycle
    MotorAngularSpeed          = 2
    # For every radian x s of accumulated motor angle,          apply this amount of duty cycle
    MotorAngleErrorAccumulated = 0.1     


class Power:
    voltageNominal = 8.0
    frictionOffsetNominal = 5

class Timing:
    #Timing settings for the program
    loopTimeMiliSec             = 15                    # Time of each loop, measured in miliseconds.
    motorAngleHistoryLength     = 7                     # Number of previous motor angle samples we keep track of.
    gyroDriftCompensationFactor = 0.05      