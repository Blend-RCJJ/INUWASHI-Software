#include "./camera.h"

CAMERA::CAMERA(HardwareSerial *ptr) {
    serialPtr = ptr;
    serialPtr->begin(115200);
}

void CAMERA::read(void) {
    if (serialPtr->available() > 0) {
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