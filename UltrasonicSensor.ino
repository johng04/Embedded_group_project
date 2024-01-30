#define triggerPin 10
#define echoPin 11
float distance;
float duration;
int STATE = 1;
void setup() {
  pinMode(triggerPin, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
}

void loop() {

    while(STATE == 1){
  
      for(int i = 0; i < 10; i ++){
        digitalWrite(triggerPin, LOW); 
        delayMicroseconds(2);
        //pulse trigger pin for 10 micros
        digitalWrite(triggerPin, HIGH);
        delayMicroseconds(10);
        digitalWrite(triggerPin, LOW);
        //start clock at 0 to 
        duration = pulseIn(echoPin, HIGH);
        distance = (duration * 0.0343)/2;
        if(distance < 8.00){
          digitalWrite(4, HIGH);
        }
        else{digitalWrite(4,LOW);}
        Serial.println(distance);
        delay(200);

      }
    }
}
