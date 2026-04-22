#include "Lights.h"

namespace {

constexpr uint8_t LED_FLT = 49;
constexpr uint8_t LED_FRT = 43;
constexpr uint8_t LED_RLT = 31;
constexpr uint8_t LED_RRT = 37;
constexpr uint8_t LED_RLB = 27;
constexpr uint8_t LED_RRB = 33;

constexpr unsigned long BLINK_INTERVAL_MS = 300;

LightPattern activePattern = LIGHT_PATTERN_NONE;
bool blinkOn = false;
unsigned long nextBlinkAtMs = 0;
uint8_t togglesRemaining = 0;

void setLeftSignal(bool enabled) {
    digitalWrite(LED_FLT, enabled ? HIGH : LOW);
    digitalWrite(LED_RLT, enabled ? HIGH : LOW);
}

void setRightSignal(bool enabled) {
    digitalWrite(LED_FRT, enabled ? HIGH : LOW);
    digitalWrite(LED_RRT, enabled ? HIGH : LOW);
}

void setBrake(bool enabled) {
    digitalWrite(LED_RLB, enabled ? HIGH : LOW);
    digitalWrite(LED_RRB, enabled ? HIGH : LOW);
}

void resetSignalState() {
    blinkOn = false;
    togglesRemaining = 0;
    nextBlinkAtMs = 0;
}

uint8_t blinkTogglesForPattern(LightPattern pattern) {
    switch (pattern) {
        case LIGHT_PATTERN_LEFT:
        case LIGHT_PATTERN_RIGHT:
            return 8;
        case LIGHT_PATTERN_LEFT_U:
        case LIGHT_PATTERN_RIGHT_U:
            return 16;
        default:
            return 0;
    }
}

void applyPatternOutput() {
    setLeftSignal(false);
    setRightSignal(false);
    setBrake(activePattern == LIGHT_PATTERN_BRAKE);

    if (!blinkOn) {
        return;
    }

    if (activePattern == LIGHT_PATTERN_LEFT ||
        activePattern == LIGHT_PATTERN_LEFT_U) {
        setLeftSignal(true);
    } else if (activePattern == LIGHT_PATTERN_RIGHT ||
               activePattern == LIGHT_PATTERN_RIGHT_U) {
        setRightSignal(true);
    }
}

}  // namespace

void lightsInit() {
    pinMode(LED_FLT, OUTPUT);
    pinMode(LED_FRT, OUTPUT);
    pinMode(LED_RLT, OUTPUT);
    pinMode(LED_RRT, OUTPUT);
    pinMode(LED_RLB, OUTPUT);
    pinMode(LED_RRB, OUTPUT);

    allLightsOff();
}

void lightsTask() {
    if (activePattern == LIGHT_PATTERN_NONE ||
        activePattern == LIGHT_PATTERN_BRAKE) {
        return;
    }

    const unsigned long now = millis();
    if (now < nextBlinkAtMs) {
        return;
    }

    blinkOn = !blinkOn;
    if (togglesRemaining > 0) {
        --togglesRemaining;
    }

    applyPatternOutput();

    if (togglesRemaining == 0) {
        allLightsOff();
        return;
    }

    nextBlinkAtMs = now + BLINK_INTERVAL_MS;
}

void startLightPattern(LightPattern pattern) {
    activePattern = pattern;

    if (pattern == LIGHT_PATTERN_NONE) {
        allLightsOff();
        return;
    }

    if (pattern == LIGHT_PATTERN_BRAKE) {
        resetSignalState();
        applyPatternOutput();
        return;
    }

    resetSignalState();
    togglesRemaining = blinkTogglesForPattern(pattern);
    nextBlinkAtMs = millis();
}

bool lightPatternActive() {
    return activePattern != LIGHT_PATTERN_NONE;
}

void brakeLights() {
    startLightPattern(LIGHT_PATTERN_BRAKE);
}

void allLightsOff() {
    activePattern = LIGHT_PATTERN_NONE;
    resetSignalState();
    setLeftSignal(false);
    setRightSignal(false);
    setBrake(false);
}

void leftTurnSignal() {
    startLightPattern(LIGHT_PATTERN_LEFT);
}

void rightTurnSignal() {
    startLightPattern(LIGHT_PATTERN_RIGHT);
}

void leftUTurnSignal() {
    startLightPattern(LIGHT_PATTERN_LEFT_U);
}

void rightUTurnSignal() {
    startLightPattern(LIGHT_PATTERN_RIGHT_U);
}
