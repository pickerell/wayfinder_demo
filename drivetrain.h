#include <Servo.h>

Servo leftESC;
Servo rightESC;

const uint8_t leftESCPin = 4;
const uint8_t rightESCPin = 5;

float speed; //-1 to 1, positive is forwards
float rotation; //-1 to 1, positive is clockwise
// int leftSpeed;
// int rightSpeed;

void driveSetup() {
  leftESC.attach(leftESCPin);
  rightESC.attach(rightESCPin);
  leftESC.write(90);
  rightESC.write(90);
  speed = 0;
  rotation = 0;
  // leftSpeed = 0;
  // rightSpeed = 0;
  // delay(5000);
}

void drive(float throttle, float yaw, float wheelAccel, float wheelDecel) {
  if(!leftESC.attached() || !rightESC.attached()) {
    leftESC.attach(leftESCPin);
    rightESC.attach(rightESCPin);
  }

  speed += constrain(throttle - speed, -wheelAccel, wheelAccel);
  rotation += constrain(yaw - rotation, -wheelAccel, wheelAccel);

  int leftSpeed = (speed + rotation) * 90 + 90;
  int rightSpeed = (speed - rotation) * 90 + 90;
  // leftSpeed += constrain((throttle - leftSpeed) + yaw, -1000, 1000);
  // rightSpeed += constrain((throttle - rightSpeed) + yaw, -wheelAccel, wheelAccel);

  leftESC.write(leftSpeed);
  rightESC.write(rightSpeed);
  Serial.print(leftSpeed);
  Serial.print(", ");
  Serial.println(rightSpeed);
}

void park() {//test to see if i github right
  speed = 0;
  rotation = 0;
  // leftSpeed = 0;
  // rightSpeed = 0;
  leftESC.write(90);
  rightESC.write(90);
  if(leftESC.attached() || rightESC.attached()) {
    leftESC.detach();
    rightESC.detach();
  }
}