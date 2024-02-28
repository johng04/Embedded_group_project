#include <Servo.h>
//SERVO PIN
#define servoPin 5
Servo steering;
//IR SENSOR DEFINES
#define d_in_L 24
#define d_in_R 25

//MOTOR DEFINES
#define frontMotor 11
#define backMotor 10
#define VOLTAGE_INPUT A0 

//ULTRASONIC SENSOR PINS
#define triggerPin 22
#define echoPin 23

//remote channels
#define CH3 3
#define CH1 2
#define CH6 7

// Integers to represent values from sticks and pots
int ch3Value; //motor
int ch1Value; //steering
bool ch6Value;
// Read the number of a specified channel and convert to the range provided.
// If the channel is off, return the default value
int readChannel(int channelInput, int minLimit, int maxLimit, int defaultValue){
  int ch = pulseIn(channelInput, HIGH, 30000);
  if (ch < 100) return defaultValue;
  return map(ch, 1000, 2000, minLimit, maxLimit);
}
bool readSwitch(byte channelInput, bool defaultValue){
  int intDefaultValue = (defaultValue)? 100: 0;
  int ch = readChannel(channelInput, 0, 100, intDefaultValue);
  return (ch > 50);
}
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

float distance;
int duration;

void setup() {
  Serial.begin(9600);
//inputs
  pinMode(d_in_R, INPUT); //IR sensor
  pinMode(d_in_L, INPUT); //IR sensor
  pinMode(CH3, INPUT); //Speed
  pinMode(CH1, INPUT); //Remote stering
  pinMode(echoPin, INPUT);//US sensor
//outputs
  pinMode(triggerPin, OUTPUT);//US sensor
  pinMode(servoPin, OUTPUT);//Servo
  pinMode(frontMotor, OUTPUT);//Front motor
  pinMode(backMotor, OUTPUT);//Back motor
  steering.attach(servoPin);//Attaches steering servo to pin servoPin (5)
}

void loop() {
  ch6Value = readSwitch(CH6, false);

  //Automatic
  while(mode == 0){

  line_R = digitalRead(d_in_R);
  line_L = digitalRead(d_in_L);
  
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
      digitalWrite(triggerPin, LOW); 
      delayMicroseconds(2);

      //pulse trigger pin for 10 micros
      digitalWrite(triggerPin, HIGH);
      delayMicroseconds(10);
      digitalWrite(triggerPin, LOW);

      //start clock at 0 to
      duration = pulseIn(echoPin, HIGH);
      distance = (duration * 0.0343)/2;

      distance = distance * 100;
    if(distance < 2){
      mode = 2;
    }
  }
    //Manual controll
    while(mode == 1){
  //motor control
      ch3Value = readChannel(CH3, -100, 100, 0);
      int speed=map(ch3Value,-100,100, 0,255);
      analogWrite(frontMotor, speed);
      analogWrite(backMotor, speed);
      //steering control
      ch1Value = readChannel(CH1, -100, 100, 0);
      int angle=map(ch1Value,-100,100, 0,180); //0 left default; 90 forward; 180 right
      if(angle<70 OR angle >110){
        analogWrite(backMotor, 0.8*speed);
      }
    steering.write(angle);
    }   

    while(mode == 2){
      straight();
      setFrontSpeed(0);
      setBackSpeed(0);
      delay(1000);
      setFrontSpeed(100);
      setBackSpeed(100);
    }
}

