#include <Servo.h>
#include <Pixy2.h>
#include <SPI.h>

// init pan, tilt
Servo panServo;
Servo tiltServo;
const int panPin = 12;
const int tiltPin = 13;

// init pan limits
const int panMin = 0;
const int panWrite = 90; // 90 = Forward
const int panMax = 180;

// init tilt limits
const int tiltMin = 0;
const int tiltWrite = 90; // 90 = Forward
const int tiltMax = 180;

Pixy2 pixy;

void setup() {
  // setup servos
  panServo.attach(panPin); // 180 = Forward
  tiltServo.attach(tiltPin); // 180 = Forward, 90 = Up, 360 = Down
}

void loop() {
  // put your main code here, to run repeatedly:
  panServo.write(panWrite);
  tiltServo.write(tiltWrite);
}