#ifndef _DATA_BOX_H_
#define _DATA_BOX_H_

#include <Arduino.h>
class DATA_BOX {
   public:
    int gyro = 0;
    bool gyroReset = false;

    void init(void) {
        Serial1.begin(1000000);
    }

    void update(void) {
        if (Serial1.available() >= 4) {
            if (Serial1.read() == 'U') {
                if (Serial1.read() == 'I') {
                    char a = Serial1.read();
                    char b = Serial1.read();
                    gyro = a * 256 + b;
                }
            }
        }
    }
};

#endif