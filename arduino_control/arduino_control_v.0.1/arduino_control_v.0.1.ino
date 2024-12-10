#include <Servo.h>
#include <Pixy2.h>

Pixy2 pixy;

Servo panServo;
Servo tiltServo;
Servo steeringServo;

const int panPin = 9;
const int tiltPin = 10;
const int motorPin = 3;
const int steeringPin = 5;
const int laserPin = 6;

const int panCenter = 100;
const int panRight = 10;
const int panLeft = 200;

const int tiltCenter = 180;
const int tiltUp = 90;

const int steerCenter = 90;
const int steerLeft = 5;
const int steerRight = 175;

const int centerWidth = pixy.frameWidth / 2;
const int centerHeight = pixy.frameHeight / 2;

int moveSpeed = 1;
int centerCounter = 0;
const int centerThreshold = 50; // Number of frames the object needs to be centered

bool turnRight = true;

void setup() {
  Serial.begin(9600);
  pixy.init();
  pixy.setLamp(1, 1);

  panServo.attach(panPin);
  tiltServo.attach(tiltPin);
  steeringServo.attach(steeringPin);
  pinMode(motorPin, OUTPUT);
  pinMode(laserPin, OUTPUT);
  
  panServo.write(panCenter);
  tiltServo.write(tiltCenter);
  steeringServo.write(steerCenter);
}

void loop() {
  pixy.ccc.getBlocks();
  
  if (pixy.ccc.numBlocks) {
    int x = pixy.ccc.blocks[0].m_x;
    int y = pixy.ccc.blocks[0].m_y;
    int blockWidth = pixy.ccc.blocks[0].m_width;
    
    int frameWidth = pixy.frameWidth;
    int frameHeight = pixy.frameHeight;

    int xDiff = abs(x - centerWidth);
    int yDiff = abs(y - centerHeight);

    if (xDiff > 130 || yDiff > 100) {
      moveSpeed = 3;
    } else if (xDiff > 100 || yDiff > 80) {
      moveSpeed = 1;
    }
    
    if (x < frameWidth / 3) {
      panServo.write(panServo.read() + moveSpeed);
      steeringServo.write(steeringServo.read() - moveSpeed);
      Serial.println("Moving left");
      centerCounter = 0;
    } else if (x > 2 * frameWidth / 3) {
      panServo.write(panServo.read() - moveSpeed);
      steeringServo.write(steeringServo.read() + moveSpeed);
      Serial.println("Moving right");
      centerCounter = 0;
    } else {
      centerCounter++;
    }
    
    if (y < frameHeight / 3) {
      tiltServo.write(tiltServo.read() - moveSpeed);
      Serial.println("Moving up");
      centerCounter = 0;
    } else if (y > 2 * frameHeight / 3) {
      tiltServo.write(tiltServo.read() + moveSpeed);
      Serial.println("Moving down");
      centerCounter = 0;
    } else {
      centerCounter++;
    }

    if (centerCounter >= centerThreshold) {
      digitalWrite(laserPin, HIGH);
    } else {
      digitalWrite(laserPin, LOW);
    }

    // motor control
    if (blockWidth < (0.1 * frameWidth)) {
      analogWrite(motorPin, 70);
    } else if (blockWidth < (0.2 * frameWidth)) {
      analogWrite(motorPin, 50);
    } else {
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
    tiltServo.write(150);
    if (turnRight) {
      panServo.write(panServo.read() + moveSpeed);
      if (panServo.read() >= 150) {
        turnRight = false;
      }
      Serial.println("Look right");
    } else {
      panServo.write(panServo.read() - moveSpeed);
      if (panServo.read() <= 30) {
        turnRight = true;
      }
      Serial.println("Look left");
    }
  }
  
  delay(20);
}