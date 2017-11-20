const int in1 = 2;
const int in2 = 3;
const int enA = 5;
void setup() {
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(enA, OUTPUT);
  Serial.begin(4800);

}

void loop() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(enA, 255);
  Serial.println("On");

  delay(5000);

  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  Serial.println("off");

  delay(5000);

}
