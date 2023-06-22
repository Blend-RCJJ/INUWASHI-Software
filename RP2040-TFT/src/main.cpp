#include <Arduino.h>

#include <exception>

#include "neopixel.h"
#define NEO_PWR 11
#define NEOPIX 12
Adafruit_NeoPixel pixels(1, NEOPIX, NEO_GRB + NEO_KHZ800);
LED led(&pixels, NEO_PWR);

#include "./ui_kit/ui_kit.h"

UI_KIT ui;

void setup() {
    Serial.begin(115200);
    ui.init();
}

void loop() {
    ui.touchUpdate();
    ui.publish();

    led.normalSign();
}