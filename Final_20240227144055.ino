/*#include "myServo.h"
#include "motorSet.h"*/
#include <Servo.h>
//SERVO PIN

//IR SENSOR DEFINES
#define d_in_L 24
#define d_in_R 25

//MOTOR DEFINES
#define frontMotor 11
#define backMotor 10
#define VOLTAGE_INPUT A0 
#define servoPin 5

//ULTRASONIC SENSOR PINS
#define triggerPin 22
#define echoPin 23

Servo steering;


//mode.0 = test mode, 1 = line following; 2 = remote control; 3 = ball.
int mode;

//1 or 0 if black line is detected Left or Right.
bool line_R;
bool line_L;

int speed;

void setFrontSpeed(int x){
  int mappedVal = map(x, 0, 100, 0, 150);
  analogWrite(frontMotor, mappedVal);
}

void setBackSpeed(int x){
  int mappedVal = map(x,0,100,0,150);
  analogWrite(backMotor, mappedVal);
}
void setAngle(int x){
  int mappedVal = map(x,-90,90, 0,180);
  steering.write(mappedVal);
}
void straight(){
  steering.write(90);
}
void hardLeft(){
  steering.write(45);
} 
void hardRight(){
  steering.write(135);
} 
void shallowLeft(){
  steering.write(67);
} 
void shallowRight(){
  steering.write(113);
}



void setup() {
  Serial.begin(9600);
  
//inputs
  pinMode(d_in_R, INPUT);
  pinMode(d_in_L, INPUT);
//outputs
  pinMode(servoPin, OUTPUT);
  pinMode(frontMotor, OUTPUT);
  pinMode(backMotor, OUTPUT);
  steering.attach(servoPin);
}

void loop() {
  
  line_R = digitalRead(d_in_R);
  line_L = digitalRead(d_in_L);
  
  while(mode == 0){

  }
  while(mode == 1){
    if(line_L == LOW && line_R == LOW ){
      straight();
      setFrontSpeed(100);
      setBackSpeed(100);
      
    }
    if(line_L == LOW && line_R == HIGH){
      shallowRight();
      setFrontSpeed(80);
      setBackSpeed(75);
    }
    if(line_L == HIGH && line_R == LOW){
      shallowLeft();
      setFrontSpeed(80);
      setBackSpeed(75);
    }
    if(line_L == HIGH && line_R == HIGH){
      setFrontSpeed(0);
      setBackSpeed(0);
    }
  }
    while(mode == 2){
      //John's code here. (Steering mode)

    }
    
    
}
  

  
  /*if(line_L == HIGH){
    digitalWrite(LED_L, HIGH);
    Serial.print("LINE DETECTED ON LEFT.   " );
  }
  else{
    digitalWrite(LED_L, LOW);
    Serial.print("X   ");
  }

  if(line_R == HIGH){
    digitalWrite(LED_R, HIGH);
    Serial.println("LINE DETECTED ON RIGHT." );
  }
  else{
    digitalWrite(LED_R, LOW);
    Serial.println("X");
  }*/

  
