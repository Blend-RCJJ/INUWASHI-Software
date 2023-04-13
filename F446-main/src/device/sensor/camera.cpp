#include "camera.h"

CAMERA_INDEPENDENT::CAMERA_INDEPENDENT(HardwareSerial *ptr) {
    serialPtr = ptr;
    serialPtr->begin(115200);
}

void CAMERA_INDEPENDENT::read(void) {
    if (serialPtr->available() > 0) {
        // this->data = serialPtr->read();
        int temp = serialPtr->read();

        if (temp == 'H' || temp == 'S' || temp == 'U' || temp == 'Y' ||
            temp == 'R' || temp == 'G' || temp == 'N') {
            this->data = temp;
        }

        while (serialPtr->available() > 0) {
            serialPtr->read();
        }
    }
}

CAMERA::CAMERA(HardwareSerial *_leftPtr, HardwareSerial *_rightPtr) {
    leftPtr = _leftPtr;
    rightPtr = _rightPtr;
}

void CAMERA::read(void) {
    left.read();
    right.read();

    if (left.isVictimDetected || right.isVictimDetected) {
        isVictimDetected = true;
    } else {
        isVictimDetected = false;
    }
}