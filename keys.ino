const char keyUp = 'U';
const char keyDown = 'D';
const char keyRight = 'R';
const char keyLeft = 'L';
const char keyNone = 'N';
const byte rowAmount = 4;
const byte colAmount = 4;
const byte delayMs = 300;

int lastMs = millis();

char keyMatrix[rowAmount][colAmount] = {
  {keyNone, keyUp,    keyNone,  keyNone},
  {keyLeft, keyNone,  keyRight, keyNone},
  {keyNone, keyDown,  keyNone,  keyNone},
  {keyNone, keyNone,  keyNone,  keyNone}
};

int usedButtons[4][2] = {
  {0, 1},
  {1, 0},
  {1, 2},
  {2, 1}
};

byte rowPins[rowAmount] = { 5, 4, 3, 2 };
byte colPins[colAmount] = { 6, 7, 8, 9 };


void setup()
{
  for (int i = 0; i < rowAmount; i++) {
    pinMode(rowPins[i], OUTPUT);
    digitalWrite(rowPins[i], HIGH);
  }

  for (int i = 0; i < colAmount; i++) {
    pinMode(colPins[i], INPUT);
    digitalWrite(colPins[i], HIGH);
  }
  Serial.begin(115200);
  Serial1.begin(115200);
}

void loop()
{
  char key = getKey();
  if (key != keyNone) {
    Serial1.write(key);
    delay(100);
  }
}

char getKey()
{
  char result = keyNone;
  for (int i = 0; i < 4; i++) {
    int y = usedButtons[i][0];
    int x = usedButtons[i][1];
    bool isDown = isKeyDown(y, x);
    if (isDown && millis() - lastMs > delayMs) {
      result = keyMatrix[y][x];
      lastMs = millis();
    }
  }
  return result;
}

bool isKeyDown(int i, int j)
{
  bool result = false;
  digitalWrite(rowPins[i], LOW);
  if (digitalRead(colPins[j]) == LOW) {
    result = true;
  }
  digitalWrite(rowPins[i], HIGH);
  return result;
}