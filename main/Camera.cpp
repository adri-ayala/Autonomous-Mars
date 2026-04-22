#include "Buzzer.h"
#include "Camera.h"
#include "Lights.h"
#include "MotorControl.h"
#include "OLED.h"
#include "ServoControl.h"
#include <Pixy2.h>

namespace {

enum CameraActionState {
    CAMERA_ACTION_IDLE = 0,
    CAMERA_ACTION_WAIT_LIGHTS,
    CAMERA_ACTION_WAIT_TURN
};

Pixy2 pixy;
int lastBarcode = -1;
CameraActionState actionState = CAMERA_ACTION_IDLE;
MotorAction pendingMotorAction = MOTOR_ACTION_NONE;

void startBarcodeAction(int code) {
    if (actionState != CAMERA_ACTION_IDLE) {
        return;
    }

    buzzerTask("switch");

    switch (code) {
        case 0:
            oledSetMessage("START");
            allLightsOff();
            servoCenter();
            moveForward();
            break;

        case 1:
            oledSetMessage("RIGHT");
            stopMotors();
            servoRight();
            startLightPattern(LIGHT_PATTERN_RIGHT);
            pendingMotorAction = MOTOR_ACTION_RIGHT_90;
            actionState = CAMERA_ACTION_WAIT_LIGHTS;
            break;

        case 2:
            oledSetMessage("U RIGHT");
            stopMotors();
            servoRight();
            startLightPattern(LIGHT_PATTERN_RIGHT_U);
            pendingMotorAction = MOTOR_ACTION_U_RIGHT;
            actionState = CAMERA_ACTION_WAIT_LIGHTS;
            break;

        case 3:
            oledSetMessage("U LEFT");
            stopMotors();
            servoLeft();
            startLightPattern(LIGHT_PATTERN_LEFT_U);
            pendingMotorAction = MOTOR_ACTION_U_LEFT;
            actionState = CAMERA_ACTION_WAIT_LIGHTS;
            break;

        case 4:
            oledSetMessage("LEFT");
            stopMotors();
            servoLeft();
            startLightPattern(LIGHT_PATTERN_LEFT);
            pendingMotorAction = MOTOR_ACTION_LEFT_90;
            actionState = CAMERA_ACTION_WAIT_LIGHTS;
            break;

        case 5:
            oledSetMessage("STOP");
            stopMotors();
            brakeLights();
            servoCenter();
            break;

        default:
            oledSetMessage("UNKNOWN");
            stopMotors();
            break;
    }
}

void finishCameraAction() {
    servoCenter();
    pendingMotorAction = MOTOR_ACTION_NONE;
    actionState = CAMERA_ACTION_IDLE;
}

}  // namespace

void cameraInit() {
    pixy.init();
}

bool cameraTask() {
    if (actionState != CAMERA_ACTION_IDLE) {
        return false;
    }

    pixy.line.getAllFeatures();

    if (pixy.line.numBarcodes <= 0) {
        return false;
    }

    const int code = pixy.line.barcodes[0].m_code;
    if (code == lastBarcode) {
        return false;
    }

    lastBarcode = code;
    startBarcodeAction(code);
    return true;
}

void cameraActionTask() {
    switch (actionState) {
        case CAMERA_ACTION_IDLE:
            return;

        case CAMERA_ACTION_WAIT_LIGHTS:
            if (!lightPatternActive()) {
                startMotorAction(pendingMotorAction);
                actionState = CAMERA_ACTION_WAIT_TURN;
            }
            return;

        case CAMERA_ACTION_WAIT_TURN:
            if (!motorActionActive()) {
                finishCameraAction();
            }
            return;
    }
}

bool cameraActionActive() {
    return actionState != CAMERA_ACTION_IDLE;
}

void cameraReset() {
    if (actionState == CAMERA_ACTION_IDLE) {
        lastBarcode = -1;
    }
}
