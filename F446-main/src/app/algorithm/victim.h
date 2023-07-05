#ifndef _VICTIM_H_
#define _VICTIM_H_

#include "../../device/device.h"

class VICTIM {
   public:
    int isRightOrLeft = 0;  // 0;NAN 1;right 2;left
    int id = 0;

    void read(void) {
        static unsigned long timer = 0;
        for (int i = 0; i < 2; i++) {
            camera[i].read();
            if (camera[i].data != 'N') {
                this->id = i;
                timer = millis();
                break;
            }
        }

        if (camera[0].data != 'N') {
            this->isRightOrLeft = 1;
        } else if (camera[1].data != 'N') {
            this->isRightOrLeft = 2;
        } else if (millis() - timer > 5000) {
            this->isRightOrLeft = 0;
        }
    }

    unsigned long color[6] = {led.pink, led.blue,   led.white,
                              led.red,  led.yellow, led.green};

} victim;

#endif