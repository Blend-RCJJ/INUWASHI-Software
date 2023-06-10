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

    delay(10);

    // set color
    setColor(TOP, cyan);
    setColor(RIGHT, white);
    setColor(LEFT, white);
    setColor(UI, cyan);
}

void LED::setColor(int led, int r, int g, int b) {
    if (isDisabled) return;

    ptrArr[led]->fill(ptrArr[led]->Color(r, g, b));
    ptrArr[led]->show();
}

void LED::setColor(int led, unsigned long color) {
    if (isDisabled) return;

    ptrArr[led]->fill(color);
    ptrArr[led]->show();
}

unsigned long LED::colorRGB(int red, int green, int blue) {
    return ptrArr[0]->Color(red, green, blue);
}

unsigned long LED::colorHSV(int hue, int saturation, int value) {
    return ptrArr[0]->ColorHSV(hue * 256, saturation, value);
}