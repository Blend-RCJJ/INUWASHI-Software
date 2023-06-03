/** distanceSensor.h
 * VL53L0Xからの情報を監視します。
 * XIAOと繋がっているuartのポインタを渡して初期化すること。
 */

#ifndef _DISTANCE_SENSOR_H_
#define _DISTANCE_SENSOR_H_

#include <Arduino.h>

class DISTANCE_SENSOR {
   public:
    DISTANCE_SENSOR(HardwareSerial *p);

    HardwareSerial *serialPtr;

    int val[12] = {0};

    int vecX[12] = {0};
    int vecY[12] = {0};
    bool isNotRight = false;
    bool isNotLeft  = false;

    bool isNorthWall = false;
    bool isEastWall  = false;
    bool isSouthWall = false;
    bool isWestWall  = false;

    int read(void);
    void calcVector(int angle);  // 定義しときました〜
    void rightWall(void);
    void leftWall(void);
    void direction(void);

   private:
    int _valTemp[12] = {0};
};

#endif