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
    static int oldMode = 0;

    static int mode = 0;
    static unsigned long timer = 0;

    ui.touchUpdate();

    if (ui.goToHome) {
        ui.goToHome = false;
        mode = 2;
    }

    if (millis() - timer > 100) {
        ui.showSettingImage(mode);
        timer = millis();
        mode = 0;
    }

    oldMode = mode;
}