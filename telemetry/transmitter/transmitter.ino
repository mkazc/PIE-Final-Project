#include <SPI.h>
#include "printf.h"
#include "RF24.h"
  
// instantiate an object for the nRF24L01 transceiver
RF24 radio(9, 10); // using pin 7 for the CE pin, and pin 8 for the CSN pin

// Let these addresses be used for the pair
uint8_t address[][6] = {"1Node", "2Node"};
// It is very helpful to think of an address as a path instead of as
// an identifying device destination

// to use different addresses on a pair of radios, we need a variable to
// uniquely identify which address this radio will use to transmit
bool radioNumber = 0; // 0 uses address[0] to transmit, 1 uses address[1] to transmit

// For this example, we'll be using a payload containing
// a single float number that will be incremented
// on every successful transmission
float payload = 0.0;


int leftMotorSpeed=0;
int rightMotorSpeed=0;

// Set up data recieve and use
String readString = "";
char lastIncomingChar;
bool begin = false;

void setup() {
  
   Serial.begin(9600);
   while (!Serial) {
     // some boards need to wait to ensure access to serial over USB
   }
   // initialize the transceiver on the SPI bus
   if (!radio.begin()) {
     Serial.println(F("radio hardware is not responding!!"));
     while (1) {} // hold in infinite loop
   }
   // print example's introductory prompt
   Serial.println(F("RF24/examples/GettingStarted"));
   //while (!Serial.available()) {
   // wait for user input
   //}
   char input = Serial.parseInt();
   radioNumber = 0;
   //Serial.print(F("radioNumber = "));
   //Serial.println((int)radioNumber);
  
   // role variable is hardcoded to RX behavior, inform the user of this
   // Serial.println(("PRESS 'T' to begin transmitting to the other node"));
  
   // Set the PA Level low to try preventing power supply related problems
   // because these examples are likely run with nodes in close proximity to
   // each other.
   radio.setPALevel(RF24_PA_LOW);  // RF24_PA_MAX is default.
  
   // save on transmission time by setting the radio to only transmit the
   // number of bytes we need to transmit a float
   radio.setPayloadSize(sizeof(payload)); // float datatype occupies 4 bytes

   // set the TX address of the RX node into the TX pipe
   radio.openWritingPipe(address[radioNumber]);     // always uses pipe 0
  
   // set the RX address of the TX node into a RX pipe
   radio.openReadingPipe(1, address[!radioNumber]); // using pipe 1
  
   // additional setup specific to the node's role
   radio.stopListening();  // put radio in TX mode
  
   // For debugging info
   //printf_begin();             // needed only once for printing details
   // radio.printDetails();       // (smaller) function that prints raw register values
   // radio.printPrettyDetails(); // (larger) function that prints human readable data
  
} // setup


void loop() {
  while(true) {
    if (Serial.available()){
      // Make sure data is at start
      Serial.println("taking serial data!");
      if (!begin){
        lastIncomingChar = Serial.read(); // grab the most recent char
        // when to start through ternary operator, make sure data format usable
        begin = ( lastIncomingChar == '.' ) ? true : false;
      }
      // Make sure that there is new data over Serial
      // Note: needs to include '.', so not else if
      if (begin) {
        lastIncomingChar = Serial.read(); // grab the most recent char
        Serial.println(lastIncomingChar);
        unsigned long start_timer = micros();                    // start the timer
        bool report = radio.write(&payload, sizeof(float));      // transmit & save the report
        unsigned long end_timer = micros();                      // end the timer
        if (report) {
          Serial.print(F("Transmission successful! "));          // payload was delivered
          Serial.print(F("Time to transmit = "));
          Serial.print(end_timer - start_timer);                 // print the timer result
          Serial.print(F(" us. Sent: "));
          Serial.println(payload);                               // print payload sent
          payload += 0.01;                                       // increment float payload
        } else {
          Serial.println(F("Transmission failed or timed out")); // payload was not delivere  
        // to make this example readable in the serial monitor
        } delay(1000);  // slow transmissions down by 1 second
      }
    }
    else{
      Serial.println("No Serial Data");
    }
  }
}
