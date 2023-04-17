#include <Arduino.h>
#include <SPI.h>
#include <Adafruit_SPIDevice.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>

#include "./img/matsuken.h"
#include "./img/shirosuke.h"
#include "./img/shirokuma.h"
#include "./img/samba.h"
#include "./img/blend.h"

#define ARR_SIZE 76800

// SPI0の場合
#define TFT_CS 17    // CS
#define TFT_RST 22   // Reset
#define TFT_DC 28    // D/C
#define TFT_MOSI 19  // SDI(MOSI)
#define TFT_MISO 16  // SDI(MOSI)
#define TFT_SCK 18   // SCK

Adafruit_ILI9341 tft = Adafruit_ILI9341(&SPI, TFT_DC, TFT_CS, TFT_RST);

void showImage(const uint16_t *imagePtr) {
    uint16_t *imageData;
    imageData = new uint16_t[ARR_SIZE];

    for (int i = 0; i < ARR_SIZE; i++) {
        imageData[i] = imagePtr[i];
    }

    tft.drawRGBBitmap(0, 0, imageData, 320, 240);

    delete[] imageData;
}

void setup() {
    Serial.begin(115200);
    tft.begin(100000000);
    tft.setRotation(1);

    // 頑張って起動してるっぽい仕草
    showImage(image_data_blend);
    delay(3000);
}

void loop(void) {
    showImage(image_data_shirokuma);
    delay(1000);

    showImage(image_data_shirosuke);
    delay(1000);

    showImage(image_data_samba);
    delay(1000);

    showImage(image_data_matsuken);
    delay(1000);
}