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

    int val[16] = {0};

    int vecX[16]    = {0};
    int vecY[16]    = {0};
    bool isNotRight = false;
    bool isNotLeft  = false;
    bool isNotFront = false;

    bool isNorthWall = false;
    bool isEastWall  = false;
    bool isSouthWall = false;
    bool isWestWall  = false;

    bool isFrontWall  = false;
    bool isRightWall  = false;
    bool isBehindWall = false;
    bool isLeftWall   = false;

    int wallStatus = 0;

    int read(void);
    void calc(int angle);  // 定義しときました〜
    void leftWall(void);
    void direction(void);
    void rightWall(void);
    void wallCondition(void);
    void relativeDirection(void);

   private:
    int _valTemp[16] = {0};
};

#endif