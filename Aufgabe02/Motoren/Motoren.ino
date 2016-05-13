//global
#include <LiquidCrystal.h>

int analogPinValue;
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
  //pinMode(us1, INPUT);
  lcd.begin(20,4);
}

void loop() {
  driveForward(2000, 100);
  delay(5000);
  int cm = meassureDistance(us1);
  lcd.clear();
  lcd.print(cm);
  delay(5000);
  circle();
  delay(20000);
  square();
  delay(20000);
  triangle();
  delay(20000);
  hexagon();
  delay(20000);
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
      analogWrite(11, spd); 
      // Motor A always forward
      digitalWrite(10, LOW);
      
      if (str == 0){
        driveForward(runtime, spd);
        }    
      
      else if(str == 45){
        digitalWrite(6, LOW);
        digitalWrite(9, LOW);
        }
      else if(str > 45){
        analogWrite(6, spB);// motor B backwards
        digitalWrite(9, LOW);
        }
      // motor B forward
      else{
        analogWrite(9, spF);
        digitalWrite(6, LOW);
      }
  }
  else{
     sp =  spd * (45 - str)/45;
    int spB1 = (int)sp;
     sp = spd * (str + 45)/45;
    int spF1 = (int)sp;

    analogWrite(9, spd);
    // Motor B always forward
    digitalWrite(6, LOW);
    if(str > -44){
      if (str == -45){
        digitalWrite(11, LOW);
        digitalWrite(10, LOW);
        }
      else{
        analogWrite(11, spB1);
        digitalWrite(10, LOW);
      }
    }
     // motor A forward
    else{
      analogWrite(10, spF1);
      digitalWrite(11, LOW);
    }
  }
    delay(runtime);
  }

  void circle() {
  // drives a circle
  driveCurve(5000, 100, 40);
}
void square(){
  // drives a square
  int i = 0;
  while (i <= 3 ) {  // do this four times.
    driveForward(3000, 100);
    driveCurve(675, 100, 90);  // should turn 90° by changing runtime.
    i += 1;
  }
}
void triangle() {
  // drives a triangle
  int i = 0;
  while (i <= 2) {  // do this three times.
    driveForward(3000, 100);
    driveCurve(900, 100, 90);  // should turn 60° by changing runtime.
    i += 1;
  }
}
void hexagon() {
  // drives a hexagon.
  int i = 0;
  while (i <= 5) { // do this six times.
    driveForward(3000, 100);
    driveCurve(450, 100, 90);
    i += 1; 
  }
}
  
// detect the distance of a barrier and return the distance in cm.
// -1 is returned if no barrier is detected.
// use PIN 12 as connector for US1
int meassureDistance (int Pin) {
  activateSensor();
  //
  boolean gotSignal = false;
  uint32_t stSignalTest = micros();
  uint32_t endSignalTest = micros();
  uint32_t endTime;
  uint32_t stTime;
  uint32_t deltaSignalTest = endSignalTest - stSignalTest;  // to qualify if we waited allready 30ms and got no signal
  while ((digitalRead(Pin) == LOW) || (deltaSignalTest < 30000 ))  // wait 30ms for a response to come
  {
    endSignalTest = micros();
    deltaSignalTest = endSignalTest - stSignalTest;
    if (digitalRead(Pin) == HIGH)  // we got a response so break loop
    {
      uint32_t stTime = micros();  // startTime from the responsepulse
      gotSignal = true;
      deltaSignalTest = 30000;  // to break while loop
    }
  }
  if (gotSignal == false)
  {
    return -1;
  }
  else
  {
  while (digitalRead(Pin) == HIGH)
  {
    if (digitalRead(Pin) == LOW)
    {
      uint32_t endTime = micros();
    }
  }
  uint32_t distance = (endTime -stTime) / 58;
  return distance;
  }
}  
  
//  int starttime = micros();
//  while (digitalRead(Pin) == HIGH)
//  {
//    continue;
//  }
//  int endtime = micros();
//  uint32_t impulseTime = endtime-starttime;
//  if (impulseTime == 0) // no barrier detected
//  {
//    return -1;
//  }
//  else 
//  {
//    uint32_t distance = (impulseTime/58);
//    return distance;
void activateSensor() {
  // method to activate US1 according to the exercisesheet.
  pinMode(12, OUTPUT);
  digitalWrite(12, LOW);
  digitalWrite(12, HIGH);
  delayMicroseconds(15);  // it says at least wait for 10µs, so we better wait for 15µs
  digitalWrite(12, LOW);
  pinMode(12, INPUT);
} 

void driveWithoutCollision() {
  while (meassureDistance(us1) == -1)
  {
    // everything is fine here, no barrier detected
    // you could test here how fast in meters per secounds the robot drives
    // with speed value 100.
    // while meassureDistance == -1 no barrier in ca 5meter.
    driveForward(1000, 100);
  }
  while (meassureDistance(us1) > 100)
  {
    // a barrier comes in 1meter or less, so we have to slow down
    driveForward(500, 50);
  }
  while (meassureDistance(us1) < 30)
  {
    //better stop now completly, a barrier comes in less than 30cm
    driveForward(0, 0);
    // now check where we can continue to drive
    driveCurve(100, 20, -90);
    driveCurve(200, 20, 90);
    // else add another 90°, than we got the roboter 180° turned from
    // where he stopped driving.
  }
}
