#include <Servo.h>

// init pan, tilt
Servo panServo;
Servo tiltServo;

// TEST VARS
int tiltWrite = 270;
int panWrite = 180;

void setup() {
  // setup servos
  panServo.attach(12); // 180 = Forward
  tiltServo.attach(13); // 270 = Forward, 90 = Up, 360 = Down
}

void loop() {
  // put your main code here, to run repeatedly:
  panServo.write(panWrite);
  tiltServo.write(tiltWrite);
}