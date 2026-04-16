#include <Arduino.h>
#include "Buzzer.h"
#include "Camera.h"
#include "OLED.h"
#include "Lights.h"
#include "ServoControl.h"
#include "MotorControl.h"

String receivedWord = "";
unsigned long lastReceiveTime = 0;
const unsigned long WORD_TIMEOUT = 120;

void setup() {
  Serial2.begin(38400);

  oledInit();// shows 'READY' 
  cameraInit();// immediately starts scanning
  motorInit();// Motor
  lightsInit();// Lights
}

void loop() {
  readBluetooth();
  buzzerTask("");
  cameraTask();// always scanning
  
}

// BLUETOOTH
void readBluetooth() {
  while (Serial2.available()) {
    char c = Serial2.read();
    lastReceiveTime = millis();

    if (c == '\n' || c == '\r') {
      if (receivedWord.length() > 0) {
        processCommand(receivedWord);
        receivedWord = "";
      }
    } else {
      receivedWord += c;
    }
  }
  if (receivedWord.length() > 0 && millis() - lastReceiveTime > WORD_TIMEOUT) {
    processCommand(receivedWord);
    receivedWord = "";
  }
}

void processCommand(String word) {
  word.toLowerCase();
  word.trim();

  buzzerTask(word);
}