#include <Servo.h>
#include <Pixy2.h>
#include <PIDLoop.h>
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
PIDLoop panLoop(400, 0, 400, true);
PIDLop tiltLoop(500, 0, 500, true);

void setup() {
  // setup servos
  panServo.attach(panPin);
  tiltServo.attach(tiltPin);

  // setup pixy
  pixy.init();
  pixy.changeProg("color_connected_components");

  // serial start (for debug)
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  static int i = 0;
  int j;
  char buf[64];
  int32_t panOffset, tiltOffset;

  // get active blocks
  pixy.ccc.getBlocks();

  if (pixy.ccc.numBlocks)
  {        
    i++;
    
    if (i%60==0)
      Serial.println(i);   
    
    // calculate pan and tilt "errors" with respect to first object (blocks[0]), 
    // which is the biggest object (they are sorted by size).  
    panOffset = (int32_t)pixy.frameWidth/2 - (int32_t)pixy.ccc.blocks[0].m_x;
    tiltOffset = (int32_t)pixy.ccc.blocks[0].m_y - (int32_t)pixy.frameHeight/2;  
  
    // update loops
    panLoop.update(panOffset);
    tiltLoop.update(tiltOffset);
  
    // set pan and tilt servos  
    pixy.setServos(panLoop.m_command, tiltLoop.m_command);
   
#if 0 // for debugging
    sprintf(buf, "%ld %ld %ld %ld", rotateLoop.m_command, translateLoop.m_command, left, right);
    Serial.println(buf);   
#endif

  }  
  else // no object detected, go into reset state
  {
    panLoop.reset();
    tiltLoop.reset();
    pixy.setServos(panLoop.m_command, tiltLoop.m_command);
  }
}