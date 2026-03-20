// ===== Receiver Pins =====
const int throttlePin = 12;
const int steeringPin = 11;

// Emergency Stop Pin
const int stopPin = 7;

// ===== Motor Driver Pins =====
// Left Motor
const int IN1 = 2;
const int IN2 = 3;
const int ENA = 9;

// Right Motor
const int IN3 = 4;
const int IN4 = 5;
const int ENB = 10;

// ===== Variables =====
int throttle = 0;
int steering = 0;

int leftTarget = 0;
int rightTarget = 0;

int leftSpeed = 0;
int rightSpeed = 0;

// Smooth ramp speed (higher = faster response)
int rampStep = 15;

void setup() {
  pinMode(throttlePin, INPUT);
  pinMode(steeringPin, INPUT);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENA, OUTPUT);

  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  // ===== Read Receiver Signals =====
  int throttlePulse = pulseIn(throttlePin, HIGH, 25000);
  int steeringPulse = pulseIn(steeringPin, HIGH, 25000);
  int stopPulse = pulseIn(stopPin, HIGH, 25000);

  Serial.print("Steering > ");
  Serial.println(steeringPulse);
  Serial.print("Throttle > ");
  Serial.println(throttlePulse);
  Serial.print("stopPulse > ");
  Serial.println(stopPulse);

  // Safety check (if signal lost)
  if (throttlePulse == 0 || steeringPulse == 0) {
    throttle = 0;
    steering = 0;
  } else {
    // Convert pulse (1000–2000) to -255 to 255
    throttle = map(throttlePulse, 980, 2120, -255, 255);
    steering = map(steeringPulse, 980, 2120, -255, 255);
  }

  // Deadzone (prevents jitter)
  if (abs(throttle) < 20) throttle = 0;
  if (abs(steering) < 20) steering = 0;

  //Constrain Values
  if (throttle > 255) throttle = 254;
  if (steering > 255) steering = 254;
  if (throttle < -255) throttle = -254;
  if (steering < -255) steering = -254;


  // ===== Differential Mixing =====
  leftTarget  = throttle + steering;
  rightTarget = throttle - steering;

  //Constrain Values
  if(leftTarget > 255) leftSpeed = 254;
  if(leftTarget < -255) leftSpeed = -254;
  if(rightTarget > 255) rightSpeed = 254;
  if(rightTarget < -255) rightSpeed = -254;

  // ===== Smooth Acceleration =====
  leftSpeed = ramp(leftSpeed, leftTarget);
  rightSpeed = ramp(rightSpeed, rightTarget);

  //Constrain Values
  if(leftSpeed > 255) leftSpeed = 254;
  if(leftSpeed < -255) leftSpeed = -254;
  if(rightSpeed > 255) rightSpeed = 254;
  if(rightSpeed < -255) rightSpeed = -254;

  // ===== Drive Motors =====
  if(stopPulse <= 2000){
    setMotor(ENA, IN1, IN2, leftSpeed);
    setMotor(ENB, IN3, IN4, rightSpeed);
  }else{
    setMotor(ENA, IN1, IN2, 0);
    setMotor(ENB, IN3, IN4, 0);
    leftSpeed = 0;
    rightSpeed = 0;
  }


  delay(20); // small loop delay
}

// ===== Smooth Ramp Function =====
int ramp(int current, int target) {
  if (current < target) {
    current += rampStep;
    if (current > target) current = target;
  } else if (current > target) {
    current -= rampStep;
    if (current < target) current = target;
  }
  return current;
}

// ===== Motor Control Function =====
void setMotor(int pwmPin, int in1, int in2, int speed) {
  if (speed > 0) {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    analogWrite(pwmPin, speed);
  } 
  else if (speed < 0) {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    analogWrite(pwmPin, -speed);
  } 
  else {
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    analogWrite(pwmPin, 0);
  }
}
