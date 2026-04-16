#include "Lights.h"

// =======================
// FRONT
// =======================
#define LED_FLT 49
#define LED_FRT 43

// =======================
// REAR
// =======================
#define LED_RLT 31
#define LED_RRT 37

#define LED_RLB 27
#define LED_RRB 33

// =======================
void lightsInit() {
    pinMode(LED_FLT, OUTPUT);
    pinMode(LED_FRT, OUTPUT);
    pinMode(LED_RLT, OUTPUT);
    pinMode(LED_RRT, OUTPUT);
    pinMode(LED_RLB, OUTPUT);
    pinMode(LED_RRB, OUTPUT);

    allLightsOff();
}

// =======================
void allLightsOff() {
    digitalWrite(LED_FLT, LOW);
    digitalWrite(LED_FRT, LOW);
    digitalWrite(LED_RLT, LOW);
    digitalWrite(LED_RRT, LOW);
    digitalWrite(LED_RLB, LOW);
    digitalWrite(LED_RRB, LOW);
}

// =======================
void brakeLights() {
    digitalWrite(LED_RLB, HIGH);
    digitalWrite(LED_RRB, HIGH);
}

// =======================
void leftTurnSignal() {
    for (int i = 0; i < 4; i++) {
        digitalWrite(LED_FLT, HIGH);
        digitalWrite(LED_RLT, HIGH);

        delay(300);

        digitalWrite(LED_FLT, LOW);
        digitalWrite(LED_RLT, LOW);

        delay(300);
    }
}

// =======================
void rightTurnSignal() {
    for (int i = 0; i < 4; i++) {
        digitalWrite(LED_FRT, HIGH);
        digitalWrite(LED_RRT, HIGH);

        delay(300);

        digitalWrite(LED_FRT, LOW);
        digitalWrite(LED_RRT, LOW);

        delay(300);
    }
}

// =======================
void leftUTurnSignal() {
    leftTurnSignal();
    leftTurnSignal();
}

// =======================
void rightUTurnSignal() {
    rightTurnSignal();
    rightTurnSignal();
}