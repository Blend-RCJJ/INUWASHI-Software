#ifndef _LED_H_
#define _LED_H_

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#define TOP 0
#define RIGHT 1
#define LEFT 2
#define UI 3
class LED {
   public:
    LED(Adafruit_NeoPixel* top, Adafruit_NeoPixel* right,
        Adafruit_NeoPixel* left, Adafruit_NeoPixel* ui);

    Adafruit_NeoPixel* ptrArr[4];

    // settings:
    const int maxBrightness = 255;
    const int normalBrightness = 50;
    const bool disableAll = false;

    bool disableUI = false;
    bool disableTop = false;
    bool disableSide = false;

    const bool* disablePtr[4] = {&disableTop, &disableSide, &disableSide,
                                 &disableUI};

    // functions:
    void bootIllumination(void);
    void initCompleteIllumination(void);

    void setColorBar(int position, unsigned long color);

    void setColor(int led, int r, int g, int b);
    void setColor(int led, unsigned long color);
    void setGlowColor();
    void setBrightness(int led, int brightness);
    void setBrightnessRaw(int led, int brightness);

    void showAll(void);
    void show(int led);

    // colors:
    unsigned long pink = colorHSV(0, 125, 255);
    unsigned long red = colorHSV(0, 255, 255);
    unsigned long yellow = colorHSV(45, 255, 255);
    unsigned long green = colorHSV(90, 255, 255);
    unsigned long cyan = colorHSV(140, 255, 255);
    unsigned long blue = colorHSV(180, 255, 255);
    unsigned long white = colorRGB(255, 255, 255);
    unsigned long lowWhite = colorRGB(255, 255, 255);
    unsigned long blank = colorHSV(0, 0, 0);

   private:
    // funcitons:
    unsigned long colorRGB(int red, int green, int blue);
    unsigned long colorHSV(int hue, int saturation, int value);
};

#endif