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
        ptrArr[i]->setBrightness(normalBrightness);
        ptrArr[i]->clear();
        ptrArr[i]->show();
    }
}

void LED::bootIllumination(void) {
    for (int brightCtr = 0; brightCtr < 255; brightCtr += 4) {
        for (int i = 0; i < 4; i++) {
            setBrightness(i, brightCtr);
            setColor(i, white);
            show(i);
        }
        delay(1);
    }
}

void LED::initCompleteIllumination(void) {
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
    ptrArr[led]->fill(ptrArr[led]->Color(r, g, b));
}

void LED::setColor(int led, unsigned long color) {
    ptrArr[led]->fill(color);
}

unsigned long LED::colorRGB(int red, int green, int blue) {
    return ptrArr[0]->Color(red, green, blue);
}

unsigned long LED::colorHSV(int hue, int saturation, int value) {
    return ptrArr[0]->ColorHSV(hue * 256, saturation, value);
}

void LED::setBrightness(int led, int brightness) {
    ptrArr[led]->setBrightness((int)(brightness * normalBrightness / 255.0));
}

void LED::setBrightnessRaw(int led, int brightness) {
    ptrArr[led]->setBrightness(brightness);
}

void LED::showAll(void) {
    for (int i = 0; i < 4; i++) {
        show(i);
    }
}

void LED::show(int led) {
    if (disableAll || *(disablePtr[led])) return;

    if (led == LEFT || led == RIGHT) {
        setColor(led, blank);
    }

    ptrArr[led]->show();
}

void LED::setColorBar(int position, unsigned long color) {
    if (disableAll || disableUI) return;

    const int barWidth = 5;  // 奇数

    const int barMax = ptrArr[UI]->numPixels() - 1 - barWidth / 2;
    const int barMin = barWidth / 2;

    int nomalizedPosition =
        round(constrain(map(position, 10, 80, barMin, barMax), barMin, barMax));

    ptrArr[UI]->fill(blank);

    for (int i = 0; i < barWidth / 2 + 1; i++) {
        ptrArr[UI]->setPixelColor(nomalizedPosition + i, color);
        ptrArr[UI]->setPixelColor(nomalizedPosition - i, color);
    }
}

void LED::setGlowColor(void) {
    for (int i = 0; i < 4; i++) {
        setBrightnessRaw(i, normalBrightness);
    }

    setColor(LEFT, blank);
    setColor(RIGHT, blank);
    setColor(UI, blank);
    setColor(TOP, lowWhite);

    for (int i = 8; i < 13; i++) {
        ptrArr[TOP]->setPixelColor(i, white);
    }

    for (int i = 20; i < 25; i++) {
        ptrArr[TOP]->setPixelColor(i, white);
    }
}