/** distanceSensor.h
 * VL53L0Xからの情報を監視します。
 * XIAOと繋がっているuartのポインタを渡して初期化すること。
 */

#ifndef _DISTANCE_SENSOR_H_
#define _DISTANCE_SENSOR_H_

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

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