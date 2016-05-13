//global
#include <LiquidCrystal.h>

int analogValue;
int motorA1 = 10;
int motorA2 = 11;
int motorB1 = 6;
int motorB2 = 9;
int us1 = 12;

LiquidCrystal lcd(2, 3, 4, 5, 7, 8);
// Pins 10, 11 as output and connect them
// with motorsignals A1 and A2
// Pin10 with A1
// Pin11 with A2
// check if spd got right int value.
// Pin6 with B1
// Pin9 with B2

void setup() {
  pinMode(motorA1, OUTPUT);
  pinMode(motorA2, OUTPUT);
  pinMode(motorB1, OUTPUT);
  pinMode(motorB2, OUTPUT);
  lcd.begin(20,4);
}

void loop() {
  analogValue = analogRead(A0);
  if (analogValue < 100)  // S1
  {
    circle();
  }
  else if (analogValue >=200 && analogValue <=300)  // S2
  {
    triangle();
  }
  else if (analogValue >= 420 && analogValue <=530)  // S3
  {
    driveWithoutCollision();
  }
  else if (analogValue >=600 && analogValue <=750)  // S4
  {
    square();
  }
  else if (analogValue >=770 && analogValue <= 900)  // S5
  {
    hexagon();
  }
  else
  {
  driveForward(2000, 100);
  delay(2000);
  int cm = meassureDistance(us1);
  lcd.clear();
  lcd.print(cm);
  delay(1000);
  }
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
      // TODO activate A2, A1 is backwards.
      analogWrite(motorA2, spd);
      digitalWrite(motorA1, LOW);
    } else {
      analogWrite(motorA1, spd);
      digitalWrite(motorA2,  LOW);
      }
  } 
  if (selectMotor == 1) {
    if (forward == true) {
      analogWrite(motorB2, spd);
      digitalWrite(motorB1, LOW);
    } else {
      analogWrite(motorB1, spd);
      digitalWrite(motorB2,  LOW);
    }
  }
  if (selectMotor == 2) {
    if (forward == true) {
      analogWrite(motorB2, spd);
      digitalWrite(motorB1, LOW);
      analogWrite(motorA2, spd);
      digitalWrite(motorA1, LOW);
    } else {
      analogWrite(motorB1, spd);
      digitalWrite(motorB2,  LOW);
      analogWrite(motorA1, spd);
      digitalWrite(motorA2,  LOW);
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

void driveCurve(int runtime, uint8_t spd, uint8_t str){
  // strength has to be between -90 and 90
  // at 90 and -90 do a circle
  // at 0 drive straight forward
  float sp = - spd * (str - 45)/45; 
  int spB = (int)sp;
  sp = spd * (45 - str)/45;
  int spF = (int)sp;
  if(str > -1){
      analogWrite(motorA2, spd); 
      // Motor A always forward
      digitalWrite(motorA1, LOW);
      
      if (str == 0){
        driveForward(runtime, spd);
        }    
      
      else if(str == 45){
        digitalWrite(motorB1, LOW);
        digitalWrite(motorB2, LOW);
        }
      else if(str > 45){
        analogWrite(motorB1, spB);// motor B backwards
        digitalWrite(motorB2, LOW);
        }
      // motor B forward
      else{
        analogWrite(motorB2, spF);
        digitalWrite(motorB1, LOW);
      }
  }
  else{
     sp =  spd * (45 - str)/45;
    int spB1 = (int)sp;
     sp = spd * (str + 45)/45;
    int spF1 = (int)sp;

    analogWrite(motorB2, spd);
    // Motor B always forward
    digitalWrite(motorB1, LOW);
    if(str > -44){
      if (str == -45){
        digitalWrite(motorA2, LOW);
        digitalWrite(motorA1, LOW);
        }
      else{
        analogWrite(motorA2, spB1);
        digitalWrite(motorA1, LOW);
      }
    }
     // motor A backwards
    else{
      analogWrite(motorA1, spF1);
      digitalWrite(motorA2, LOW);
    }
  }
    delay(runtime);
  }

  void circle() {
  // drives a circle
  driveCurve(20000, 100, 40);
}
void square(){
  // drives a square
  int i = 0;
  while (i <= 3 ) {  // do this four times.
    driveForward(3000, 100);
    driveCurve(950, 100, 45);  // should turn 90° by changing runtime.
    i += 1;
  }
}
void triangle() {
  // drives a triangle
  int i = 0;
  while (i <= 2) {  // do this three times.
    driveForward(3000, 100);
    driveCurve(1500, 100, 45);  // should turn 60° by changing runtime.
    i += 1;
  }
}
void hexagon() {
  // drives a hexagon.
  int i = 0;
  while (i <= 5) { // do this six times.
    driveForward(3000, 100);
    driveCurve(600, 100, 45);
    i += 1; 
  }
}
  
// detect the distance of a barrier and return the distance in cm.
// -1 is returned if no barrier is detected.
// use PIN 12 as connector for US1
int meassureDistance (int Pin) {
  activateSensor();
  uint32_t pulseTime = pulseIn (Pin, HIGH, 30000);
  if (pulseTime == 0)
  {
    return -1;
  }
  else
  {
    return pulseTime / 58;
  }

}  

void activateSensor() {
  // method to activate US1 according to the exercisesheet.
  pinMode(us1, OUTPUT);
  digitalWrite(us1, LOW);
  digitalWrite(us1, HIGH);
  delayMicroseconds(15);  // it says at least wait for 10µs, so we better wait for 15µs
  digitalWrite(us1, LOW);
  pinMode(us1, INPUT);
} 

void driveWithoutCollision() {
  while (true)
  {
    int currentValue = meassureDistance(us1);
    if (currentValue == -1)
    {
      // everything is fine here, no barrier detected
      // you could test here how fast in meters per secounds the robot drives
      // with speed value 100.
      // while meassureDistance == -1 no barrier in ca 5meter.
      driveForward(1000, 100);
      delay(1000);
    }
    if (currentValue > 100)
    {
      // a barrier comes in 1meter or less, so we have to slow down
      driveForward(500, 100);
      delay(500);
    }
    if (currentValue <= 100 && currentValue >=30)
    {
      driveForward(500, 75);
      delay(500);
    }
    if (currentValue < 30)
    {
      //better stop now completly, a barrier comes in less than 30cm
      driveForward(0, 0);
      // now check where we can continue to drive
      driveCurve(100, 20, -90);
      delay(100);
      driveCurve(200, 20, 90);
      delay(200);
    }
  }
}
