#include <Arduino.h>
#include <TFT_eSPI.h>
#include <XPT2046_Touchscreen.h>

TFT_eSPI tft = TFT_eSPI();
XPT2046_Touchscreen ts(20);

#include "img/blend.h"
#include "ui-kit/00-top.h"
#include "ui-kit/01-camera.h"
#include "ui-kit/02-led.h"
#include "ui-kit/03-motor.h"
#include "ui-kit/04-load.h"
#include "ui-kit/05-tof.h"
#include "ui-kit/06-floor.h"
// #include "img/shirosuke.h"
// #include "img/shirokuma.h"
// #include "img/samba.h"
// #include "img/top3.h"
// #include "img/led.h"
// #include "img/matsuken.h"

#define ARR_SIZE 76800

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
    delay(500);
}

void setup() {
    Serial.begin(115200);
    tft.begin();
    tft.setRotation(1);
    tft.setSwapBytes(true);

    ts.begin();
    ts.setRotation(3);

    showBootImage();
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
        if (!oldTouch && mode == 0) {
            if (abs(1000 - p.x) < 500 && abs(3000 - p.y) < 500) {
                mode = 4;
            } else if (abs(2000 - p.x) < 500 && abs(3000 - p.y) < 500) {
                mode = 5;
            } else if (abs(3000 - p.x) < 500 && abs(3000 - p.y) < 500) {
                mode = 6;
            } else if (abs(1000 - p.x) < 500 && abs(1600 - p.y) < 500) {
                mode = 1;
            } else if (abs(2000 - p.x) < 500 && abs(1600 - p.y) < 500) {
                mode = 2;
            } else if (abs(3000 - p.x) < 500 && abs(1600 - p.y) < 500) {
                mode = 3;
            }
        }
        
        if (mode != 0) {
            if (abs(2000 - p.x) < 800 && p.y > 3000 && !oldTouch) {
                homeCount = 1;
                oldY = p.y;
                homeTime = millis();
            }

            if (homeCount == 1 && millis() - homeTime < 100) {
                if (p.y < oldY - 300) {
                    homeCount = 0;
                    mode = 0;
                }
            }
        }

        Serial.print(p.x);
        Serial.print("\t");
        Serial.println(p.y);
    }
    oldTouch = bTouch;

    if (mode != oldMode) {
        SPI.beginTransaction(
            SPISettings(SPI_FREQUENCY, MSBFIRST, TFT_SPI_MODE));
        SPI.endTransaction();

        switch (mode) {
            case 0:
                showImage(image_data_00top);
                break;
            case 1:
                showImage(image_data_01camera);
                break;
            case 2:
                showImage(image_data_02led);
                break;
            case 3:
                showImage(image_data_03motor);
                break;
            case 4:
                showImage(image_data_04load);
                break;
            case 5:
                showImage(image_data_05tof);
                break;
            case 6:
                showImage(image_data_06floor);
                break;
        }

        oldMode = mode;
    }
}