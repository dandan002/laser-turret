#include <Pixy2.h>
#include <Servo.h>

Pixy2 pixy;
Servo panServo;
Servo tiltServo;

const int panPin = 9;
const int tiltPin = 10;

// PID constants
float Kp = 0.5;
float Ki = 0.1;
float Kd = 0.05;

// PID variables for pan
float panSetpoint = 90;
float panInput, panOutput;
float panPrevError = 0, panIntegral = 0;

// PID variables for tilt
float tiltSetpoint = 90;
float tiltInput, tiltOutput;
float tiltPrevError = 0, tiltIntegral = 0;

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
    panInput = map(pixy.ccc.blocks[0].m_x, 0, 319, 0, 180);
    tiltInput = map(pixy.ccc.blocks[0].m_y, 0, 199, 0, 180);
    
    // PID control for pan
    float panError = panSetpoint - panInput;
    panIntegral += panError;
    float panDerivative = panError - panPrevError;
    panOutput = Kp * panError + Ki * panIntegral + Kd * panDerivative;
    panPrevError = panError;
    
    // PID control for tilt
    float tiltError = tiltSetpoint - tiltInput;
    tiltIntegral += tiltError;
    float tiltDerivative = tiltError - tiltPrevError;
    tiltOutput = Kp * tiltError + Ki * tiltIntegral + Kd * tiltDerivative;
    tiltPrevError = tiltError;
    
    // Update servo positions
    panServo.write(constrain(panSetpoint + panOutput, 0, 180));
    tiltServo.write(constrain(tiltSetpoint + tiltOutput, 0, 180));
    
    Serial.print("Pan Position: ");
    Serial.print(panSetpoint + panOutput);
    Serial.print(" | Tilt Position: ");
    Serial.println(tiltSetpoint + tiltOutput);
    
    delay(100); // wait 100 ms
  }
  
  delay(20);
}