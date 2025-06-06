#include <Servo.h>
String inputString; 

Servo left_right;
Servo up_down;

const int left_right_pin = 2;
const int up_down_pin = 3;

void setup()
{
  left_right.attach(left_right_pin); // attach servo to pin 2
  up_down.attach(up_down_pin); // attach servo to pin 3
  Serial.begin(9600);
}

void loop()
{
  while(Serial.available())
  {
    inputString = Serial.readStringUntil('\r');
    Serial.println(inputString);
    int x_axis = inputString.substring(0, inputString.indexOf(',')).toInt();
    int y_axis = inputString.substring(inputString.indexOf(',') + 1).toInt();

    int y = map(y_axis, 0, 1080, 180, 0);
    int x = map(x_axis, 0, 1920, 180, 0);

    left_right.write(x);
    up_down.write(y);
    
    // Print the parsed values
    Serial.print("First Integer: ");
    Serial.println(x);
    Serial.print("Second Integer: ");
    Serial.println(y);
  }
}