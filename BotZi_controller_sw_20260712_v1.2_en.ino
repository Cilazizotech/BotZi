/**************************************/
// BOTZI 2026 Controller software v1.2
// Author: Zilahi, Zoltán
/**************************************/
#include <Servo.h> // Include the standard library required for controlling servo motors

// Create the 4 servo motor objects (give them names)
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;

// Specifying the analog pins for the joysticks on the Arduino
const int joy1X = A3; // Joystick 1 X-axis (horizontal movement)
const int joy1Y = A2; // Joystick 1 Y-axis (vertical movement)
const int joy2X = A1; // Joystick 2 X-axis
const int joy2Y = A0; // Joystick 2 Y-axis

// Specifying which digital pins the servo motors are connected to
const int servo1Pin = 5;
const int servo2Pin = 4;
const int servo3Pin = 3;
const int servo4Pin = 2;

// Store the current and last positions of the servos in degrees (starting all in the middle: 90 degrees)
int currentPos1 = 90;
int currentPos2 = 90;
int currentPos3 = 90;
int currentPos4 = 90;
int lastPos1 = 90;
int lastPos2 = 90;
int lastPos3 = 90;
int lastPos4 = 90;

// Dead Zone setting: if the joystick is only slightly flicked, or doesn't return exactly to the center by itself, 
// this safety margin prevents the robotic arm from twitching uncontrollably.
const int deadZone = 250; 

// Set movement speeds and delay times for smooth motion
const int stepSize = 1;               // How many degrees the motor should turn in one step
const int servoDelayTime = 14;         // General delay in ms (smoothest between 10 and 20)
const int servoGripperDelayTime = 10;  // Speed of the gripper servo
const int servoArm3DelayTime = 16;     // Speed of arm servo number 3
unsigned int servoGriperMoves = 0;     // Monitors if the gripper is currently moving
unsigned int servoArm3Moves = 0;       // Monitors if arm 3 is currently moving

unsigned long lastMoveTime4 = 0; // Timer to turn off the gripper motor (so it doesn't buzz unnecessarily)
bool isAttached4 = false;        // Monitors if servo 4 is currently receiving power/signal

// If the joystick works exactly opposite to what you want, this line needs to be commented out or modified!
#define DIRECTION_ORIGINAL

void setup() {
  // Start the system and connect the servos in the code with the physical pins
  delay(500); // Wait half a second for the power supply to stabilize at startup
  
  servo1.attach(servo1Pin);
  delay(200); // Keep short pauses between turning on the motors to avoid sudden load on the power supply
  servo2.attach(servo2Pin);
  delay(200);
  servo3.attach(servo3Pin);
  delay(200);
  servo4.attach(servo4Pin);

  // Serial.begin(9600); // If you want to test on the computer, you can enable the debugging monitor here
}

void loop() {
  // Read the current position of the joysticks (they return a value between 0 and 1023)
  int joy1XVal = analogRead(joy1X);
  int joy1YVal = analogRead(joy1Y);
  int joy2XVal = analogRead(joy2X);
  int joy2YVal = analogRead(joy2Y);

  // Re-calculate (map) the 0-1023 joystick signal to the 0-180 degree range understandable by the servos
#ifdef DIRECTION_ORIGINAL  
// **********************************************************************************
// Some Arduino Nano boards interpret directions differently. This is the default direction setting:
   int targetPos1 = map(joy1YVal, 0, 1023, 1, 179);
   int targetPos2 = map(joy1XVal, 0, 1023, 175, 20 );
// *************************************************** If the arm moves opposite to the joystick, use the #else section below!
#else
   int targetPos1 = map(joy1YVal, 0, 1023, 179, 1);
   int targetPos2 = map(joy1XVal, 0, 1023, 20, 175 );
// *********************************************************************************
#endif
   
  int targetPos3 = map(joy2XVal, 0, 1023, 175, 1);
  int targetPos4 = map(joy2YVal, 0, 1023, 30 , 140); // Opening and closing angle limits of the gripper in degrees

  // --- MOVING THE SERVOS ---
  // Check if the joystick has moved away from the center position (512) more than the deadZone

  // Servo 1 movement block
  if (abs(joy1YVal - 512) > deadZone) {
    if (currentPos1 < targetPos1) currentPos1 += stepSize;      // If our angle is smaller than the target, increase it
    else if (currentPos1 > targetPos1) currentPos1 -= stepSize; // If larger, decrease it
    if(currentPos1 != lastPos1) {
      servo1.write(currentPos1); // Send the new position to the servo
    }
    lastPos1 = currentPos1; // Save where we stood last time
  }

  // Servo 2 movement block
  if (abs(joy1XVal - 512) > deadZone) {
    if (currentPos2 < targetPos2) currentPos2 += stepSize;
    else if (currentPos2 > targetPos2) currentPos2 -= stepSize;
    if(currentPos2 != lastPos2) {
      servo2.write(currentPos2);
    }
    lastPos2 = currentPos2;
  }

  // Servo 3 movement block
  if (abs(joy2XVal - 512) > deadZone) {
    if (currentPos3 < targetPos3) currentPos3 += stepSize;
    else if (currentPos3 > targetPos3) currentPos3 -= stepSize;
    if(currentPos3 != lastPos3) {
      servoArm3Moves = 1; // Indicate to the program that arm 3 is currently moving
      servo3.write(currentPos3);
    }
    lastPos3 = currentPos3;
  }

  // Servo 4 (gripper) movement block
  if (abs(joy2YVal - 512) > deadZone) {
    if (currentPos4 < targetPos4) currentPos4 += stepSize;
    else if (currentPos4 > targetPos4) currentPos4 -= stepSize;
    if(currentPos4 != lastPos4) {
      servoGriperMoves = 1; // Indicate that the gripper is moving

      // If the gripper servo was disconnected (sleeping), we now reactivate it and power it up
      if (!isAttached4) {
          servo4.attach(servo4Pin); 
          isAttached4 = true;
      }

      servo4.write(currentPos4);
      lastMoveTime4 = millis(); // Save the exact time of movement for the automatic shut-off
    }
    lastPos4 = currentPos4;
  }

  // You could print the positions here to the computer screen for testing:
  /*Serial.print("Servo1: "); Serial.print(currentPos1);
  Serial.print(" Servo2: "); Serial.print(currentPos2);
  Serial.print(" Servo3: "); Serial.print(currentPos3);
  Serial.print(" Servo4: "); Serial.println(currentPos4);
  */

  // Manage pauses and timings to keep the robotic arm movement continuous and smooth, rather than twitchy
  if(servoArm3Moves) {
    servoArm3Moves = 0;
    delay(servoArm3DelayTime); // Special wait after the movement of arm 3
  }
  else {
    delay(servoDelayTime); // General short pause between steps
  }

  // AUTOMATIC SHUT-OFF: 
  // If the gripper motor is not moving but is turned on, it might constantly buzz/heat up due to the holding current.
  // If 500 milliseconds (half a second) have passed since the last movement, we turn off its control (resting mode).
  if (isAttached4 && (millis() - lastMoveTime4 > 500)) {
      servo4.detach(); // Disconnect
      isAttached4 = false;
  }  
}