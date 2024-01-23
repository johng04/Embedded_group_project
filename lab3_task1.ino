int cnt=0;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
attachInterrupt(digitalPinToInterrupt(2), countUP,FALLING);
attachInterrupt(digitalPinToInterrupt(3), countDOWN,FALLING);
}

void countUP(){
  cnt++;
  Serial.println(String(cnt));
  delay(300);
}

void countDOWN(){
  cnt--;
  Serial.println(String(cnt));
  delay(300);
}

void loop() {
  // put your main code here, to run repeatedly:

}
