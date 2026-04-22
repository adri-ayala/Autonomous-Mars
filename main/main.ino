#include <Arduino.h>

#include "Buzzer.h"
#include "Camera.h"
#include "Lights.h"
#include "LineSensor.h"
#include "MotorControl.h"
#include "OLED.h"
#include "ServoControl.h"
#include "UltraSonic.h"
#include "protothreads.h"

namespace {

pt lineThreadState;
pt cameraThreadState;
pt cameraActionThreadState;
pt rangeThreadState;
pt motorThreadState;
pt lightsThreadState;
pt musicThreadState;
pt oledThreadState;

bool obstacleDetected = false;
float lastDistanceCm = -1.0f;
bool cameraEnabled = false;
bool musicStarted = false;
unsigned long obstacleSeenAtMs = 0;

constexpr unsigned long LINE_THREAD_INTERVAL_MS = 20;
constexpr unsigned long RANGE_THREAD_INTERVAL_MS = 60;
constexpr unsigned long CAMERA_THREAD_INTERVAL_MS = 120;
constexpr unsigned long CAMERA_ACTION_THREAD_INTERVAL_MS = 20;
constexpr unsigned long MOTOR_THREAD_INTERVAL_MS = 20;
constexpr unsigned long LIGHTS_THREAD_INTERVAL_MS = 20;
constexpr unsigned long MUSIC_THREAD_INTERVAL_MS = 20;
constexpr unsigned long OLED_THREAD_INTERVAL_MS = 80;
constexpr unsigned long CAMERA_HOLD_MS = 1200;

PT_THREAD(runLineThread(struct pt* pt)) {
    static unsigned long nextRunAt;

    PT_BEGIN(pt);

    while (true) {
        nextRunAt = millis() + LINE_THREAD_INTERVAL_MS;

        if (!cameraEnabled && !cameraActionActive() && !motorActionActive()) {
            followLine();
        } else if (!motorActionActive()) {
            stopMotors();
        }

        PT_WAIT_UNTIL(pt, millis() >= nextRunAt);
    }

    PT_END(pt);
}

PT_THREAD(runRangeThread(struct pt* pt)) {
    static unsigned long nextRunAt;

    PT_BEGIN(pt);

    while (true) {
        nextRunAt = millis() + RANGE_THREAD_INTERVAL_MS;

        lastDistanceCm = readDistanceCm();
        obstacleDetected = lastDistanceCm > 0.0f &&
                           lastDistanceCm <= ULTRASONIC_OBJECT_DISTANCE_CM;

        if (obstacleDetected) {
            obstacleSeenAtMs = millis();
        }

        cameraEnabled =
            obstacleDetected ||
            cameraActionActive() ||
            (obstacleSeenAtMs != 0 &&
             millis() - obstacleSeenAtMs < CAMERA_HOLD_MS);

        PT_WAIT_UNTIL(pt, millis() >= nextRunAt);
    }

    PT_END(pt);
}

PT_THREAD(runCameraActionThread(struct pt* pt)) {
    static unsigned long nextRunAt;

    PT_BEGIN(pt);

    while (true) {
        nextRunAt = millis() + CAMERA_ACTION_THREAD_INTERVAL_MS;
        cameraActionTask();
        PT_WAIT_UNTIL(pt, millis() >= nextRunAt);
    }

    PT_END(pt);
}

PT_THREAD(runMotorThread(struct pt* pt)) {
    static unsigned long nextRunAt;

    PT_BEGIN(pt);

    while (true) {
        nextRunAt = millis() + MOTOR_THREAD_INTERVAL_MS;
        motorTask();
        PT_WAIT_UNTIL(pt, millis() >= nextRunAt);
    }

    PT_END(pt);
}

PT_THREAD(runLightsThread(struct pt* pt)) {
    static unsigned long nextRunAt;

    PT_BEGIN(pt);

    while (true) {
        nextRunAt = millis() + LIGHTS_THREAD_INTERVAL_MS;
        lightsTask();
        PT_WAIT_UNTIL(pt, millis() >= nextRunAt);
    }

    PT_END(pt);
}

PT_THREAD(runCameraThread(struct pt* pt)) {
    static unsigned long nextRunAt;

    PT_BEGIN(pt);

    while (true) {
        nextRunAt = millis() + CAMERA_THREAD_INTERVAL_MS;

        if (cameraEnabled && !cameraActionActive()) {
            oledSetMessage("CAMERA");
            cameraTask();
        } else if (!cameraEnabled && !cameraActionActive()) {
            cameraReset();
        }

        PT_WAIT_UNTIL(pt, millis() >= nextRunAt);
    }

    PT_END(pt);
}

PT_THREAD(runMusicThread(struct pt* pt)) {
    static unsigned long nextRunAt;

    PT_BEGIN(pt);

    while (true) {
        nextRunAt = millis() + MUSIC_THREAD_INTERVAL_MS;

        if (!musicStarted) {
            buzzerTask("play");
            musicStarted = true;
        } else {
            buzzerTask("");
        }

        PT_WAIT_UNTIL(pt, millis() >= nextRunAt);
    }

    PT_END(pt);
}

PT_THREAD(runOledThread(struct pt* pt)) {
    static unsigned long nextRunAt;

    PT_BEGIN(pt);

    while (true) {
        nextRunAt = millis() + OLED_THREAD_INTERVAL_MS;

        if (!cameraEnabled) {
            oledSetMessage("DRIVE");
        }

        oledTask();
        PT_WAIT_UNTIL(pt, millis() >= nextRunAt);
    }

    PT_END(pt);
}

}  // namespace

void setup() {
    oledInit();
    lightsInit();
    servoInit();
    motorInit();
    lineSensorInit();
    ultraSonicInit();
    cameraInit();
    oledSetMessage("DRIVE");

    PT_INIT(&lineThreadState);
    PT_INIT(&cameraThreadState);
    PT_INIT(&cameraActionThreadState);
    PT_INIT(&rangeThreadState);
    PT_INIT(&motorThreadState);
    PT_INIT(&lightsThreadState);
    PT_INIT(&musicThreadState);
    PT_INIT(&oledThreadState);
}

void loop() {
    runRangeThread(&rangeThreadState);
    runCameraThread(&cameraThreadState);
    runCameraActionThread(&cameraActionThreadState);
    runLineThread(&lineThreadState);
    runMotorThread(&motorThreadState);
    runLightsThread(&lightsThreadState);
    runMusicThread(&musicThreadState);
    runOledThread(&oledThreadState);
}
