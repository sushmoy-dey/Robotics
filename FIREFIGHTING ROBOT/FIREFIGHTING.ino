#include <Servo.h>

// L298N Motor Driver Pins (Left and Right wheels)
const int enA = 3;
const int in1 = 4;
const int in2 = 5;
const int in3 = 6;
const int in4 = 7; 
const int enB = 9;

// Relay Control Pin for Water Pump
const int pumpRelayPin = 8; 

// Flame Sensor Pins
const int leftFlamePin = A0;
const int rightFlamePin = A1;

// Servo Motor
Servo fireServo;
const int servoPin = 10;

void setup() {
  // Initialize motor control pins
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  // Initialize pump relay pin: Set HIGH first, then OUTPUT to prevent startup glitch
  digitalWrite(pumpRelayPin, HIGH);
  pinMode(pumpRelayPin, OUTPUT);
  digitalWrite(pumpRelayPin, HIGH); // Ensure relay starts in OFF state

  // Initialize flame sensor pins as inputs
  pinMode(leftFlamePin, INPUT);
  pinMode(rightFlamePin, INPUT);

  // Attach Servo
  fireServo.attach(servoPin);
  fireServo.write(90); // Center position
}

void loop() {
  int leftFlame = digitalRead(leftFlamePin);
  int rightFlame = digitalRead(rightFlamePin);

  // Flame sensors output LOW when a flame is detected
  if (leftFlame == LOW && rightFlame == LOW) {
    fireServo.write(90);
    moveForward(180);
    turnOnPump();
  } 
  else if (leftFlame == LOW && rightFlame == HIGH) {
    fireServo.write(30); 
    turnLeft(180);
    turnOnPump();
  } 
  else if (leftFlame == HIGH && rightFlame == LOW) {
    fireServo.write(150); 
    turnRight(180);
    turnOnPump();
  } 
  else {
    fireServo.write(90);
    stopRobot();
    turnOffPump();
  }
}

void moveForward(int speed) {
  analogWrite(enA, speed);
  analogWrite(enB, speed);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void turnLeft(int speed) {
  analogWrite(enA, speed);
  analogWrite(enB, speed);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void turnRight(int speed) {
  analogWrite(enA, speed);
  analogWrite(enB, speed);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

void turnOnPump() {
  digitalWrite(pumpRelayPin, LOW);  // Triggers relay ON
}

void turnOffPump() {
  digitalWrite(pumpRelayPin, HIGH); // Turns relay OFF
}

void stopRobot() {
  analogWrite(enA, 0);
  analogWrite(enB, 0);
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}