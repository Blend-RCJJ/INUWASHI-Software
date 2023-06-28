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
    if (redVal > 800 && blankVal < 700 && blueVal < 700) {
        isBlue = true;
        // 青
    } else {
        isBlue = false;
    }
    if (redVal < 100 && blankVal < 100 && blueVal < 100) {
        isWhite = true;
        // 白
    } else {
        isWhite = false;
    }
    if (redVal > 900 && blankVal > 900 && blueVal > 900) {
        isBlack = true;
        // 黒
    } else {
        isBlack = false;
    }
}