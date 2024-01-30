#define triggerPin 10
#define echoPin 11
float distance;
float duration;
String input;
float* values = new float[10];

void setup() {
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  Serial.println("Press enter to go !!!!!!");
  

    while(Serial.available() == 0);{
  
      for(int i = 0; i < 10; i ++){
        digitalWrite(triggerPin, LOW);
      
        delayMicroseconds(2);
        //pulse trigger pin for 10 micros
        digitalWrite(triggerPin, HIGH);
        delayMicroseconds(10);
        digitalWrite(triggerPin, LOW);
        //start clock at 0 to 
        duration = pulseIn(echoPin, HIGH);
        distance = (duration*.0343)/2;

        Serial.println(distance);
        values[i] = distance;
        delay(1000);
      }
    }

//MEASURING TAPE FROM JACK
  float sum;
  for(int i = 0; i < 10; i ++){
    sum = sum + values[i];
  }

  float mean = sum / 10;
  Serial.println("__________________________"); 
  Serial.println(mean);
 
  delay(10000);
 
}
