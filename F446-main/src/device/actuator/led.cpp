#include "led.h"

#include "../../kit/RTOS-Kit.h"
extern RTOS_Kit app;

LED::LED(Adafruit_NeoPixel* top, Adafruit_NeoPixel* right,
         Adafruit_NeoPixel* left, Adafruit_NeoPixel* ui) {
    ptrArr[TOP] = top;
    ptrArr[RIGHT] = right;
    ptrArr[LEFT] = left;
    ptrArr[UI] = ui;

    // init
    for (int i = 0; i < 4; i++) {
        ptrArr[i]->begin();
        setBrightness(i, maxBrightness);
        ptrArr[i]->show();
    }
}

void LED::bootIllumination(void) {
    if (isDisabled) return;

    for (int brightCtr = 0; brightCtr < 255; brightCtr += 4) {
        for (int i = 0; i < 4; i++) {
            setBrightness(i, brightCtr);
            setColor(i, white);
            ptrArr[i]->show();
        }
        delay(1);
    }
}

void LED::initCompleteIllumination(void) {
    if (isDisabled) return;

    unsigned long timer = millis();
    const int duration = 200;

    while (millis() - timer < duration) {
        for (int i = 0; i < 4; i++) {
            int off;
            switch (i) {
                case TOP:
                case UI:
                    off = map(millis() - timer, 0, duration, 0,
                              ptrArr[i]->numPixels() / 2);

                    ptrArr[i]->setPixelColor(off, blank);
                    ptrArr[i]->setPixelColor(ptrArr[i]->numPixels() - off,
                                             blank);
                    break;

                default:
                    off = map(millis() - timer, 0, duration, 0,
                              ptrArr[i]->numPixels());

                    ptrArr[i]->setPixelColor(off, blank);
            }
        }

        showAll();
    }

    for (int i = 0; i < 4; i++) {
        setColor(i, blank);
    }
    showAll();
}

void LED::setColor(int led, int r, int g, int b) {
    if (isDisabled) return;

    ptrArr[led]->fill(ptrArr[led]->Color(r, g, b));
}

void LED::setColor(int led, unsigned long color) {
    if (isDisabled) return;

    ptrArr[led]->fill(color);
}

unsigned long LED::colorRGB(int red, int green, int blue) {
    return ptrArr[0]->Color(red, green, blue);
}

unsigned long LED::colorHSV(int hue, int saturation, int value) {
    return ptrArr[0]->ColorHSV(hue * 256, saturation, value);
}

void LED::setBrightness(int led, int brightness) {
    if (isDisabled) return;

    ptrArr[led]->setBrightness((int)(brightness * maxBrightness / 255.0));
}

void LED::showAll(void) {
    if (isDisabled) return;

    for (int i = 0; i < 4; i++) {
        ptrArr[i]->show();
    }
}

void LED::show(int led) {
    if (isDisabled) return;

    ptrArr[led]->show();
}