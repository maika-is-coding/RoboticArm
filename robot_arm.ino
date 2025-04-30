#include <Servo.h>

#define BASE_PIN 3
#define SHOULDER_PIN 5
#define ELBOW_PIN 6
#define CLAW_PIN 9
#define JOYSTICK1_X A0
#define JOYSTICK1_Y A1
#define JOYSTICK2_X A2
#define JOYSTICK2_Y A3

Servo servos[4];
int joystickPins[4] = {JOYSTICK1_X, JOYSTICK1_Y, JOYSTICK2_X, JOYSTICK2_Y};
int servoPins[4] = {BASE_PIN, SHOULDER_PIN, ELBOW_PIN, CLAW_PIN};
const char* labels[4] = {"Base", "Shoulder", "Elbow", "Claw"};
int angles[4] = {90, 90, 90, 90};

int mapJoystick(int value) {
  return constrain(map(value, 0, 1023, 0, 180), 0, 180);
}

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < 4; i++) {
    servos[i].attach(servoPins[i]);
    servos[i].write(angles[i]);
  }
}

void loop() {
  for (int i = 0; i < 4; i++) {
    angles[i] = mapJoystick(analogRead(joystickPins[i]));
    servos[i].write(angles[i]);
    Serial.print(labels[i]);
    Serial.print(": ");
    Serial.print(angles[i]);
    if (i < 3) Serial.print(" ");
    else Serial.println();
  }
  delay(50);
}
