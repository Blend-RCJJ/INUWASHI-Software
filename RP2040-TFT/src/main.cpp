#include <Arduino.h>
#include <TFT_eSPI.h>
#include <XPT2046_Touchscreen.h>

TFT_eSPI tft = TFT_eSPI();
XPT2046_Touchscreen ts(20);

#include "img/blend.h"
#include "img/shirosuke.h"
#include "img/shirokuma.h"

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
    showImage(image_data_shirokuma);
    delay(500);
    showImage(image_data_shirosuke);
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

void loop() {
    bool bTouch = ts.touched();
    TS_Point p = ts.getPoint();

    delay(10);

    if (bTouch) {
        Serial.print("x:");
        Serial.print(p.x);
        Serial.print("\ty:");
        Serial.println(p.y);

        SPI.beginTransaction(
            SPISettings(SPI_FREQUENCY, MSBFIRST, TFT_SPI_MODE));
        SPI.endTransaction();

        showImage(image_data_shirokuma);

        tft.setCursor(0, 0);
        tft.setTextColor(TFT_RED);
        tft.setTextSize(8);
        tft.print(p.x);
        tft.setCursor(0, 15 * 4);
        tft.print(p.y);
    } else {
        Serial.println("No YUBI!!!!!");
        SPI.beginTransaction(
            SPISettings(SPI_FREQUENCY, MSBFIRST, TFT_SPI_MODE));
        SPI.endTransaction();

        showImage(image_data_blend);
    }
}