#include <Arduino.h>

#include "neopixel.h"
#define NEO_PWR 11
#define NEOPIX 12
Adafruit_NeoPixel pixels(1, NEOPIX, NEO_GRB + NEO_KHZ800);
LED led(&pixels, NEO_PWR);

#include "./ui-kit/ui-kit.h"

UI_KIT ui;

void setup() {
    Serial.begin(115200);
    ui.init();
    ui.showSettingImage(0);

    led.normalSign();
}

int mode = 0;
int oldMode = 1;

void loop() {
    // touch.read();

    // sprite.fillRect(0, 0, 320, 240, TFT_BLUE);

    // if (touch.isTouched) {
    //     sprite.fillCircle(touch.point.x, touch.point.y, 15, TFT_WHITE);
    // }

    // sprite.pushSprite(0, 0);
}