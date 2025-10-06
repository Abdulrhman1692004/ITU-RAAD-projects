#include <PID_v1.h>
#include <Stepper.h>
#include "TimerOne.h"

// Variables for speed measurement and PID control
volatile unsigned int counter = 0;     // Counter for speed sensor interrupts


// Stepper motor configuration
const int stepsPerRevolution = 200;     // Steps per revolution of the stepper motor
Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11); // Stepper motor instance

double rotation = 0.0;           // Placeholder for PID input (not used in this example)
double actual_rotation = 0.0;          // Variable where PID output will be stored
double desired_speed = 4.0 * 9.54;        // Placeholder for PID setpoint (desired speed)
double kp = 2.0;              // Proportional gain
double ki = 5.0;              // Integral gain
double kd = 1.0;              // Derivative gain

PID myPID(&rotation, &actual_rotation, &desired_speed, kp, ki, kd, DIRECT); // PID controller instance

void docount() {
  counter++; // Increment counter on speed sensor interrupt
}

void timerIsr() {
  Timer1.detachInterrupt();  // Stop the timer interrupt
  rotation = counter / 20.0;  // Calculate rotations per second
  Serial.print("Motor Speed: ");
  Serial.print(rotation, 2); // Print speed (rotations per second) with 2 decimal places
  Serial.println(" RPM");
  counter = 0;                // Reset counter
  Timer1.attachInterrupt(timerIsr); // Re-attach the timer interrupt
}

void setup() {
  Serial.begin(9600);

  // Initialize stepper motor control
  myStepper.setSpeed(0); // Initially set motor speed to 0 RPM

  // Initialize PID controller
  myPID.SetMode(AUTOMATIC);  // Enable automatic control mode
  myPID.SetTunings(kp, ki, kd); // Set PID tuning parameters

  // Configure and start the timer for speed measurement (every 1 second)
  Timer1.initialize(1000000); // Timer interval (microseconds) for 1 second
  attachInterrupt(0, docount, RISING); // Attach interrupt to speed sensor input
  Timer1.attachInterrupt(timerIsr); // Attach timer ISR
}

void loop() {
  // Compute PID output based on current speed (rotation) and desired speed
  myPID.Compute();

  // Set the stepper motor speed based on PID output
  int stepper_speed = actual_rotation * stepsPerRevolution * 1.0 / 60.0; // Calculate steps per second
  myStepper.setSpeed(stepper_speed);

  // Perform one step to rotate the stepper motor continuously
  myStepper.step(stepsPerRevolution);

  // Add a delay to control the loop execution rate
  delay(100); // Adjust delay based on system response time
}
