#include "Camera.h"
#include <Pixy2.h>

Pixy2 pixy;

int lastBarcode = -1;

// Function prototype
void interpretBarcode(int code);

// =======================
// INIT
// =======================
void cameraInit() {
    Serial.println("Initializing Pixy Camera...");
    pixy.init();
    Serial.println("Pixy Ready!");
}

// =======================
// MAIN
// =======================
void cameraTask() {
    pixy.line.getAllFeatures();

    // Check if barcode detected
    if (pixy.line.numBarcodes > 0) {
        int code = pixy.line.barcodes[0].m_code;

        if (code != lastBarcode) {
            lastBarcode = code;

            Serial.print("Barcode detected: ");
            Serial.println(code);

            interpretBarcode(code);
        }
    }
}

// =======================
// BARCODE INTERPRETER
// =======================
void interpretBarcode(int code) {
    switch (code) {
        case 0:
            Serial.println("START");
            break;
        case 1:
            Serial.println("TURN RIGHT");
            break;
        case 2:
            Serial.println("U-TURN RIGHT");
            break;
        case 3:
            Serial.println("U-TURN LEFT");
            break;
        case 4:
            Serial.println("TURN LEFT");
            break;
        case 5:
            Serial.println("STOP");
            break;
        default:
            Serial.println("UNKNOWN BARCODE");
            break;
    }
}