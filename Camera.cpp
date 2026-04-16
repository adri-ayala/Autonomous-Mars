#include "Camera.h"
#include "OLED.h"
#include "Lights.h"
#include "ServoControl.h"
#include "MotorControl.h"
#include <Pixy2.h>

Pixy2 pixy;

int lastBarcode = -1;

void interpretBarcode(int code);

// INIT
void cameraInit() {
    pixy.init();
}

// MAIN LOOP
void cameraTask() {
    pixy.line.getAllFeatures();

    if (pixy.line.numBarcodes > 0) {
        int code = pixy.line.barcodes[0].m_code;

        if (code != lastBarcode) {
            lastBarcode = code;
            interpretBarcode(code);
        }
    }
}

// BARCODE LOGIC
void interpretBarcode(int code) {
    switch (code) {

        case 0: // START
            oledShowLine("START");
            allLightsOff();
            servoCenter();
            moveForward();
            break;

        case 1: // TURN RIGHT
            oledShowLine("RIGHT");
            stopMotors();
            rightTurnSignal();
            servoRight();
            turnRight90();
            servoCenter();
            moveForward();
            break;

        case 2: // U-TURN RIGHT
            oledShowLine("U RIGHT");
            stopMotors();
            rightUTurnSignal();
            servoRight();
            uTurnRight();
            servoCenter();
            moveForward();
            break;

        case 3: // U-TURN LEFT
            oledShowLine("U LEFT");
            stopMotors();
            leftUTurnSignal();
            servoLeft();
            uTurnLeft();
            servoCenter();
            moveForward();
            break;

        case 4: // TURN LEFT
            oledShowLine("LEFT");
            stopMotors();
            leftTurnSignal();
            servoLeft();
            turnLeft90();
            servoCenter();
            moveForward();
            break;

        case 5: // STOP
            oledShowLine("STOP");
            stopMotors();
            brakeLights();
            servoCenter();
            break;

        default:
            oledShowLine("UNKNOWN");
            stopMotors();
            break;
    }
}