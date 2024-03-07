#include <Servo.h>
//SERVO PIN
#define servoPin 5
Servo steering;
//IR SENSOR DEFINES
#define d_in_L A15
#define d_in_R A14

//MOTOR DEFINES
#define frontMotor 11
#define backMotor 10

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
bool mode;
bool push;
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
int line_R;
int line_L;

int blackVal = 500;

int speed;

void setFrontSpeed(int x){
  int mappedVal = map(x, -100, 100, -150, 150);
  analogWrite(frontMotor, mappedVal);
}

void setBackSpeed(int x){
  int mappedVal = map(x,-100,100,-150,150);
  analogWrite(backMotor, mappedVal);
}
void setAngle(int x){
  int mappedVal = map(x,-90,90, 0,180);
  steering.write(mappedVal);
}
void straight(){
  setAngle(0);

}
void hardLeft(){
  setAngle(-45);

} 
void hardRight(){
  steering.write(45);
} 
void shallowLeft(){
  steering.write(-23);
} 
void shallowRight(){
  steering.write(23);
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
  push = 0;
  mode = 0;
}

void loop() {
  mode = readSwitch(CH6, false);
  line_R = analogRead(d_in_R);
  line_L = analogRead(d_in_L);
  //Automatic
  while(mode == 0){
    

    while(push == 0){
        if(line_L < blackVal && line_R < blackVal){
          straight();
          setFrontSpeed(100);
          setBackSpeed(100);
          
        }
        if(line_L < blackVal && line_R >= blackVal){
          shallowRight();
          setFrontSpeed(80);
          setBackSpeed(75);
        }
        if(line_L >= HIGH && line_R < blackVal){
          shallowLeft();
          setFrontSpeed(80);
          setBackSpeed(75);
        }
        if(line_L >= blackVal && line_R >= blackVal){
          straight();
          setFrontSpeed(20);
          setBackSpeed(20);
        }
    }
        while(push == 1){
          straight();
          setFrontSpeed(0);
          setBackSpeed(0);
          delay(1000);
          setFrontSpeed(80);
          setBackSpeed(80);

          if(line_L >= blackVal || line_R >= blackVal){
            analogWrite(backMotor, -80);
            analogWrite(frontMotor, -80);
            delay(2000);
            exit(0);
          }
        }
  }
    //ULTRASONIC TRIGGER
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
      Serial.println(distance);
    if(distance < 2){
      push = 1;
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
      if(angle<70 || angle >110){
        analogWrite(backMotor, 0.8*speed);
      }
    steering.write(angle);
    }   

    
}
