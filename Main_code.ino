// ===== Motor pin definitions =====
// Left motor
const int LEFT_DIR1 = 2;
const int LEFT_DIR2 = 3;
const int LEFT_SPEED = 9;   // PWM pin




// Right motor
const int RIGHT_DIR1 = 4;
const int RIGHT_DIR2 = 5;
const int RIGHT_SPEED = 10; // PWM pin




void setup() {
  // Set all motor pins as outputs
  Serial.begin(9600);
  pinMode(LEFT_DIR1, OUTPUT);
  pinMode(LEFT_DIR2, OUTPUT);
  pinMode(LEFT_SPEED, OUTPUT);




  pinMode(RIGHT_DIR1, OUTPUT);
  pinMode(RIGHT_DIR2, OUTPUT);
  pinMode(RIGHT_SPEED, OUTPUT);




  // Move forward
  delay(1000);        // Start
  for (int i = 0;i < 151; i = i + 15){
    moveForward(i);   // speed (0–255)
    delay(200);
    Serial.print("Speed > ");
    Serial.println(i);
  }
  analogWrite(LEFT_SPEED, 150);
  analogWrite(RIGHT_SPEED, 75); // Moves left slowly




  // Set direction (forward)
  digitalWrite(LEFT_DIR1, LOW);
  digitalWrite(LEFT_DIR2, HIGH);
  //Forward




  digitalWrite(RIGHT_DIR1, LOW);
  digitalWrite(RIGHT_DIR2, HIGH);
  //Foward


  delay(3000);
  for (int i = 151;i > 0; i = i - 15){
    moveForward(i);   // speed (0–255)
    delay(200);
    Serial.print("Speed > ");
    Serial.println(i);
  }
  stopMotors();
  /*
  stopMotors();
  delay(1000);


  moveLeft(150);
  delay(1500);


  stopMotors();
  delay(1000);


  moveForward(150);
  delay(2000);


  stopMotors();
  delay(1000);


  moveRight(150);
  delay(1500);        // move for 3 seconds


  stopMotors();       // Stop the rover
  delay(1000);


  moveForward(150);
  delay(2000);


  stopMotors();      
  delay(1000);


  moveBackwards(150);
  delay(2000);


  stopMotors();   // End    
  delay(1000);
  */
}




void loop() {
  // Nothing here
  // Rover already did its job in setup()
}




// ===== Motor control functions =====






void moveForward(int speed) {
  // Set speed
  analogWrite(LEFT_SPEED, speed);
  analogWrite(RIGHT_SPEED, speed);




  // Set direction (forward)
  digitalWrite(LEFT_DIR1, LOW);
  digitalWrite(LEFT_DIR2, HIGH);
  //Forward




  digitalWrite(RIGHT_DIR1, LOW);
  digitalWrite(RIGHT_DIR2, HIGH);
  //Foward
}


void moveBackwards(int speed) {
  // Set speed
  analogWrite(LEFT_SPEED, speed);
  analogWrite(RIGHT_SPEED, speed);




  // Set direction (Backward)
  digitalWrite(LEFT_DIR1, HIGH);
  digitalWrite(LEFT_DIR2, LOW);
  //Backward




  digitalWrite(RIGHT_DIR1, HIGH);
  digitalWrite(RIGHT_DIR2, LOW);
  //Backward
}


void moveLeft(int speed) {
  // Set speed
  analogWrite(LEFT_SPEED, speed);
  analogWrite(RIGHT_SPEED, speed);




  // Set direction (forward)
  digitalWrite(LEFT_DIR1, LOW);
  digitalWrite(LEFT_DIR2, HIGH);
  //Forward




  digitalWrite(RIGHT_DIR1, HIGH);
  digitalWrite(RIGHT_DIR2, LOW);
  //Backward
}


void moveRight(int speed) {
  // Set speed
  analogWrite(LEFT_SPEED, speed);
  analogWrite(RIGHT_SPEED, speed);




  // Set direction (forward)
  digitalWrite(LEFT_DIR1, HIGH);
  digitalWrite(LEFT_DIR2, LOW);
  //Backward




  digitalWrite(RIGHT_DIR1, LOW);
  digitalWrite(RIGHT_DIR2, HIGH);
  //Forward
}


void stopMotors() {
  // Stop motor speed
  analogWrite(LEFT_SPEED, 0);
  analogWrite(RIGHT_SPEED, 0);




  // Disable direction pins
  digitalWrite(LEFT_DIR1, LOW);
  digitalWrite(LEFT_DIR2, LOW);




  digitalWrite(RIGHT_DIR1, LOW);
  digitalWrite(RIGHT_DIR2, LOW);
}
