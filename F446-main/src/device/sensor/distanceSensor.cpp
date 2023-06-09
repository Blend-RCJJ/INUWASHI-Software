#include "distanceSensor.h"

#include "gyro.h"

extern GYRO gyro;

DISTANCE_SENSOR::DISTANCE_SENSOR(HardwareSerial *p) {
    serialPtr = p;
    serialPtr->begin(1000000);
}

int DISTANCE_SENSOR::read(void) {
    if (serialPtr->available() >= 27) {
        int checkDegit = 0;

        if (serialPtr->read() == 'V') {
            if (serialPtr->read() == 'L') {
                for (int i = 0; i < 12; i++) {
                    char data[2];
                    data[0] = serialPtr->read();
                    data[1] = serialPtr->read();

                    checkDegit += data[0] + data[1];

                    _valTemp[i] = (data[0] << 8) + data[1];
                }
            }
        }

        if (checkDegit % 256 == serialPtr->read()) {
            for (int i = 0; i < 12; i++) {
                if (_valTemp[i] > 10) {
                    val[i] = constrain(_valTemp[i], 10, 1200);
                }
            }
        }

        while (serialPtr->available() > 0) {
            serialPtr->read();
        }

        return 0;

    } else {
        return 1;
    }
}

void DISTANCE_SENSOR::calc(int angle) {
    for (int n = 0; n < 12; n++) {
        vecX[n] = val[n] * sin(radians(n * 30 + angle));
        vecY[n] = val[n] * cos(radians(n * 30 + angle));
    }
    leftWall();
    direction();
    rightWall();
}

void DISTANCE_SENSOR::rightWall(void) {
    if (val[0] < 200 && val[3] < 180 && val[9] < 180) {
        isNotFront = true;
    } else {
        isNotFront = false;
    }
    if (val[3] > 300 && val[4] > 250) {
        isNotRight = true;
    } else {
        isNotRight = false;
    }
}

void DISTANCE_SENSOR::leftWall(void) {
    if (val[9] > 300 && val[8] > 250) {
        isNotLeft = true;
    } else {
        isNotLeft = false;
    }
}

void DISTANCE_SENSOR::direction(void) {
    gyro.read();
    if (gyro.North) {
        if (val[0] > 230) {
            isNorthWall = false;
        } else {
            isNorthWall = true;
        }

        if (val[3] > 230) {
            isEastWall = false;
        } else {
            isEastWall = true;
        }

        if (val[6] > 230) {
            isSouthWall = false;
        } else {
            isSouthWall = true;
        }

        if (val[9] > 230) {
            isWestWall = false;
        } else {
            isWestWall = true;
        }
    } else if (gyro.East) {
        if (val[9] > 230) {
            isNorthWall = false;
        } else {
            isNorthWall = true;
        }

        if (val[0] > 230) {
            isEastWall = false;
        } else {
            isEastWall = true;
        }

        if (val[3] > 230) {
            isSouthWall = false;
        } else {
            isSouthWall = true;
        }

        if (val[6] > 230) {
            isWestWall = false;
        } else {
            isWestWall = true;
        }
    } else if (gyro.South) {
        if (val[6] > 230) {
            isNorthWall = false;
        } else {
            isNorthWall = true;
        }

        if (val[9] > 230) {
            isEastWall = false;
        } else {
            isEastWall = true;
        }

        if (val[0] > 230) {
            isSouthWall = false;
        } else {
            isSouthWall = true;
        }

        if (val[3] > 230) {
            isWestWall = false;
        } else {
            isWestWall = true;
        }
    } else if (gyro.West) {
        if (val[9] > 230) {
            isNorthWall = false;
        } else {
            isNorthWall = true;
        }

        if (val[0] > 230) {
            isEastWall = false;
        } else {
            isEastWall = true;
        }

        if (val[6] > 230) {
            isSouthWall = false;
        } else {
            isSouthWall = true;
        }

        if (val[3] > 230) {
            isWestWall = false;
        } else {
            isWestWall = true;
        }
    }
}