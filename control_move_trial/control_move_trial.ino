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

int leftMotorSpeed=0;
int rightMotorSpeed=0;

// Set up data recieve and use
String readString;
char lastIncomingData;
int ind1;
String left_motors;
String right_motors;


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
  // Set up serial
  Serial.begin(9600);
}
void loop() {
    if (Serial.available() > 0) {
      lastIncomingData = Serial.read();
      if (lastIncomingData == '*'){
        ind1 = readString.indexOf(',');
        left_motors = readString.substring(0,ind1);
        right_motors = readString.substring(ind1+1);
        leftMotorSpeed = left_motors.toInt();
        rightMotorSpeed = right_motors.toInt();
        // Run car
        leftMotor1->run(FORWARD);
        leftMotor2->run(FORWARD);
        rightMotor1->run(FORWARD);
        rightMotor2->run(FORWARD);

        leftMotor1->setSpeed(leftMotorSpeed);
        leftMotor2->setSpeed(leftMotorSpeed);
        rightMotor1->setSpeed(rightMotorSpeed);
        rightMotor2->setSpeed(rightMotorSpeed);
      }
    }
    else {
      readString += lastIncomingData;
      }
}