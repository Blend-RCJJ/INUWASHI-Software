#ifndef _DISTANCE_SENSOR_H
#define _DISTANCE_SENSOR_H

#include <Arduino.h>

class DISTANCE_SENSOR {
   public:
    DISTANCE_SENSOR(HardwareSerial *p);

    HardwareSerial *serialPtr;

    int val[12] = {0};

    int vecX[12] = {0};
    int vecY[12] = {0};

    int read(void);
    void calcVector(int angle);  // 定義しときました〜

   private:
    int _valTemp[12] = {0};
};

#endif