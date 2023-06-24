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
        if (Serial1.available() >= 3) {
            if (Serial1.read() == 'U') {
                if (Serial1.read() == 'I') {
                    char byteNum = Serial1.read();

                    while (Serial1.available() < byteNum) {
                    }

                    if (byteNum == 13) {  // setting Mode
                        gyro = Serial1.read() * 256 + Serial1.read();
                        
                    }
                }
            }
        }
    }
};

#endif