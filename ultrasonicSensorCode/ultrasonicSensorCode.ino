
#define echoF 2 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigF 3 //attach pin D3 Arduino to pin Trig of HC-SR04

// defines variables
long durationF;
long durationB;
long duragionL;
long durationR

int distanceF;
int distanceB;
int diistanceL;
int distanceR;

void setup() {
  pinMode(trigF, OUTPUT); // Sets the trigPin as an OUTPUT trigFront
  pinMode(echoF, INPUT); // Sets the echoPin as an INPUT echoFront
}
void loop() {
  // Clears the trigPin condition
  digitalWrite(trigF, LOW);
  delayMicroseconds(2);
  digitalWrite(trigF, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigF, LOW);
  durationF = pulseIn(echoF, HIGH);
  distanceF = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back) in cm

  if(distanceF<5){
  //motor move back  
  }
  
}
