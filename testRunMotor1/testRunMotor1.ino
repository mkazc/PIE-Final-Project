#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"



// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();

// Select which 'port' M1, M2, M3 or M4. In this case, M1
Adafruit_DCMotor *leftMotor1 = AFMS.getMotor(4);
Adafruit_DCMotor *leftMotor2 = AFMS.getMotor(1);
Adafruit_DCMotor *rightMotor1 = AFMS.getMotor(3);
Adafruit_DCMotor *rightMotor2 = AFMS.getMotor(2);

int leftMotorSpeed=30;
int rightMotorSpeed=30;


void setup() {
  // put your setup code here, to run once:
  AFMS.begin();
  // Set initial motor speeds
  leftMotor1->setSpeed(0);
  leftMotor2->setSpeed(0);
  rightMotor1->setSpeed(0);
  rightMotor2->setSpeed(0);
  // Stop the motors
  leftMotor1->run(FORWARD);
  leftMotor2->run(FORWARD);
  rightMotor1->run(FORWARD);
  rightMotor2->run(FORWARD);
}
void loop() {
    leftMotorSpeed = 30;
    rightMotorSpeed = 30;
    leftMotor1->setSpeed(leftMotorSpeed);
    leftMotor2->setSpeed(leftMotorSpeed);
    rightMotor1->setSpeed(rightMotorSpeed);
    rightMotor2->setSpeed(rightMotorSpeed);
    delay(2000);
  
    leftMotorSpeed = 0;
    rightMotorSpeed = 0;
    leftMotor1->setSpeed(leftMotorSpeed);
    leftMotor2->setSpeed(leftMotorSpeed);
    rightMotor1->setSpeed(rightMotorSpeed);
    rightMotor2->setSpeed(rightMotorSpeed);
    delay(2000);
    delay(5000);
}
