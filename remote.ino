#include <Servo.h> 
Servo myServo;
// Define Input Connections
#define front 11
#define back 10
#define CH3 6
#define CH1 9
 
// Integers to represent values from sticks and pots
int ch3Value; //motor
int ch1Value; //steering
 
// Read the number of a specified channel and convert to the range provided.
// If the channel is off, return the default value
int readChannel(int channelInput, int minLimit, int maxLimit, int defaultValue){
  int ch = pulseIn(channelInput, HIGH, 30000);
  if (ch < 100) return defaultValue;
  return map(ch, 1000, 2000, minLimit, maxLimit);
}
 
void setup(){
  // Set up serial monitor
  Serial.begin(9600);
  //attach servo
  myServo.attach(9);
  // Set all pins as inputs
  pinMode(CH3, INPUT);
  pinMode(CH1, INPUT);
}

void loop() {
  //motor control
  ch3Value = readChannel(CH3, -100, 100, 0);
  int speed=map(ch3Value,-100,100, 0,255);
  analogWrite(front, speed);
  analogWrite(back, speed);
  //steering control
  ch1Value = readChannel(CH1, -100, 100, 0);
  int angle=map(angle,-100,100, 0,180); //0 left default; 90 forward; 180 right
  myServo.write(angle);
  // // Print to Serial Monitor
  Serial.println("Speed:"+speed);
  Serial.println("angle:"+angle);
  delay(500);
}