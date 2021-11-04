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
String readString = "";
char lastIncomingChar;
int ind0;
int ind1;
int ind2;
String left_motors = "";
String right_motors = "";


void setup() {
  // put your setup code here, to run once:
  AFMS.begin();
  // Set initial motor speeds
  leftMotor1->setSpeed(leftMotorSpeed);
  leftMotor2->setSpeed(leftMotorSpeed);
  rightMotor1->setSpeed(rightMotorSpeed);
  rightMotor2->setSpeed(rightMotorSpeed);
  // Stop the motors, set to run forward
  // NOTE: Don't call often, will make wheels jitter
  leftMotor1->run(FORWARD);
  leftMotor2->run(FORWARD);
  rightMotor1->run(FORWARD);
  rightMotor2->run(FORWARD);
  // Set up serial
  Serial.begin(9600);
}

void loop() {
  while(true) {
    // Make sure that there is new data over Serial
    if (Serial.available() > 0) {
          lastIncomingChar = Serial.read(); // grab the most recent char
          if(lastIncomingChar == '*') {
            ind1 = readString.indexOf('.'); // find initial index value
            ind1 = readString.indexOf(','); // find index value of ',' in string
            left_motors = readString.substring(ind0+1,ind1); // grab string from index 0 to ','
            right_motors = readString.substring(ind1+1); // grab string from index ',' on
            leftMotorSpeed = left_motors.toInt(); // get integer value and store
            rightMotorSpeed = right_motors.toInt();
            // change speed
            leftMotor1->setSpeed(leftMotorSpeed);
            leftMotor2->setSpeed(leftMotorSpeed);
            rightMotor1->setSpeed(rightMotorSpeed);
            rightMotor2->setSpeed(rightMotorSpeed);
            // clear string to reuse
            readString = "";
          }
          else {
            readString += lastIncomingChar; // build string until '*' char is reached
          }
    }
  }
}
