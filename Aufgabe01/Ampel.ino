int rledPin = 10;
int yledPin = 11;
int gledPin = 12;
void setup() {
  // put your setup code here, to run once:
  pinMode(rledPin, OUTPUT);
  pinMode(yledPin, OUTPUT);
  pinMode(gledPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(rledPin, HIGH);
  delay(5000);
  digitalWrite(yledPin, HIGH);
  delay(1000);
  digitalWrite(rledPin, LOW);
  digitalWrite(yledPin, LOW);
  digitalWrite(gledPin, HIGH);
  delay(3000);
  digitalWrite(gledPin, LOW);
  digitalWrite(yledPin, HIGH);
  delay(1000);
  digitalWrite(yledPin, LOW);
}
