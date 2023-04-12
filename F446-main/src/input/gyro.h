/** gyro.h
 * ジャイロ読むよ
 * 次の機体ではセンサー変えるかも？
 */

#ifndef _GYRO_H
#define _GYRO_H

#include <Arduino.h>

#include <SPI.h>
#include <Wire.h>
#include <EEPROM.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>

class GYRO {
   public:
    GYRO(Adafruit_BNO055 *p);
    Adafruit_BNO055 *sensorPtr;
    
    int deg = 0;
    int magnetic = 0;
    int offset = 0;

    int error = 0;
    int oldDeg = 0;

    int slope = 0;
    int slopeOffset = 0;

    bool isGyroDisabled = true;

    void init(void);
    void setOffset(void);
    int read(void);

   private:
};

#endif