#include <Pixy2.h>
#include <Servo.h>

Pixy2 pixy;
Servo panServo;
Servo tiltServo;

const int panPin = 12;
const int tiltPin = 13;

void setup() {
  Serial.begin(115200);
  pixy.init();
  pixy.setLamp(1, 1); // Turn on Pixy2 lights
  panServo.attach(panPin);
  tiltServo.attach(tiltPin);
  panServo.write(90); // Center position
  tiltServo.write(90); // Center position
}

void loop() {
  int blocks = pixy.ccc.getBlocks();
  
  if (blocks) {
    for (int i = 0; i < blocks; i++) {
      int panPosition = map(pixy.ccc.blocks[0].m_x, 0, 319, 0, 180);
      int tiltPosition = map(pixy.ccc.blocks[0].m_y, 0, 199, 0, 180);
    
      panServo.write(panPosition);
      tiltServo.write(tiltPosition);
    
      Serial.print("Pan Position: ");
      Serial.print(panPosition);
      Serial.print(" | Tilt Position: ");
      Serial.println(tiltPosition);
    }
  }
  
  delay(20);
}