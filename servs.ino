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
    auto key = Serial1.read();
    int shiftFirst = 0;
    int shiftSecond = 0;
    if (key == 'L') {
      shiftFirst = 1;
    } else if (key == 'R') {
      shiftFirst = -1;
    } else if (key == 'U') {
      shiftSecond = 1;
    } else if (key == 'D') {
      shiftSecond = -1;
    } 
    updatePositions(shiftFirst, shiftSecond);
    return;
  }
}

void updatePositions(int shiftFirst, int shiftSecond){
    firstPosition = min(180, max(0, firstPosition + shiftFirst));
    secondPosition = min(180, max(0, secondPosition + shiftSecond));
    Serial.print(firstPosition);
    Serial.write("_");
    Serial.println(secondPosition);
    
    first.write(firstPosition);
    second.write(secondPosition);
    Serial1.print("moving to: ");
    Serial1.print(firstPosition);
    Serial1.print(" ");
    Serial1.println(secondPosition);
}