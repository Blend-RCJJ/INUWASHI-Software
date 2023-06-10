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
    const int brightness = 100;
    const bool isDisabled = false;

   private:
    // funcitons:
    void setColor(int led, int r, int g, int b);
};

#endif