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
bool begin = false;
int ind0;
int ind1;
int ind2;
String left_motors = "";
String right_motors = "";
int lastDirection;
int currentDirection;

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
    // Make sure data is at start
    if (!begin){
      lastIncomingChar = Serial.read(); // grab the most recent char
      // when to start through ternary operator, make sure data format usable
      begin = ( lastIncomingChar == '.' ) ? true : false;
    }
    // Make sure that there is new data over Serial
    if ((Serial.available() > 0) && (begin)) {
          lastIncomingChar = Serial.read(); // grab the most recent char
          // run when final index sent
          if(lastIncomingChar == '*') {
            ind0 = readString.indexOf('.'); // find initial index value
            ind1 = readString.indexOf(','); // find index value of ',' in string
            left_motors = readString.substring(ind0+1,ind1); // grab string from index 0 to ','
            right_motors = readString.substring(ind1+1); // grab string from index ',' on
            leftMotorSpeed = left_motors.toInt(); // get integer value and store
            rightMotorSpeed = right_motors.toInt();
            // change speed
            currentDirection=1;
            if(leftMotorSpeed<0&&rightMotorSpeed<0){
              currentDirection=0;
            }
            if(currentDirection!=lastDirection){
              if(currentDirection==1){
                leftMotor1->run(FORWARD);
                leftMotor2->run(FORWARD);
                rightMotor1->run(FORWARD);
                rightMotor2->run(FORWARD);
                }
              else{
                leftMotor1->run(BACKWARD);
                leftMotor2->run(BACKWARD);
                rightMotor1->run(BACKWARD);
                rightMotor2->run(BACKWARD);
                }
            }
            leftMotorSpeed=abs(leftMotorSpeed);
            rightMotorSpeed=abs(rightMotorSpeed);
            leftMotor1->setSpeed(leftMotorSpeed);
            leftMotor2->setSpeed(leftMotorSpeed);
            rightMotor1->setSpeed(rightMotorSpeed);
            rightMotor2->setSpeed(rightMotorSpeed);
            // clear string to reuse
            readString = "";
            lastDirection=currentDirection;
          }
          else {
            // build string starting from '.' until '*' char is reached
            readString += lastIncomingChar;
          }
    }
  }
}
