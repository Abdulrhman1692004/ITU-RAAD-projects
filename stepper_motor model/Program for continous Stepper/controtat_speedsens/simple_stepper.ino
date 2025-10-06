#include <Stepper.h>
const int stepsPerRevolution = 100;     // Steps per revolution of the stepper motor
Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11); // Stepper motor instance 
/*
IN1: 8
IN2: 9
IN3: 10
IN4: 11
Try connecting both the arduino and the stepper to an external power source

*/
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);

  // Initialize stepper motor control
  myStepper.setSpeed(200); // Initially set motor speed to 0 RPM
}

void loop() {
  // put your main code here, to run repeatedly:

  // Perform one step to rotate the stepper motor continuously
  myStepper.step(stepsPerRevolution);
}