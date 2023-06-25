#ifndef _DATA_BOX_H_
#define _DATA_BOX_H_

#include <Arduino.h>
class DATA_BOX {
   public:
    int status = 0;
    int gyro = 0;

    int coordinateX = 0;
    int coordinateY = 0;

    int x = 0;
    int y = 0;

    bool gyroReset = false;

    unsigned long runningTimer = 0;

    void init(void) {
        Serial1.begin(1000000);

        delay(100);

        while (Serial1.available()) {
            Serial1.read();
        }

        while (Serial1.available() <= 0) {
        }
    }

    void update(void) {
        if (Serial1.available() >= 3) {
            if (Serial1.read() == 'U') {
                if (Serial1.read() == 'I') {
                    char byteNum = Serial1.read();

                    while (Serial1.available() < byteNum) {
                    }

                    if (byteNum == 13) {  // setting Mode
                        gyro = Serial1.read() * 256 + Serial1.read();

                        while (Serial1.available()) {
                            Serial1.read();
                        }
                    } else if (byteNum == 8) {  // setting Mode
                        status = 1;
                        if (runningTimer == 0) {
                            runningTimer = millis();
                        }
                        gyro = Serial1.read() * 256 + Serial1.read();

                        coordinateX = Serial1.read() * 256 + Serial1.read();
                        coordinateY = Serial1.read() * 256 + Serial1.read();

                        if (coordinateX >= 32768) {
                            coordinateX -= 65536;
                        }

                        if (coordinateY >= 32768) {
                            coordinateY -= 65536;
                        }

                        x = round((double)coordinateX / 300.0);
                        y = round((double)coordinateY / 300.0);

                        while (Serial1.available()) {
                            Serial1.read();
                        }
                    }
                }
            }
        }
    }
};

#endif