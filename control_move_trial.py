import math
import threading

MOTOR_TOP_SPEED = 40
MOTOR_MID_SPEED = MOTOR_TOP_SPEED/2
MOTOR_INT_SPEED = MOTOR_TOP_SPEED/4

def control_move(x,y,a,b,rb,rt):
    '''
    Takes in controller inputs and outputs motor speeds.

    Inputs:
        x: (-1 to 1) Left Joystick X tilt
        y: (-1 to 1) Left Joystick Y tilt
        a: (0 or 1) A button pressed
        b: (0 or 1) B button pressed
        rb: (0 or 1) Right bumper pressed
        rt: (0 to 1) Right trigger analog
    '''
    left_speed = 0
    right_speed = 0
    # spin in place (change later)
    if rb:
        if (x < 0):
            right_speed = abs(x)*MOTOR_TOP_SPEED
        else:
            left_speed = abs(x)*MOTOR_TOP_SPEED
        return round(left_speed), round(right_speed),\
               round(left_speed), round(right_speed)
    if a:
        left_speed = MOTOR_MID_SPEED + (x*MOTOR_INT_SPEED)
        left_speed = left_speed + abs(y)*(MOTOR_TOP_SPEED-left_speed)
        right_speed = MOTOR_MID_SPEED - (x*MOTOR_INT_SPEED)
        right_speed = right_speed + abs(y)*(MOTOR_TOP_SPEED-right_speed)
    if b:
        left_speed = 0
        right_speed = 0
    return round(left_speed), round(right_speed),\
           round(left_speed), round(right_speed)
