#include <Arduino.h>

#include <exception>

#include "neopixel.h"
#define NEO_PWR 11
#define NEOPIX 12
Adafruit_NeoPixel pixels(1, NEOPIX, NEO_GRB + NEO_KHZ800);
LED led(&pixels, NEO_PWR);

#include "./ui_kit/ui_kit.h"
UI_KIT ui;

#include "./ui_kit/device/touchscreen.h"
XPT2046_Touchscreen touchscreenDevice(7);
TOUCHSCREEN touch(&touchscreenDevice, 7);

#include "./ui_kit/device/display.h"
TFT_eSPI tft = TFT_eSPI();
TFT_eSprite sprite = TFT_eSprite(&tft);
DISPLAY_DEVICE display(&tft, &sprite);

#include "./ui_kit/databox.h"
DATA_BOX data;

void setup() {
    Serial.begin(115200);

    ui.init();
}

void loop() {
    ui.touchUpdate();
    ui.publish();

    led.normalSign();
}