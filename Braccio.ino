#include <Arduino.h>
#include <Braccio.h>
#include <Servo.h>

Servo base;
Servo shoulder;
Servo elbow;
Servo wrist_rot;
Servo wrist_ver;
Servo gripper;

//const int numServos = 6; // Number of servo motors
//Servo servos[numServos]; // Array of servo objects
//int servoAngles[numServos]; // Array to store servo angles
//int servoLedPin[numServos -1] = {2, 4, 7, 8 ,13}; // Array of servo LED indicators
//int selectedServo = 0; // Currently selected servo (o o numServos -1)

const int basePin = 11;
const int shoulderPin = 10;
const int elbowPin = 9;
const int wristRotPin = 5;
const int wristVerPin = 6;
const int gripperPin = 3;

class Button {
public:
  Button(int pin, unsigned long debounceDelay = 50) : pin(pin), debounceDelay(debounceDelay) {
    pinMode(pin, INPUT);
  }
  
  bool isPressed() {
   if(millis() - lastDebounceTime > debounceDelay) {
     int buttonState = digitalRead(pin);
     if (buttonState != lastButtonState) {
       lastDebounceTime = millis();
       lastButtonState = buttonState;
       if (buttonState == HIGH) {
         return true;
       }
     }
   }
   return false;
  }
  
  bool isOn() {
    return digitalRead(pin);
  }
  
private:
  int pin;
  int lastButtonState = LOW;
  unsigned long lastDebounceTime = 0;
  unsigned long debounceDelay;
};

//class BraccioControl {
//public:
//  BraccioControl() {
    // Initialize all servo angles to 90 degrees
    //for (int i=0; i<numServos; i++) {
    //servoAngles[i] = 90;
    //}
//    servoAngles[0] = 0;
//    servoAngles[1] = 40;
//    servoAngles[2] = 180;
//    servoAngles[3] = 170;
//    servoAngles[4] = 0;
//    servoAngles[5] = 73;
//   }
  
//  void attachServos(int basePin, int shoulderPin, int elbowPin, int wristRotPin, int wristVerPin, int gripperPin) {
    // Attach servo objects to GPIO pins
//    servos[0].attach(basePin);
//    servos[1].attach(shoulderPin);
//    servos[2].attach(elbowPin);
//    servos[3].attach(wristRotPin);
//    servos[4].attach(wristVerPin);
//    servos[5].attach(gripperPin);
//  }
  
//  void selectNextServo() {
//    selectedServo = (selectedServo + 1) % numServos; // Cycle through servos
//    delay(200); // Debounce delay
//  }
  
//  void moveSelectedServo(int angle) {
//    servoAngles[selectedServo] = constrain(angle, 0, 180);
//    servos[selectedServo].write(servoAngles[selectedServo]);
//  }
  
//  int getSelectedServoAngle() {
//    return servoAngles[selectedServo];
//  }
  
//};

//BraccioControl tinkerkit;

class LED {
private:
  int pin;
  boolean isOn;
  
public:
  LED(int pinNumber) {
    pin = pinNumber;
    isOn = false;
    pinMode(pin, OUTPUT);
  }
  
  void turnOn() {
    digitalWrite(pin, HIGH);
    isOn = true;
  }
  
  void turnOff() {
    digitalWrite(pin, LOW);
    isOn = false;
  }
  
  boolean isLit() {
    return isOn;
  }  
};

Button redButton(15);
Button yellowButton(17);
Button greenButton(18);
Button blueButton(16);
Button whiteButton(19);

LED baseLED(2);
LED shoulderLED(4);
LED elbowLED(7);
LED wristVLED(8);
LED wristRLED(13);

int baseAngle = 0;
int shoulderAngle = 40;
int elbowAngle = 180;
int wristVerAngle = 170;
int wristRotAngle = 0;
int angle = 180;
  
void setup(){

  Serial.begin(9600);
  Braccio.begin();
  
//  tinkerkit.attachServos(basePin, shoulderPin, elbowPin, wristRotPin, wristVerPin, gripperPin);

//  for (int i=0; i<numServos-1; i++) {
//    pinMode(servoLedPin[i], OUTPUT);
//  }

//  Braccio.begin();

}

void loop(){
  
  if (yellowButton.isPressed()) {
//    int angle = tinkerkit.getSelectedServoAngle();
    Serial.println("yellow button pressed, angle = " + String(angle));
//    tinkerkit.selectNextServo();
//    Serial.println("selected servo = " + String(selectedServo));
//    Serial.println("servo angle = " + String(servoAngles[selectedServo]));
  }
  
  if (redButton.isPressed()) {
    base.write(80);
//    Serial.println("red button pressed, angle = " + String(angle));
//    angle += 5;
//    base.write(angle);
//    tinkerkit.moveSelectedServo(angle);
  } else if (greenButton.isPressed()) {
    base.write(180);
//    Serial.println("green button pressed, angle = " + String(angle));
//    angle -= 5;
//    base.write(angle);
//    tinkerkit.moveSelectedServo(angle);
  } 
  
  if (blueButton.isOn()) {
    if (angle<180) {
      angle++;
    }
    elbow.write(angle);
    delay(50);
  } 
  
  if (whiteButton.isOn()) {
    if (angle>0) {
      angle--;
    }
    elbow.write(angle);
    delay(50);
  } 

//  tinkerkit.moveSelectedServo(angle);
  
}  

