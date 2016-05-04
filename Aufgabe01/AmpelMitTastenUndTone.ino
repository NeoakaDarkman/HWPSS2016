// include LCD functions:
#include <LiquidCrystal.h> 

// define the LCD screen
LiquidCrystal lcd(3, 4, 6, 7, 8, 9);

// global variable, stores the result from analog pin
int analogValue;
int rTone = 0;  // extra variable for redlight tone
int rledPin = 10;
int yledPin = 11;
int gledPin = 12;
int soundPin = 13;
char* button[]={"S1", "S2", "S3", "S4", "S5", "--"};
char* color[]={"Red", "Red + Yellow", "Yellow", "Green"};

void setup() {
  // Pins initialization, creates LCD
  pinMode(rledPin, OUTPUT);
  pinMode(yledPin, OUTPUT);
  pinMode(gledPin, OUTPUT);
  pinMode(soundPin, OUTPUT);
  lcd.begin(20, 4); 
  }

void lcdInit() {
  // Function to initialize LCD-Output
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Analog: ");
  lcd.setCursor(0, 1);
  lcd.print("Button: ");
  lcd.setCursor(8,0);
  lcd.print(analogValue);
}

// Function to print Button State
void lcdPrintButton(int b) {
  lcd.setCursor(8,1);
  lcd.print(button[b]);
}

// Function to Print LED Color
void lcdPrintColor(int c) {
  lcd.setCursor(0, 2);
  lcd.print(color[c]);
}

void loop() {
  analogValue = analogRead(A0);
  digitalWrite(rledPin, HIGH); // Turn on red Light
  // Redlight tone beeps only once
  if (rTone == 0) {
    tone(13, 100, 100); // Tone for red light
    rTone++; // Add 1 to break Tone loop
  }
  lcdInit();
  lcdPrintColor(0);
// IF-Loop to define pressed button
  if (analogValue < 100) {
    lcdInit();
    lcdPrintButton(0);
    // Ampel implementation
    digitalWrite(yledPin, HIGH); // Turn on yellow Light
    lcdPrintColor(1);
    delay(1000);
    digitalWrite(rledPin, LOW); // Turn off red light
    digitalWrite(yledPin, LOW); // Turn off yellow light
    digitalWrite(gledPin, HIGH); // Turn on green light
    tone(13, 400, 100); // Tone For green light
    lcdInit();
    lcdPrintButton(0);
    lcdPrintColor(3);
    delay(3000);
    digitalWrite(gledPin, LOW); // Turn off green light
    digitalWrite(yledPin, HIGH); // Turn on yellow light
    lcdInit();
    lcdPrintButton(0);
    lcdPrintColor(2);
    delay(1000);
    digitalWrite(yledPin, LOW); // Turn of yellow light
    rTone = 0; // Reset variable for Redlight Tone to produce tone
  }
  else if (analogValue >=200 && analogValue <=300) {
    lcdInit();
    lcdPrintColor(0);
    lcdPrintButton(1);
  }
  else if (analogValue >=420 && analogValue <=530) {
    lcdInit();
    lcdPrintColor(0);
    lcdPrintButton(2);
  }
  else if (analogValue >=600 && analogValue <=750) {
    lcdInit();
    lcdPrintColor(0);
    lcdPrintButton(3);
  }
  else if (analogValue >=770 && analogValue <=900) {
    lcdInit();
    lcdPrintColor(0);
    lcdPrintButton(4);
  }
  else {
    lcdInit();
    lcdPrintColor(0);
    lcdPrintButton(5);
  }
  
  delay(200);
  lcd.clear();
}
