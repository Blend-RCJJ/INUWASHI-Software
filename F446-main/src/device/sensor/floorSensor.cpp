#include "floorSensor.h"

extern Adafruit_NeoPixel stripFloor;

void FLOOR_SENSOR::init(void) {
    stripFloor.begin();
    stripFloor.setBrightness(brightness);
    stripFloor.show();

    pinMode(PC0, INPUT);
}

unsigned long FLOOR_SENSOR::colorRGB(int red, int green, int blue) {
    return stripFloor.Color(red, green, blue);
}

unsigned long FLOOR_SENSOR::colorHSV(int hue, int saturation, int brightness) {
    return stripFloor.ColorHSV(hue * 256, saturation, brightness);
}

void FLOOR_SENSOR::setFloorColor(unsigned long color) {
    for (int i = 0; i < 4; i++) {
        stripFloor.setPixelColor(i, color);
    }
    stripFloor.show();
}

void FLOOR_SENSOR::colorJudgment(void) {
    if (redVal < 200 && (blankVal > 80 && blankVal < 250) && blueVal < 200) {
        isBlue = true;
        // 青
    } else if (redVal > 300 && blankVal > 400 && blueVal > 300) {
        isBlack = true;
        // 黒
    } else {
        isBlue = false;
        isBlack = false;
    }
}