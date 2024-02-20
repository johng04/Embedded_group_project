#include <Servo.h> 
Servo myServo;
void setup() {
  // put your setup code here, to run once:
 myServo.attach(9);
}
 
void loop() {
  // put your main code here, to run repeatedly:
  //notes taken with wires facing away number corrosponds to blade pointing towards wire
digitalWrite(12,LOW);
digitalWrite(13,LOW);
myServo.write(45);//4 left& default state
delay(2000);
digitalWrite(12,HIGH);
myServo.write(90);//1 stright
delay(2000);
digitalWrite(13,HIGH);
myServo.write(135);//2 right
delay(2000);
}
