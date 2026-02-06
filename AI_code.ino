// RC receiver pins
const int STEERING_PIN = 11;   // Channel 1
const int THROTTLE_PIN = 12;   // Channel 2

// Left motor
const int LEFT_FWD  = 2;      // PWM
const int LEFT_REV  = 3;      // PWM
const int LEFT_EN   = 9;

// Right motor
const int RIGHT_FWD = 4;      // PWM
const int RIGHT_REV = 5;     // PWM
const int RIGHT_EN  = 10;

// ----- RC limits -----
const int RC_MIN = 1500;
const int RC_MID = 1750;
const int RC_MAX = 2100;
const int DEADZONE = 40;

void setup() {
  Serial.begin(9600);
  pinMode(STEERING_PIN, INPUT);
  pinMode(THROTTLE_PIN, INPUT);

  pinMode(LEFT_FWD, OUTPUT);
  pinMode(LEFT_REV, OUTPUT);
  pinMode(LEFT_EN, OUTPUT);

  pinMode(RIGHT_FWD, OUTPUT);
  pinMode(RIGHT_REV, OUTPUT);
  pinMode(RIGHT_EN, OUTPUT);

  // Enable motors
  digitalWrite(LEFT_EN, HIGH);
  digitalWrite(RIGHT_EN, HIGH);
}

void loop() {
  // Read RC signals
  int steeringPulse = pulseIn(STEERING_PIN, HIGH, 25000);
  int throttlePulse = pulseIn(THROTTLE_PIN, HIGH, 25000);

  // Safety check
  if (steeringPulse == 0 || throttlePulse == 0) {
    stopMotors();
    return;
  }

  // Convert to -255 to +255
  int throttle = map(throttlePulse, RC_MIN, RC_MAX, -255, 255);
  int steering = map(steeringPulse, RC_MIN, RC_MAX, -255, 255);
  Serial.print("Steering > ");
  Serial.println(throttle);
  Serial.print("Throttle > ");
  Serial.println(steering);
  // Deadzone
  if (abs(throttle) < DEADZONE) throttle = 0;
  if (abs(steering) < DEADZONE) steering = 0;

  // Differential mixing
  int leftSpeed  = throttle + steering;
  int rightSpeed = throttle - steering;

  leftSpeed  = constrain(leftSpeed,  -255, 255);
  rightSpeed = constrain(rightSpeed, -255, 255);

  setMotor(LEFT_FWD, LEFT_REV, leftSpeed);
  setMotor(RIGHT_FWD, RIGHT_REV, rightSpeed);


}

// ----- Motor control function -----
void setMotor(int fwdPin, int revPin, int speed) {
  if (speed > 0) {
    analogWrite(fwdPin, speed);
    analogWrite(revPin, 0);
  } 
  else if (speed < 0) {
    analogWrite(fwdPin, 0);
    analogWrite(revPin, -speed);
  } 
  else {
    analogWrite(fwdPin, 0);
    analogWrite(revPin, 0);
  }
}

void stopMotors() {
  analogWrite(LEFT_FWD, 0);
  analogWrite(LEFT_REV, 0);
  analogWrite(RIGHT_FWD, 0);
  analogWrite(RIGHT_REV, 0);
}
