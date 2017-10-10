/* 
The R.A.T. Sketch
By: Robin Matutina, Austin Dailey, and Tommy Dao
Date: 9 October 2017

This code is a adapted version of Jim Lindblom's Example Sketch.

Three useful functions are defined:
  setupArdumoto() -- Setup the Ardumoto Shield pins
  driveArdumoto([motor], [direction], [speed]) -- Drive [motor] 
      (0 for A, 1 for B) in [direction] (0 or 1) at a [speed]
      between 0 and 255. It will spin until told to stop.
  stopArdumoto([motor]) -- Stop driving [motor] (0 or 1).

  setupArdumoto() is called in the setup().
  The loop() demonstrates use of the motor driving functions.


 */ 


// Clockwise and counter-clockwise definitions.
// Depending on how you wired your motors, you may need to swap.
#define FORWARD  0
#define REVERSE 1

// Motor definitions to make life easier:
#define MOTOR_A 0
#define MOTOR_B 1

// Pin Assignments //
//Default pins:
#define DIRA 2 // Direction control for motor A
#define PWMA 3  // PWM control (speed) for motor A
#define DIRB 4 // Direction control for motor B
#define PWMB 11 // PWM control (speed) for motor B


#define trigPinA 13
#define echoPinA 12
#define trigPinB 9
#define echoPinB 8
#define trigPinC 7
#define echoPinC 6


void setup() {
  // put your setup code here, to run once:
  setupArdumoto(); // Set all pins as outputs
  Serial.begin (9600);
  pinMode(trigPinA, OUTPUT);
  pinMode(echoPinA, INPUT);
  pinMode(trigPinB, OUTPUT);
  pinMode(echoPinB, INPUT);
  pinMode(trigPinC, OUTPUT);
  pinMode(echoPinC, INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  long duration;
  float distance_A;
  float distance_B;
  float distance_C;

  digitalWrite(trigPinA, LOW);  // Added this line
  digitalWrite(trigPinB, LOW);  // Added this line
  digitalWrite(trigPinC, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPinA, HIGH);
  digitalWrite(trigPinB, HIGH);
  digitalWrite(trigPinC, HIGH);
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPinA, LOW);
  digitalWrite(trigPinB, LOW);
  digitalWrite(trigPinC, LOW);
  duration = pulseIn(echoPinA, HIGH);
  duration = pulseIn(echoPinB, HIGH);
  duration = pulseIn(echoPinC, HIGH);
  distance_A = (duration/2) / 29.1;
  distance_B = (duration/2) / 29.1;
  distance_C = (duration/2) / 29.1;

  Serial.print(distance_A);
  Serial.println(" cm (A)");
   Serial.print(distance_B);
  Serial.println(" cm (B)");
   Serial.print(distance_C);
  Serial.println(" cm (C)");
  
  delay(100);
  
  // Drive both
  driveArdumoto(MOTOR_A, FORWARD, 255);  // Motor A at max speed.
  driveArdumoto(MOTOR_B, FORWARD, 255);  // Motor B at max speed.
  delay(1000);  // Drive forward for a second

  // Right Turn
  if (distance_A < 5 && distance_B < 5) {
    // Now spin in place!
    driveArdumoto(MOTOR_A, FORWARD, 255);  // Motor A at max speed.
    driveArdumoto(MOTOR_B, REVERSE, 255);  // Motor B at max speed.
    delay(2000);  // Drive forward for a second
    stopArdumoto(MOTOR_A);  // STOP motor A 
    stopArdumoto(MOTOR_B);  // STOP motor B 
  } 
  // Left Turn
  if (distance_A < 5 && distance_C < 5) {
    // Now spin in place!
    driveArdumoto(MOTOR_A, REVERSE, 255);  // Motor A at max speed.
    driveArdumoto(MOTOR_B, FORWARD, 255);  // Motor B at max speed.
    delay(2000);  // Drive forward for a second
    stopArdumoto(MOTOR_B);  // STOP motor A 
    stopArdumoto(MOTOR_A);  // STOP motor B 
  } 
}

// driveArdumoto drives 'motor' in 'dir' direction at 'spd' speed
void driveArdumoto(byte motor, byte dir, byte spd)
{
  if (motor == MOTOR_A)
  {
    digitalWrite(DIRA, dir);
    analogWrite(PWMA, spd);
  }
  else if (motor == MOTOR_B)
  {
    digitalWrite(DIRB, dir);
    analogWrite(PWMB, spd);
  }  
}

// stopArdumoto makes a motor stop
void stopArdumoto(byte motor)
{
  driveArdumoto(motor, 0, 0);
}

// setupArdumoto initialize all pins
void setupArdumoto()
{
  // All pins should be setup as outputs:
  pinMode(PWMA, OUTPUT);
  pinMode(PWMB, OUTPUT);
  pinMode(DIRA, OUTPUT);
  pinMode(DIRB, OUTPUT);

  // Initialize all pins as low:
  digitalWrite(PWMA, LOW);
  digitalWrite(PWMB, LOW);
  digitalWrite(DIRA, LOW);
  digitalWrite(DIRB, LOW);
}
