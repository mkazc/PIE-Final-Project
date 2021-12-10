#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(9, 10); // CE, CSN

// NOTE: the "LL" at the end of the constant is "LongLong" type
const uint64_t pipe = 0xE8E8F0F0E1LL; // Define the transmit pipe


int leftMotorSpeed=0;
int rightMotorSpeed=0;

// Set up data recieve and use
String readString = "";
char lastIncomingChar;
bool begin = false;
void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(pipe);
}

void loop() {
  while(true) {
    
    if (Serial.available() > 0){
      // Make sure data is at start
      if (!begin){
        lastIncomingChar = Serial.read(); // grab the most recent char
        // when to start through ternary operator, make sure data format usable
        begin = ( lastIncomingChar == '.' ) ? true : false;
      }
      // Make sure that there is new data over Serial
      // Note: needs to include '.', so not else if
      if (begin) {
        lastIncomingChar = Serial.read(); // grab the most recent char
        // run when final index sent
        radio.write(lastIncomingChar, sizeof(lastIncomingChar));
        Serial.println(lastIncomingChar);
      }
    }
  }
}
