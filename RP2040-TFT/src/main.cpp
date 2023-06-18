#include <Arduino.h>
#include <TFT_eSPI.h>

TFT_eSPI tft = TFT_eSPI();
TFT_eSprite sprite = TFT_eSprite(&tft);

#define ARR_SIZE 76800

#include "./img/blend.h"
#include "./img/ui-image/ui-image.h"
#include "./img/victim/victim.h"
#include "./device/device.h"

#define BACKLIGHT 29

void showImage(const uint16_t *imagePtr) {
    uint16_t *imageData;
    imageData = new uint16_t[ARR_SIZE];

    for (int i = 0; i < ARR_SIZE; i++) {
        imageData[i] = imagePtr[i];
    }

    sprite.pushImage(0, 0, 320, 240, imageData);
    sprite.pushSprite(0, 0);

    delete[] imageData;
}

void showBootImage(void) {
    tft.fillScreen(TFT_BLACK);
    showImage(image_data_blend);
}

void setup() {
    pinMode(BACKLIGHT, OUTPUT);
    sprite.createSprite(320, 240);
    sprite.setColorDepth(7);

    Serial.begin(115200);

    touch.begin();

    tft.begin();
    tft.setAddrWindow(0, 0, 240, 320);
    tft.setRotation(1);
    tft.setSwapBytes(true);

    // showBootImage();
    sprite.pushImage(0, 0, 320, 240, image_data_blend);
    sprite.pushSprite(0, 0);
    digitalWrite(BACKLIGHT, LOW);
    delay(500);

    sprite.fillRect(0, 0, 320, 240, TFT_BLUE);
    sprite.pushSprite(0, 0);

    led.normalSign();
}

int mode = 0;
int oldMode = 1;

void loop() {
    touch.read();

    sprite.fillRect(0, 0, 320, 240, TFT_BLUE);

    if (touch.isTouched) {
        sprite.fillCircle(touch.point.x, touch.point.y, 15, TFT_WHITE);
    }

    SPI.beginTransaction(SPISettings(SPI_FREQUENCY, MSBFIRST, TFT_SPI_MODE));
    SPI.endTransaction();
    sprite.pushSprite(0, 0);

    // Serial.print(touch.point.x);
    // Serial.print("\t");
    // Serial.print(touch.point.y);
    // Serial.print("\t");
    // Serial.println(touch.isTouched);

    // delay(10);
}