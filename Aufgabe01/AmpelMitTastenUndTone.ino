// include LCD functions:
#include <LiquidCrystal.h> 

// define the LCD screen
LiquidCrystal lcd(3, 4, 6, 7, 8, 9);

// global variable, stores the result from analog pin
int analogValue;
int rTone = 0;
int rledPin = 10;
int yledPin = 11;
int gledPin = 12;
int soundPin = 13;

void setup() {
  // put your setup code here, to run once:
  pinMode(rledPin, OUTPUT);
  pinMode(yledPin, OUTPUT);
  pinMode(gledPin, OUTPUT);
  pinMode(soundPin, OUTPUT);
  lcd.begin(20, 4); 
  }

void loop() {
  lcd.setCursor(0,0);
  lcd.print("Analog: ");
  lcd.setCursor(0, 1);
  lcd.print("Button: ");
  analogValue = analogRead(A0);
  digitalWrite(rledPin, HIGH);
  if (rTone == 0)
  {
    tone(13, 100, 100);
    rTone++;
  }
  lcd.setCursor(0, 2);
  lcd.print("Red");
  lcd.setCursor(8,0);
  lcd.print("    ");
  lcd.setCursor(8,0);
  lcd.print(analogValue);
  if (analogValue < 100) {
    lcd.setCursor(8,1);
    lcd.print("S1");
    digitalWrite(yledPin, HIGH);
    lcd.setCursor(0, 2);
    lcd.print("              ");
    lcd.setCursor(0, 2);
    lcd.print("Red + Yellow");
    delay(1000);
    digitalWrite(rledPin, LOW);
    digitalWrite(yledPin, LOW);
    digitalWrite(gledPin, HIGH);
    tone(13, 400, 100);
    lcd.setCursor(0, 2);
    lcd.print("              ");
    lcd.setCursor(0, 2);
    lcd.print("Green");
    delay(3000);
    digitalWrite(gledPin, LOW);
    digitalWrite(yledPin, HIGH);
    lcd.setCursor(0, 2);
    lcd.print("              ");
    lcd.setCursor(0, 2);
    lcd.print("Yellow");
    delay(1000);
    digitalWrite(yledPin, LOW);
    rTone = 0;
  }
  else if (analogValue >=200 && analogValue <=300) {
    lcd.setCursor(8,1);
    lcd.print("S2");
  }
  else if (analogValue >=420 && analogValue <=530) {
    lcd.setCursor(8,1);
    lcd.print("S3");
  }
  else if (analogValue >=600 && analogValue <=750) {
    lcd.setCursor(8,1);
    lcd.print("S4");
  }
  else if (analogValue >=770 && analogValue <=900) {
    lcd.setCursor(8,1);
    lcd.print("S5");
  }
  else {
    lcd.setCursor(8,1);
    lcd.print("--");
  }
  delay(200);
  lcd.clear();
}
