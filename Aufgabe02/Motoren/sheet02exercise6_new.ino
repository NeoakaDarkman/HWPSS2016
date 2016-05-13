// S1 = circle
// S2 = triangle
// S3 = driveWithoutCollision
// S4 = square
// S5 = hexagon
  
  analogValue = analogRead(A0);
  if (analogValue < 100)  // S1
  {
    circle();
  }
  if (analogValue >=200 && analogValue <=300)  // S2
  {
    triangle();
  }
  if (analogValue >= 420 && analogValue <=530)  // S3
  {
    driveWithoutCollision();
  }
  if (analogValue >=600 && analogValue <=750)  // S4
  {
    square();
  }
  if (analogValue >=770 && analogValue <= 900)  // S5
  {
    hexagon();
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
  while ((digitalRead(Pin) == LOW) && (deltaSignalTest < 30000 ))  // wait 30ms for a response to come
  {
    endSignalTest = micros();
    deltaSignalTest = endSignalTest - stSignalTest;

    if (digitalRead(Pin) == HIGH)  // we got a response so break loop
    {
      uint32_t stTime = micros();  // startTime from the responsepulse
      gotSignal = true;
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
  while (true)
  {
    int currentValue = meassureDistance(12);
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
      driveForward(500, 50);
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
      // else add another 90°, than we got the roboter 180° turned from
      // where he stopped driving.
    }
  }
}
