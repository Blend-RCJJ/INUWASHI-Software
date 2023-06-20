#include <Arduino.h>

#include "./img/blend.h"
#include "./img/ui-image/ui-image.h"

#include "./device/device.h"

void setup() {
    Serial.begin(115200);

    touch.begin();
    display.init();

    display.setBackgroundImage(image_data_blend);
    display.publish();

    led.normalSign();
}

int mode = 0;
int oldMode = 1;

void loop() {
    touch.read();

    // sprite.fillRect(0, 0, 320, 240, TFT_BLUE);

    // if (touch.isTouched) {
    //     sprite.fillCircle(touch.point.x, touch.point.y, 15, TFT_WHITE);
    // }


    // sprite.pushSprite(0, 0);
}