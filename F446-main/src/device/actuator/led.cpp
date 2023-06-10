#include "led.h"

LED::LED(Adafruit_NeoPixel* top, Adafruit_NeoPixel* right,
         Adafruit_NeoPixel* left, Adafruit_NeoPixel* ui) {
    ptrArr[TOP] = top;
    ptrArr[RIGHT] = right;
    ptrArr[LEFT] = left;
    ptrArr[UI] = ui;

    // init
    for (int i = 0; i < 4; i++) {
        ptrArr[i]->begin();
        ptrArr[i]->setBrightness(brightness);
        ptrArr[i]->show();
    }
}

void LED::setColor(int led, int r, int g, int b) {
    if (isDisabled) return;

    ptrArr[led]->fill(ptrArr[led]->Color(r, g, b));
    ptrArr[led]->show();
}