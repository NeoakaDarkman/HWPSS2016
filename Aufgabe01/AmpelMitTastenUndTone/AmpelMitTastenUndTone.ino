// include LCD functions:
#include <LiquidCrystal.h> 

// define the LCD screen
LiquidCrystal lcd(3, 4, 6, 7, 8, 9);

// global variable, stores the result from analog pin
int analogValue;
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
  lcd.print("Analog: ");
  lcd.setCursor(0, 1);
  lcd.print("Button: ");


}

void loop() {
  analogValue = analogRead(A0);
  digitalWrite(rledPin, HIGH);
  //tone(13, 100, 100);
  lcd.setCursor(0, 2);
  lcd.print("Red");
  lcd.setCursor(8,0);
  lcd.print("    ");
  lcd.setCursor(8,0);
  lcd.print(analogValue);  
  switch (analogValue){
    case 0:
    lcd.setCursor(8,1);
    lcd.print("S1");
    break;
    
    case 242:
    lcd.setCursor(8,1);
    lcd.print("S2");
    break;
    
    case 472:
    lcd.setCursor(8,1);
    lcd.print("S3");
    break;
    
    case 676:
    lcd.setCursor(8,1);
    lcd.print("S4");
    break;
    
    case 829:
    lcd.setCursor(8,1);
    lcd.print("S5");
    break;
    
    case 1023:
    lcd.setCursor(8,1);
    lcd.print("--");
    break;
    
  }
  if (gled
    delay(200);
  if (analogValue == 0){
  digitalWrite(yledPin, HIGH);
  delay(1000);
  digitalWrite(rledPin, LOW);
  digitalWrite(yledPin, LOW);
  digitalWrite(gledPin, HIGH);
  //tone(13, 400, 100);
  delay(3000);
  digitalWrite(gledPin, LOW);
  digitalWrite(yledPin, HIGH);
  delay(1000);
  digitalWrite(yledPin, LOW);
}
}
