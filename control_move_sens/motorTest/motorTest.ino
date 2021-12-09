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
int lastDirection=1;
int currentDirection;
#define echoF 2 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigF 3 //attach pin D3 Arduino to pin Trig of HC-SR04
#define echoB 4 //SENSOR IN THE BACK
#define trigB 5 //SENSOR IN THE BACK
#define echoL 6 //SENSOR IN THE LEFT
#define trigL 7 //SENSOR IN THE LEFT
#define echoR 8 //SENSOR IN THE RIGHT
#define trigR 9 //SENSOR IN THE RIGHT
long distanceF;
long distanceB;
long distanceL;
long distanceR;
int Speed;
unsigned long new_time;
unsigned long next_time;

#define INTERVAL    30
#define MAX_ECHO    30000
#define SCALE_CM    58

void setup() {
  // put your setup code here, to run once:
 // pinMode(trigF, OUTPUT); // Sets the trigPin as an OUTPUT trigFront
 // pinMode(echoF, INPUT); // Sets the echoPin as an INPUT echoFront
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
  next_time = INTERVAL;       /* set time from reset */
  pinMode( trigF, OUTPUT );
  pinMode( trigB, OUTPUT );
  pinMode( trigL, OUTPUT );
  pinMode( trigR, OUTPUT );
  digitalWrite( trigF, LOW );       // Set trig pin LOW here NOT later
  digitalWrite( trigB, LOW );       // Set trig pin LOW here NOT later
  digitalWrite( trigL, LOW );       // Set trig pin LOW here NOT later
  digitalWrite( trigR, LOW );       // Set trig pin LOW here NOT later
  pinMode( echoF, INPUT );
  pinMode( echoB, INPUT );
  pinMode( echoL, INPUT );
  pinMode( echoR, INPUT );
  Serial.begin( 9600 );
}

void loop() {
  leftMotorSpeed=30;
  rightMotorSpeed=30;
    leftMotor1->setSpeed(leftMotorSpeed);
  leftMotor2->setSpeed(leftMotorSpeed);
  rightMotor1->setSpeed(rightMotorSpeed);
  rightMotor2->setSpeed(rightMotorSpeed);
  delay(1000);
    leftMotorSpeed=0;
  rightMotorSpeed=0;
    leftMotor1->setSpeed(leftMotorSpeed);
  leftMotor2->setSpeed(leftMotorSpeed);
  rightMotor1->setSpeed(rightMotorSpeed);
  rightMotor2->setSpeed(rightMotorSpeed);
  delay(1000);
}
