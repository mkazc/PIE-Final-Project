#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include "printf.h"
RF24 radio(9, 10); // CE, CSN

// Let these addresses be used for the pair
uint8_t address[][6] = {"1Node", "2Node"};
// It is very helpful to think of an address as a path instead of as
// an identifying device destination

#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"
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
bool done;
int ind0;
int ind1;
String left_motors = "";
String right_motors = "";
int lastDirection=1;
int currentDirection;
#define echoF 2 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigF 3 //attach pin D3 Arduino to pin Trig of HC-SR04

long distanceF;

int Speed;
unsigned long new_time;
unsigned long next_time;

#define INTERVAL    30
#define MAX_ECHO    30000
#define SCALE_CM    58

// to use different addresses on a pair of radios, we need a variable to
// uniquely identify which address this radio will use to transmit
bool radioNumber = 1; // 0 uses address[0] to transmit, 1 uses address[1] to transmit

// Used to control whether this node is sending or receiving
bool role = false;  // true = TX role, false = RX role

// For this example, we'll be using a payload containing
// a single float number that will be incremented
// on every successful transmission
float payload = 0.0;
  

void makePayload(uint8_t); // prototype to construct a payload dynamically

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
  pinMode(trigF, OUTPUT);
  digitalWrite(trigF, LOW);       // Set trig pin LOW here NOT later
  pinMode(echoF, INPUT);


   
  Serial.begin(9600);
  while (!Serial) {
    // some boards need to wait to ensure access to serial over USB
  }

  // initialize the transceiver on the SPI bus
  if (!radio.begin()) {
    Serial.println(F("radio hardware is not responding!!"));
    while (1) {} // hold in infinite loop
  }

  if (radio.begin()){
    Serial.println("no hardware issue yayy...");
    //while (!Serial.available()) {
      // wait for user input
    //}
    char input = Serial.parseInt();
    radioNumber = 1;
    Serial.print(F("radioNumber = "));
    Serial.println((int)radioNumber);

    // Set the PA Level low to try preventing power supply related problems
    // because these examples are likely run with nodes in close proximity to
    // each other.
    radio.setPALevel(RF24_PA_LOW);  // RF24_PA_MAX is default.

    // save on transmission time by setting the radio to only transmit the
    // number of bytes we need to transmit a float
    radio.setPayloadSize(sizeof(payload)); // float datatype occupies 4 bytes

    // set the RX address of the TX node into a RX pipe
    radio.openReadingPipe(1, address[!radioNumber]); // using pipe 1

    // additional setup specific to the node's role
    radio.startListening(); // put radio in RX mode
  }  

  // For debugging info
  // printf_begin();             // needed only once for printing details
  // radio.printDetails();       // (smaller) function that prints raw register values
  // radio.printPrettyDetails(); // (larger) function that prints human readable data
} // setup

void loop() {
  while(true) {
    new_time = millis( );
      if( new_time >= next_time ){
        digitalWrite( trigF, HIGH );
        delayMicroseconds( 10 );
        digitalWrite( trigF, LOW );
        distanceF = pulseIn( echoF, HIGH, MAX_ECHO );
        if( distanceF > 0 ){
        distanceF /= SCALE_CM;
        }
        
        next_time = new_time + INTERVAL;   // save next time to run this part of loop
      }
        if(distanceF<5){
          leftMotor1->run(BACKWARD);
          leftMotor2->run(BACKWARD);
          rightMotor1->run(BACKWARD);
          rightMotor2->run(BACKWARD);
        
          Speed=30;
          leftMotor1->setSpeed(Speed);
          leftMotor2->setSpeed(Speed);
          rightMotor1->setSpeed(Speed);
          rightMotor2->setSpeed(Speed);
          delay(700);
        
          leftMotor1->run(FORWARD);
          leftMotor2->run(FORWARD);
          rightMotor1->run(FORWARD);
          rightMotor2->run(FORWARD);
          leftMotor1->setSpeed(0);
          leftMotor2->setSpeed(0);
          rightMotor1->setSpeed(0);
          rightMotor2->setSpeed(0);
        }
        

    // This device is a RX node
    uint8_t pipe;
    if (radio.available(&pipe)) {             // is there a payload? get the pipe number that recieved it
      uint8_t bytes = radio.getPayloadSize(); // get the size of the payload
      radio.read(&payload, bytes);            // fetch payload from FIFO
      // Serial.print(F("Received "));
      // Serial.print(bytes);                    // print the size of the payload
      // Serial.print(F(" bytes on pipe "));
      // Serial.print(pipe);                     // print the pipe number
      // Serial.print(F(": "));
      // Serial.println(payload);                // print the payload's value
 
      // run when final index sent
      lastIncomingChar = payload;
      Serial.println(lastIncomingChar);
      if(lastIncomingChar == '*') {
        ind0 = readString.indexOf('.'); // find initial index value
        ind1 = readString.indexOf(','); // find index value of ',' in string
        left_motors = readString.substring(ind0+1,ind1); // grab string from past '.' index to ','
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
    else{
      Serial.println("No Radio Available");
    }
  }
}
