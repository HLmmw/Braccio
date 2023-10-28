#include <Braccio.h>
#include <Servo.h>

Servo base;
Servo shoulder;
Servo elbow;
Servo wrist_rot;
Servo wrist_ver;
Servo gripper;

void setup(){
  Braccio.begin();
}

void loop(){
  Braccio.ServoMovement(20, 0, 15, 180, 170, 0, 73);
  delay(1000);
  Braccio.ServoMovement(20, 180, 165, 0, 0, 180, 10);
  delay(1000);
}

