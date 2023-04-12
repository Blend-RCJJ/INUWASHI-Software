#ifndef _FLOOR_SENSOR_H
#define _FLOOR_SENSOR_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

class FLOOR_SENSOR {
   public:
    const int brightness = 200;
    int redVal;
    int greenVal;
    int blueVal;

   private:
};

#endif