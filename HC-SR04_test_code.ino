#define triggerPin 10
#define echoPin 11
float distance;
int msTimeTaken;

void setup() {
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  digitalWrite(triggerPin, LOW);
  
  delay(2);
  //pulse trigger pin for 10 micros
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  //start clock at 0 to 
  msTimeTaken = 0;

  do{
    msTimeTaken = msTimeTaken + 1;
    delayMicroseconds(1);
    
  }
  while(echoPin != HIGH);
  
  distance = (msTimeTaken/2000000) * 343; //can be improved with temperature or humidity sensor??
  Serial.println(distance * 100, 2);
}
