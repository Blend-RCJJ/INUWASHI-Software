#ifndef _RTOS_UI_H_
#define _RTOS_UI_H_

#include "../../device/device.h"

class VICTIM {
   public:
    bool isDetected = false;
    int id = 0;

    unsigned long color[6] = {led.pink, led.blue,   led.white,
                              led.red,  led.yellow, led.green};
} victim;

#endif