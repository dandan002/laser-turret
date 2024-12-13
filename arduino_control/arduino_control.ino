#include <Servo.h>
#include <Pixy2.h>

Pixy2 pixy;

// initialize servos
Servo panServo;
Servo tiltServo;
Servo steeringServo;

// define pins
const int panPin = 9;
const int tiltPin = 10;
const int motorPin = 3;
const int steeringPin = 5;
const int laserPin = 6;

// define default servo positions (pan)
const int panCenter = 100;
const int panRight = 10;
const int panLeft = 200;

// define default servo positions (tilt)
const int tiltCenter = 180;
const int tiltUp = 90;

// define default servo positions (steering)
const int steerCenter = 90;
const int steerLeft = 5;
const int steerRight = 175;

// define center of the frame
const int centerWidth = pixy.frameWidth / 2;
const int centerHeight = pixy.frameHeight / 2;

// get frame dimensions
int frameWidth = pixy.frameWidth;
int frameHeight = pixy.frameHeight;

// set initial movement speed, locking mechanism
int moveSpeed = 1;
int centerCounter = 0;
const int centerThreshold = 50; // # of frames to lock target

// set initial seeking direction
bool turnRight = true;

void setup() {
  // initialize pixy, serial communication
  Serial.begin(9600);
  pixy.init();
  pixy.setLamp(1, 1);

  // initialize servos
  panServo.attach(panPin);
  tiltServo.attach(tiltPin);
  steeringServo.attach(steeringPin);
  pinMode(motorPin, OUTPUT);
  pinMode(laserPin, OUTPUT);
  
  // set initial servo positions
  panServo.write(panCenter);
  tiltServo.write(tiltCenter);
  steeringServo.write(steerCenter);
}

void loop() {
  pixy.ccc.getBlocks();
  
  // if object found
  if (pixy.ccc.numBlocks) {
    // get object position + width
    int x = pixy.ccc.blocks[0].m_x;
    int y = pixy.ccc.blocks[0].m_y;
    int blockWidth = pixy.ccc.blocks[0].m_width;

    // calculate difference from center
    int xDiff = abs(x - centerWidth);
    int yDiff = abs(y - centerHeight);

    // adjust movement speed based on distance from center
    if (xDiff > 130 || yDiff > 100) {
      moveSpeed = 3;
    } else if (xDiff > 100 || yDiff > 80) {
      moveSpeed = 1;
    }
    
    // adjust servos based on object position
    if (x < frameWidth / 3) {
      // object is left
      panServo.write(panServo.read() + moveSpeed);
      steeringServo.write(steeringServo.read() - moveSpeed);
      Serial.println("Moving left");
      centerCounter = 0;
    } else if (x > 2 * frameWidth / 3) {
      // object is right
      panServo.write(panServo.read() - moveSpeed);
      steeringServo.write(steeringServo.read() + moveSpeed);
      Serial.println("Moving right");
      centerCounter = 0;
    } else {
      // center
      centerCounter++;
    }
    
    if (y < frameHeight / 3) {
      // object is up
      tiltServo.write(tiltServo.read() - moveSpeed);
      Serial.println("Moving up");
      centerCounter = 0;
    } else if (y > 2 * frameHeight / 3) {
      // object is down
      tiltServo.write(tiltServo.read() + moveSpeed);
      Serial.println("Moving down");
      centerCounter = 0;
    } else {
      // center
      centerCounter++;
    }

    // laser control
    if (centerCounter >= centerThreshold) {
      // centered for a while (target locked)
      digitalWrite(laserPin, HIGH);
    } else {
      // not centered (off)
      digitalWrite(laserPin, LOW);
    }

    // motor control
    if (blockWidth < (0.1 * frameWidth)) {
      // object is far away
      analogWrite(motorPin, 70);
    } else if (blockWidth < (0.2 * frameWidth)) {
      // object is close
      analogWrite(motorPin, 50);
    } else {
      // object is very close
      analogWrite(motorPin, 0);
    }
  } else {
    // IF NOT FOUND

    // Turn laser off
    digitalWrite(laserPin, LOW);
    centerCounter = 0;

    // Turn off motor
    analogWrite(motorPin, 0);

    // Look around
    tiltServo.write(150); // look a bit upwards
    if (turnRight) {
      // turn to the right
      panServo.write(panServo.read() + moveSpeed);
      if (panServo.read() >= 150) {
        turnRight = false;
      }
      Serial.println("Look right");
    } else {
      // turn to the left
      panServo.write(panServo.read() - moveSpeed);
      if (panServo.read() <= 30) {
        turnRight = true;
      }
      Serial.println("Look left");
    }
  }
  
  delay(20);
}