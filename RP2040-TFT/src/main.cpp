#include <Arduino.h>
#include <TFT_eSPI.h>
TFT_eSPI tft = TFT_eSPI();

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

    showBootImage();
}

void loop() {
}
