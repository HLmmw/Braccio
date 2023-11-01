#include <Arduino.h>
#include <Braccio.h>
#include <Servo.h>

const int numServos = 6; // Number of servo motors
Servo servos[numServos]; // Array of servo objects
int servoAngles[numServos]; // Array to store servo angles
int servoLedPin[numServos -1] = {2, 4, 7, 8 ,13}; // Array of servo LED indicators
int selectedServo = 0; // Currently selected servo (o o numServos -1)

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
  
private:
  int pin;
  int lastButtonState = LOW;
  unsigned long lastDebounceTime = 0;
  unsigned long debounceDelay;
};

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

BraccioControl tinkerkit;

Button redButton(15);
Button yellowButton(17);
Button greenButton(18);
Button blueButton(16);
Button whiteButton(19);

void setup(){

  Serial.begin(9600);
    
  tinkerkit.attachServos(basePin, shoulderPin, elbowPin, wristRotPin, wristVerPin, gripperPin);

  for (int i=0; i<numServos-1; i++) {
    pinMode(servoLedPin[i], OUTPUT);
  }

  pinMode(baseLedPin, OUTPUT);
  pinMode(shoulderLedPin, OUTPUT);
  pinMode(elbowLedPin, OUTPUT);
  pinMode(wristvLedPin, OUTPUT);
  pinMode(wristrLedPin, OUTPUT);

//  Braccio.begin();

}

void loop(){
  int angle = tinkerkit.getSelectedServoAngle();
  
  if (yellowButton.isPressed()) {
    Serial.println("yellow button pressed, angle = " + String(angle));
    tinkerkit.selectNextServo();
    Serial.println("selected servo = " + String(selectedServo));
    Serial.println("servo angle = " + String(servoAngles[selectedServo]));
  }
  
  if (redButton.isPressed()) {
    Serial.println("red button pressed, angle = " + String(angle));
    angle += 5;
//    tinkerkit.moveSelectedServo(angle);
  } 
  else if (greenButton.isPressed()) {
    Serial.println("green button pressed, angle = " + String(angle));
    angle -= 5;
//    tinkerkit.moveSelectedServo(angle);
  }

//  tinkerkit.moveSelectedServo(angle);
  
}  

