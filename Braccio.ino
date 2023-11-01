#include <Braccio.h>
#include <Servo.h>

const int numServos = 6; // Number of servo motors
Servo servos[numServos]; // Array of servo objects
int servoAngles[numServos]; // Array to store servo angles
int servoLedPin[numServos -1] = {2, 4, 7, 8 ,13}; // Array of servo LED indicators
int selectedServo = 0; // Currently selected servo (o o numServos -1)

const int redButtonPin = 15;
const int yellowButtonPin = 17;
const int greenButtonPin = 18;
const int blueButtonPin = 16;
const int whiteButtonPin = 19;

const int basePin = 11;
const int shoulderPin = 10;
const int elbowPin = 9;
const int wristRotPin = 5;
const int wristVerPin = 6;
const int gripperPin = 3;

const int baseLedPin = 2;
const int shoulderLedPin = 4;
const int elbowLedPin = 7;
const int wristvLedPin = 8;
const int wristrLedPin = 13;

class BraccioControl {
public:
  BraccioControl() {
    // Initialize all servo angles to 90 degrees
    //for (int i=0; i<numServos; i++) {
    //servoAngles[i] = 90;
    //}
    servoAngles[0] = 0;
    servoAngles[1] = 40;
    servoAngles[2] = 180;
    servoAngles[3] = 170;
    servoAngles[4] = 0;
    servoAngles[5] = 73;
   }
  
  void attachServos(int basePin, int shoulderPin, int elbowPin, int wristRotPin, int wristVerPin, int gripperPin) {
    // Attach servo objects to GPIO pins
    servos[0].attach(basePin);
    servos[1].attach(shoulderPin);
    servos[2].attach(elbowPin);
    servos[3].attach(wristRotPin);
    servos[4].attach(wristVerPin);
    servos[5].attach(gripperPin);
  }
  
  void selectNextServo() {
    selectedServo = (selectedServo + 1) % numServos; // Cycle through servos
    delay(200); // Debounce delay
  }
  
  void moveSelectedServo(int angle) {
    servoAngles[selectedServo] = constrain(angle, 0, 180);
    servos[selectedServo].write(servoAngles[selectedServo]);
  }
  
  int getSelectedServoAngle() {
    return servoAngles[selectedServo];
  }
  
};

//BraccioControl tinkerkit;

int motorSelector = 0;
int yellowButtonState = 0;
bool yellowButtonFlag = false;

Servo base;
Servo shoulder;
Servo elbow;
Servo wrist_rot;
Servo wrist_ver;
Servo gripper;

int baseDeg = 0;
int ShoulderDeg = 0;
int elbowDeg = 0;
int wristvDeg = 0;
int wristreDeg = 0;

void setup(){

//  pinMode(redButtonPin, INPUT);
//  pinMode(yellowButtonPin, INPUT);
//  pinMode(greenButtonPin, INPUT);
//  pinMode(blueButtonPin, INPUT);
//  pinMode(whiteButtonPin, INPUT);
//  
//  tinkerkit.attachServos(basePin, shoulderPin, elbowPin, wristRotPin, wristVerPin, gripperPin);
//
//  for (int i=0; i<numServos-1; i++) {
//    pinMode(servoLedPin[i], OUTPUT);
//  }

  pinMode(baseLedPin, OUTPUT);
  pinMode(shoulderLedPin, OUTPUT);
  pinMode(elbowLedPin, OUTPUT);
  pinMode(wristvLedPin, OUTPUT);
  pinMode(wristrLedPin, OUTPUT);

  Braccio.begin();

}

void loop(){
//  if (digitalRead(yellowButtonPin) == HIGH) {
//    tinkerkit.selectNextServo();
//  }
//
//  int angle = tinkerkit.getSelectedServoAngle();
//
//  if (digitalRead(redButtonPin) == HIGH) {
//    angle += 5;
//  } 
//  else if (digitalRead(greenButtonPin) == HIGH) {
//    angle -= 5;
//  }
//
//  tinkerkit.moveSelectedServo(angle);
//}  

  yellowButtonState = digitalRead(yellowButtonPin);

  if (yellowButtonState == HIGH && !yellowButtonFlag) {
    
    motorSelector++;
    yellowButtonFlag = true;
    
    if (motorSelector > 5) {
      motorSelector = 0;
    }
    
  } else if (yellowButtonState == LOW) {
    yellowButtonFlag = false;
  }
  
  switch (motorSelector) {
    case 0:
      digitalWrite(baseLedPin, LOW);
      digitalWrite(shoulderLedPin, LOW);
      digitalWrite(elbowLedPin, LOW);
      digitalWrite(wristvLedPin, LOW);
      digitalWrite(wristrLedPin, LOW);
      base.write(0);
      shoulder.write(40);
      elbow.write(180);
      wrist_ver.write(170);
      wrist_rot.write(0);
      gripper.write(73);
      break;
    case 1:
      digitalWrite(baseLedPin, HIGH);
      digitalWrite(shoulderLedPin, LOW);
      digitalWrite(elbowLedPin, LOW);
      digitalWrite(wristvLedPin, LOW);
      digitalWrite(wristrLedPin, LOW);
      base.write(90);
      break;
    case 2:
      digitalWrite(baseLedPin, LOW);
      digitalWrite(shoulderLedPin, HIGH);
      digitalWrite(elbowLedPin, LOW);
      digitalWrite(wristvLedPin, LOW);
      digitalWrite(wristrLedPin, LOW);
      base.write(-90);
      break;
    case 3:
      digitalWrite(baseLedPin, LOW);
      digitalWrite(shoulderLedPin, LOW);
      digitalWrite(elbowLedPin, HIGH);
      digitalWrite(wristvLedPin, LOW);
      digitalWrite(wristrLedPin, LOW);
      base.write(180);
      break;
    case 4:
      digitalWrite(baseLedPin, LOW);
      digitalWrite(shoulderLedPin, LOW);
      digitalWrite(elbowLedPin, LOW);
      digitalWrite(wristvLedPin, HIGH);
      digitalWrite(wristrLedPin, LOW);
      wrist_ver.write(90);
      break;
    case 5:
      digitalWrite(baseLedPin, LOW);
      digitalWrite(shoulderLedPin, LOW);
      digitalWrite(elbowLedPin, LOW);
      digitalWrite(wristvLedPin, LOW);
      digitalWrite(wristrLedPin, HIGH);
      break;
  }
      
//  Braccio.ServoMovement(20, 0, 40, 180, 170, 0, 73);
//  delay(1000);
//  Braccio.ServoMovement(20, 180, 165, 0, 0, 180, 10);
//  delay(1000);
//  delay(100);
}


