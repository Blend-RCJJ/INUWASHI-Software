#ifndef _FLOOR_SENSOR_H_
#define _FLOOR_SENSOR_H_

#include <Adafruit_NeoPixel.h>
#include <Adafruit_Sensor.h>
#include <Arduino.h>
#include <EEPROM.h>
#include <SPI.h>
#include <Wire.h>

class FLOOR_SENSOR {
   public:
    const int brightness = 160;
    int redVal;
    int blankVal;
    int blueVal;
    int tof_of_bottom;

    unsigned long colorRGB(int red, int green, int blue);
    unsigned long colorHSV(int hue, int saturation, int brightness);

    unsigned long red   = colorRGB(255, 0, 0);
    unsigned long green = colorRGB(0, 255, 0);
    unsigned long blue  = colorRGB(0, 0, 255);
    unsigned long white = colorRGB(255, 255, 255);
    unsigned long blank = colorRGB(0, 0, 0);

    bool isRed   = false;
    bool isGreen = false;
    bool isBlue  = false;
    bool isBlack = false;
    bool isWhite = false;

    void init(void);

    void tof_of_bottom_read(void);

    void setFloorColor(unsigned long color);
    void colorJudgment(void);

   private:
};

#endif