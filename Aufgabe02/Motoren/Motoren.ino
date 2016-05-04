//global
#include <LiquidCrystal.h>

int analogPinValue;
int motorA1 = 10;
int motorA2 = 11;
int motorB1 = 9;
int motorB2 = 6;
int us1 = 12;

LiquidCrystal lcd(2, 3, 4, 5, 7, 8);
// Pins 10, 11 as output and connect them
// with motorsignals A1 and A2
// Pin10 with A1
// Pin11 with A2
// check if spd got right int value.
// Pin9 with B1
// Pin6 with B2

void setup() {
  pinMode(motorA1, OUTPUT);
  pinMode(motorA2, OUTPUT);
  pinMode(motorB1, OUTPUT);
  pinMode(motorB2, OUTPUT);
  //pinMode(us1, INPUT);
  lcd.begin(20,4);
}

void loop() {
  driveForward(20000, 50);
  
}
//Values for selectmotor: 0 for motor A
// 1 for motor B

void setMotorSpeed (boolean forward, uint8_t spd, int selectMotor) {
  // Run the motor with the strength of the variable spd(values from
  // 0-255). 
  // If variable forward == True the robotor moves forward.
  // If variable forward == False the robotor moves backwards.
  // Variable selectMotor decides which motor should work.
  // If selectMotor == 0 motor A works,
  // if selectMotor == 1 motor B works.
  // if selectMotor == 2 both motor works.
  if (selectMotor == 0) {
    if (forward == true) {
      // TODO activate A1
      analogWrite(10, spd);
      digitalWrite(11, LOW);
    } else {
      analogWrite(11, spd);
      digitalWrite(10,  LOW);
      }
  } 
  if (selectMotor == 1) {
    if (forward == true) {
      analogWrite(9, spd);
      digitalWrite(6, LOW);
    } else {
      analogWrite(6, spd);
      digitalWrite(9,  LOW);
    }
  }
  if (selectMotor == 2) {
    if (forward == true) {
      analogWrite(9, spd);
      digitalWrite(6, LOW);
      analogWrite(10, spd);
      digitalWrite(11, LOW);
    } else {
      analogWrite(6, spd);
      digitalWrite(9,  LOW);
      analogWrite(11, spd);
      digitalWrite(10,  LOW);
    }  
}
}

void driveForward(int runtime, uint8_t spd) {
  // let the roboter drive forward for variable runtime with the value
  // of variable speed.
  setMotorSpeed(true, spd, 2); // let both motor run.
  delay(runtime);
  setMotorSpeed(true, 0, 2); // stop both motors.
}

