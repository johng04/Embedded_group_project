#include <Servo.h>
//SERVO PIN
#define servoPin 5
Servo steering;
//IR SENSOR DEFINES
#define IR_L A15
#define IR_R A14

//MOTOR DEFINES (PLace motor diraction)
#define FLMotorF 13 //M2b
#define FRMotorF 12 //M1b
#define BRMotorF 6 //M1a
#define BLMotorF 8 //M2a
#define FLMotorB 10 //M1a
#define FRMotorB 11 //M2a
#define BLMotorB 7 //M1b
#define BRMotorB 9 //M2b

//LED
#define LED 24

//ULTRASONIC SENSOR PINS
#define triggerPin 22
#define echoPin 23

//remote channels
#define RSteering 2 //ch1
#define RSpeed 3 //ch3
#define RONOFF 4 //ch6

// Integers to represent values from sticks and pots
int RSpeedValue; //motor
int RSteeringValue; //steering
bool mode;
bool push;
// Read the number of a specified channel and convert to the range provided.
// If the channel is off, return the default value
int readChannel(int channelInput, int minLimit, int maxLimit, int defaultValue){
  int ch = pulseIn(channelInput, HIGH, 30000);
  if (ch < 100) return defaultValue;
  return map(ch, 1000, 2000, minLimit, maxLimit);
}
 
// Read the switch channel and return a boolean value
bool readSwitch(byte channelInput, bool defaultValue){
  int intDefaultValue = (defaultValue)? 100: 0;
  int ch = readChannel(channelInput, 0, 100, intDefaultValue);
  return (ch > 50);
}
//1 or 0 if black line is detected Left or Right.
int line_R;
int line_L;

int blackVal = 500;

int Mspeed;

void setFrontSpeed(int x){
  int mappedValx = map(x, -100, 100, -150, 150);
  analogWrite(FLMotorF, mappedValx);
}

void setBackSpeed(int y){
  int mappedValy = map(y,-100,100,-150,150);
  analogWrite(FLMotorF, mappedValy);
}
void setAngle(int z){
  int mappedValz = map(z,-45,45, 0,180);
  steering.write(mappedValz);
}

void straight(){
  setAngle(0);

}
void hardLeft(){
  setAngle(-45);

} 
void hardRight(){
  setAngle(45);
} 
void shallowLeft(){
  setAngle(-20);
} 
void shallowRight(){
  setAngle(20);
}

float distance;
int duration;
bool Radio;

void setup() {
  Serial.begin(9600);
//inputs
  pinMode(IR_R, INPUT); //IR sensor
  pinMode(IR_L, INPUT); //IR sensor
  pinMode(RSpeed, INPUT); //Speed
  pinMode(RSteering, INPUT); //Remote stering
  pinMode(echoPin, INPUT);//US sensor
  pinMode(RONOFF, INPUT);//RONOFF sensor
//outputs
  pinMode(triggerPin, OUTPUT);//US sensor
  pinMode(servoPin, OUTPUT);//Servo
  pinMode(FLMotorB, OUTPUT);//Front motor
  pinMode(FRMotorB, OUTPUT);
  pinMode(FLMotorF, OUTPUT);
  pinMode(FRMotorF, OUTPUT);
  pinMode(BLMotorF, OUTPUT);//Back motor
  pinMode(BRMotorF, OUTPUT);
  pinMode(BLMotorB, OUTPUT);
  pinMode(BRMotorB, OUTPUT);
  pinMode(LED, OUTPUT);//Back motor
  steering.attach(servoPin);//Attaches steering servo to pin servoPin (5)
  push = 0;
  mode = false;
}

void loop() {
 Radio = readSwitch(RONOFF, false);
 //Serial.println(Radio);
  if (Radio == true){
    mode = true;
  }
  else{
    mode = false;
  }
  line_R = analogRead(IR_R);
  line_L = analogRead(IR_L);
  Serial.println(line_R);
  Serial.println();
  Serial.println(line_L);
    Serial.println("New");
    Serial.println();
    delay(500);
  //Automatic
  /*if(mode == false){
    digitalWrite(LED, LOW);

    if(push == 0){
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
        if(push == 1){
          straight();
          setFrontSpeed(0);
          setBackSpeed(0);
          delay(1000);
          setFrontSpeed(80);
          setBackSpeed(80);

          if(line_L >= blackVal || line_R >= blackVal){
            analogWrite(BLMotorF, -80);
            analogWrite(FLMotorF, -80);
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
    }*/
  

    //Manual controll
    if(mode == true){
      analogWrite(FLMotorB, 0);
      analogWrite(FRMotorB, 0);
      analogWrite(BLMotorB, 0);
      analogWrite(BRMotorB, 0);
  //motor control
      digitalWrite(LED, HIGH);
      RSpeedValue = readChannel(RSpeed, -100, 100, 0);
      int Mspeed=map(RSpeedValue,-100,100, 0,150);
      analogWrite(FRMotorB, Mspeed);
      analogWrite(BLMotorF, Mspeed);
      analogWrite(FRMotorF, Mspeed);
      analogWrite(BRMotorF, Mspeed);
      //steering control
      RSteeringValue = readChannel(RSteering, -100, 100, 0);
      int angle=map(RSteeringValue,-100,100, 55,135); //0 left default; 90 forward; 180 right
      /*if(angle<70 || angle >110){
        analogWrite(BLMotorF, 0.8*Mspeed);
        analogWrite(BRMotorF, 0.8*Mspeed);
      }*/
      Serial.println(RONOFF);
      Serial.println(Mspeed);
      Serial.println(angle);
    steering.write(angle);
    }   

    
}
