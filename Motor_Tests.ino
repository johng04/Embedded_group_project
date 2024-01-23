#define m_one_a 1
#define m_one_b 2
#define m_two_a 3
#define m_two_b 4

void setup() {
  
}

void loop() {
  digitalWrite(m_one_a, HIGH);
  digitalWrite(m_one_b, LOW);
  digitalWrite(m_two_a, LOW);
  digitalWrite(m_two_b, LOW);
}
