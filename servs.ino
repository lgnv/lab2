#include <Servo.h>

Servo first;
int firstPosition = 0;
Servo second;
int secondPosition = 0;

void setup() {
 first.attach(10);
 second.attach(9);
 updatePositions(0, 0);
 Serial.begin(115200);
 Serial1.begin(115200);
}

void loop() {
  if(Serial1.available())
  {
    updatePositions(Serial1.read());
    return;
  }
}

void updatePositions(char command){
    if (command == 'L') {
      first.write(min(180, max(0, firstPosition + 1)));
    } else if (command == 'R') {
      first.write(min(180, max(0, firstPosition - 1)));
    } else if (command == 'U') {
      second.write(min(180, max(0, secondPosition + 1)));
    } else if (command == 'D') {
      second.write(min(180, max(0, secondPosition - 1));)
    }
}