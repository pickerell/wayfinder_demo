#include "inputs.h"
#include "joystick.h"
#include "drivetrain.h"

float throttle = 0;
float yaw = 0;
float speedAccel = .5;
float speedDecel = 2;
float turnAccel = .5;
float turnDecel = 2;

void setup() {
  Serial.begin(115200);
  driveSetup();
  attachInputs();
  joystickSetup();
}

void loop() {
  throttle = -getInput(ch2);
  yaw = -getInput(ch1);
  
  if(active()) {
    drive(throttle, yaw, speedAccel, speedDecel, turnAccel, turnDecel);
    joystick(throttle, yaw);
  } else {
    park();
    joystick(0, 0);
  }
}

bool active() {
  if(connected(ch1) && connected(ch2) && connected(ch3)/*&& connected(ch4) && connected(ch5) && connected(ch6)*/ && signal[ch3] > 1100){
    return true;
  } else {
    return false;
  }
}
