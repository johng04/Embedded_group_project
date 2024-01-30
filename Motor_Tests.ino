 #define VOLTAGE_INPUT A0 
#define front 11
#define back 10

void setup() {

}

void loop() {
int rawValue = analogRead(VOLTAGE_INPUT);
int output_val=map(rawValue,0,1023, 0,100);
  analogWrite(front, output_val);
  analogWrite(back, output_val);
}
