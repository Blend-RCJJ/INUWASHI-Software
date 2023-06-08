#include <Arduino.h>
#include <TFT_eSPI.h>
#include <XPT2046_Touchscreen.h>
#include <Adafruit_NeoPixel.h>

TFT_eSPI tft = TFT_eSPI();
XPT2046_Touchscreen ts(7);

#define ARR_SIZE 76800

#include "./img/blend.h"
#include "./ui-kit/ui-kit.h"
#include "./victim/victim.h"

#define BACKLIGHT 29

void showImage(const uint16_t *imagePtr) {
    uint16_t *imageData;
    imageData = new uint16_t[ARR_SIZE];

    for (int i = 0; i < ARR_SIZE; i++) {
        imageData[i] = imagePtr[i];
    }

    tft.pushImage(0, 0, 320, 240, imageData);

    delete[] imageData;
}

void showBootImage(void) {
    tft.fillScreen(TFT_BLACK);

    showImage(image_data_blend);
}

void setup() {
    pinMode(BACKLIGHT, OUTPUT);
    pinMode(BACKLIGHT, OUTPUT);

    Serial.begin(115200);
    tft.begin();
    tft.setRotation(1);
    tft.setSwapBytes(true);

    ts.begin();
    ts.setRotation(3);

    showBootImage();
    digitalWrite(BACKLIGHT, LOW);
    delay(500);
}

int mode = 0;
int oldMode = 1;

void loop() {
    bool bTouch = ts.touched();
    static bool oldTouch = false;
    TS_Point p = ts.getPoint();

    static int oldY = 0;
    static int homeCount = 0;
    static int homeTime = 0;
    delay(10);

    if (bTouch) {
        Serial.print(p.x);
        Serial.print("\t");
        Serial.println(p.y);
    }
    oldTouch = bTouch;
}