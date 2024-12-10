#include <Pixy2.h>
#include <PWMServo.h> // Include PWMServo library

Pixy2 pixy;
PWMServo panServo;
PWMServo tiltServo;

const int panPin = 9;  // Pan servo connected to pin 9
const int tiltPin = 10; // Tilt servo connected to pin 10

// Servo range limits
const int panMin = 2;
const int panMax = 180;
const int tiltMin = 10;
const int tiltMax = 270; // Adjusted to allow centering at 180

// Current positions (centered at 120 for pan and 180 for tilt)
int panPosition = 120; // Start centered
int tiltPosition = 180;

// Maximum change per update
const int maxDelta = 2; // Maximum change in degrees per update

// Dead zone
const int deadZone = 15; // Pixels

// Block detection tracking
const int consecutiveBlockThreshold = 5; // Frames
int consecutiveBlockCount = 0; // Count of consecutive block detections
bool trackingEnabled = false; // Flag to enable servo movement

// Timing variables
unsigned long lastUpdateTime = 0;
const unsigned long updateInterval = 10; // Update every 100ms

void setup() {
  Serial.begin(115200);
  pixy.init();
  pixy.setLamp(1, 1); // Turn on Pixy2 lights

  panServo.attach(panPin);
  tiltServo.attach(tiltPin);

  // Center servos
  panServo.write(panPosition);
  tiltServo.write(tiltPosition);

  Serial.println("System initialized. Servos centered.");
  delay(1000); // Allow time for servos to center
}

void loop() {
  int blocks = pixy.ccc.getBlocks(); // Get blocks from Pixy2

  if (blocks) {
    // Increment the consecutive block count
    consecutiveBlockCount++;

    // Enable tracking if the threshold is met
    if (consecutiveBlockCount >= consecutiveBlockThreshold) {
      trackingEnabled = true;
    }

    if (trackingEnabled) {
      // Use the largest detected block
      int blockX = pixy.ccc.blocks[0].m_x;
      int blockY = pixy.ccc.blocks[0].m_y;

      // Calculate errors
      int panError = abs(160 - blockX); // Pixy's center X
      int tiltError = abs(100 - blockY); // Pixy's center Y

      // Dead zone logic
      if (panError < deadZone || tiltError < deadZone) {
        Serial.println("Block within dead zone, no movement.");
        return;
      }

      // Map block coordinates to servo positions
      int targetPanPosition = map(blockX, 0, 319, panMax, panMin);
      int targetTiltPosition = map(blockY, 0, 199, tiltMin, tiltMax);

      // Constrain the new positions to servo limits
      targetPanPosition = constrain(targetPanPosition, panMin, panMax);
      targetTiltPosition = constrain(targetTiltPosition, tiltMin, tiltMax);

      // Calculate new positions with limited movement
      if (targetPanPosition > panPosition) {
        panPosition += min(maxDelta, targetPanPosition - panPosition);
      } else if (targetPanPosition < panPosition) {
        panPosition -= min(maxDelta, panPosition - targetPanPosition);
      }

      if (targetTiltPosition > tiltPosition) {
        tiltPosition += min(maxDelta, targetTiltPosition - tiltPosition);
      } else if (targetTiltPosition < tiltPosition) {
        tiltPosition -= min(maxDelta, tiltPosition - targetTiltPosition);
      }

      // Update servos only if the time interval has passed
      unsigned long currentTime = millis();
      if (currentTime - lastUpdateTime >= updateInterval) {
        panServo.write(panPosition);
        tiltServo.write(tiltPosition);

        // Debug output
        Serial.print("Block Found | X: ");
        Serial.print(blockX);
        Serial.print(" Y: ");
        Serial.print(blockY);
        Serial.print(" | Pan: ");
        Serial.print(panPosition);
        Serial.print(" | Tilt: ");
        Serial.println(tiltPosition);

        lastUpdateTime = currentTime; // Update the last update time
      }
    } else {
      Serial.println("Block detected but tracking not enabled yet.");
    }
  } else {
    // Reset consecutive block count and disable tracking
    consecutiveBlockCount = 0;
    trackingEnabled = false;

    Serial.println("No block detected.");
  }

  delay(20); // Small delay for stability
}
