// Global Variables
int rledPin = 10;
int yledPin = 11;
int gledPin = 12;

void setup() {
  // Initialize Output Pins
  pinMode(rledPin, OUTPUT);
  pinMode(yledPin, OUTPUT);
  pinMode(gledPin, OUTPUT);
}

void loop() {
  digitalWrite(rledPin, HIGH); // Turn on red Light
  delay(5000);
  digitalWrite(yledPin, HIGH); // Turn on yellow Light
  delay(1000);
  digitalWrite(rledPin, LOW); // Turn off red light
  digitalWrite(yledPin, LOW); // Turn off yellow light
  digitalWrite(gledPin, HIGH); // Turn on green light
  delay(3000);
  digitalWrite(gledPin, LOW); // Turn off green light
  digitalWrite(yledPin, HIGH); // Turn on yellow light
  delay(1000);
  digitalWrite(yledPin, LOW); // Turn of yellow light
}
