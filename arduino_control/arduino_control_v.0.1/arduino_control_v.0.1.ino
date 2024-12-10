#include <Servo.h>
#include <Pixy2.h>

Pixy2 pixy;

Servo panServo;
Servo tiltServo;
Servo steeringServo;

const int panPin = 9;
const int tiltPin = 10;
const int motorPin = 11;
const int steeringPin = 12;
const int laserPin = 13;

const int panCenter = 100;
const int panRight = 10;
const int panLeft = 200;

const int tiltCenter = 180;
const int tiltUp = 90;

const int steerCenter = 90;
const int steerLeft = 10;
const int steerRight = 170;

const int centerWidth = pixy.frameWidth/2;
const int centerHeight = pixy.frameHeight/2;

int moveSpeed = 1;

void setup() {
  Serial.begin(9600);
  pixy.init();
  
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
    } else if (x > 2 * frameWidth / 3) {
      panServo.write(panServo.read() - moveSpeed);
      steeringServo.write(steeringServo.read() + moveSpeed);
      Serial.println("Moving right");
    }
    
    if (y < frameHeight / 3) {
      tiltServo.write(tiltServo.read() - moveSpeed);
      Serial.println("Moving up");
    } else if (y > 2 * frameHeight / 3) {
      tiltServo.write(tiltServo.read() + moveSpeed);
      Serial.println("Moving down");
    }
  }
  
  delay(20);
}