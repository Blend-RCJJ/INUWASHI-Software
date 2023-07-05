#ifndef _VICTIM_H_
#define _VICTIM_H_

#include "../../device/device.h"

class VICTIM {
   public:
    int isRightOrLeft = 0;  // 0;NAN 1;right 2;left
    int id = 0;

    bool isDetected = false;

    bool place[20 * 2][20 * 2] = {false};

    void read(void) {
        static unsigned long timer = 0;
        for (int i = 0; i < 2; i++) {
            camera[i].read();
            if (camera[i].data != 'N') {
                this->id = camera[i].data;
                timer = millis();
                break;
            }
        }

        if (camera[0].data != 'N') {
            this->isRightOrLeft = RIGHT;
        } else if (camera[1].data != 'N') {
            this->isRightOrLeft = LEFT;
        } else if (millis() - timer > 1000) {
            this->isRightOrLeft = 0;
        }
    }

    unsigned long color(int _id) {
        unsigned long returnColor;
        switch (id) {
            case VICTIM_H:
                returnColor = led.pink;
                break;
            case VICTIM_S:
                returnColor = led.blue;
                break;
            case VICTIM_U:
                returnColor = led.white;
                break;
            case VICTIM_RED:
                returnColor = led.red;
                break;
            case VICTIM_YELLOW:
                returnColor = led.yellow;
                break;
            case VICTIM_GREEN:
                returnColor = led.green;
                break;

            default:
                break;
        }
    }

} victim;

#endif