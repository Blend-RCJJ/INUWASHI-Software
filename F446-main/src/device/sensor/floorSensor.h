#ifndef _FLOOR_SENSOR_H_
#define _FLOOR_SENSOR_H_

#include <Arduino.h>

class FLOOR_SENSOR {
   public:
    const int brightness = 200;
    int redVal;
    int greenVal;
    int blueVal;

    void read(void){
        // FIXME: 未実装
    };

   private:
};

#endif