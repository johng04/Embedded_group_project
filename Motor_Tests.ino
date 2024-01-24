#define m_one_a 10 //front left
#define m_one_b 11 //front right
#define m_two_a 12 //back left
#define m_two_b 13 //back right

void setup() {
  analogWrite(m_one_a, 100);
  analogWrite(m_one_b, 100);
  analogWrite(m_two_a, 100);
  analogWrite(m_two_b, 100);
}

void loop() {
  delay(5000);
  analogWrite(m_one_a, 0);
  analogWrite(m_one_b, 0);
  analogWrite(m_two_a, 0);
  analogWrite(m_two_b, 0);
}
