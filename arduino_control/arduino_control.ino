#include <Servo.h>

// init pan, tilt
Servo panServo;
Servo tiltServo;

void setup() {
  // setup servos
  panServo.attach(12);
  tiltServo.attach(13);
}

void loop() {
  // put your main code here, to run repeatedly:
  panServo.write(50);
}
