#include <Servo.h>
#include <Pixy2.h>

Pixy2 pixy;

Servo panServo;
Servo tiltServo;
Servo steeringServo;

const int panPin = 9;
const int tiltPin = 10;
const int motorPin = 12;
const int steeringPin = 11;

const int panCenter = 100;
const int panLeft = 10;
const int panRight = 200;

const int tiltCenter = 180;
const int tiltUp = 90;

void setup() {
  Serial.begin(9600);
  pixy.init();
  
  panServo.attach(panPin);
  tiltServo.attach(tiltPin);
  steeringServo.attach(steeringPin);
  
  pinMode(motorPin, OUTPUT);
  
  panServo.write(panCenter);
  tiltServo.write(tiltCenter);
}

void loop() {
  pixy.ccc.getBlocks();
  
  if (pixy.ccc.numBlocks) {
    int x = pixy.ccc.blocks[0].m_x;
    int y = pixy.ccc.blocks[0].m_y;
    
    int panPosition = map(x, 0, 319, panLeft, panRight);
    int tiltPosition = map(y, 0, 199, tiltUp, tiltCenter);
    
    panServo.write(panPosition/5);
    tiltServo.write(tiltPosition/5);
    
    int steeringPosition = map(x, 0, 319, panLeft, panRight);
    steeringServo.write(steeringPosition);
    
    digitalWrite(motorPin, HIGH); // Move forward
  } else {
    digitalWrite(motorPin, LOW); // Stop
  }
  
  delay(20);
}