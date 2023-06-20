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
    led.normalSign();
}

void loop() {
    static int mode = 0;

    ui.showSettingImage(mode);

    mode++;
    mode %= 7;

    delay(300);

    // touch.read();

    // sprite.fillRect(0, 0, 320, 240, TFT_BLUE);

    // if (touch.isTouched) {
    //     sprite.fillCircle(touch.point.x, touch.point.y, 15, TFT_WHITE);
    // }

    // sprite.pushSprite(0, 0);
}