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
    if (blankVal > 400 && blueVal > 250) {
        isBlack = true;
        isWhite = false;
        isBlue  = false;
        // 黒
    } else if ( (blankVal > 100 && blankVal < 650) && blueVal < 300) {
        isBlue  = true;
        isWhite = false;
        isBlack = false;
        // 青
    } else {
        isWhite = true;
        isBlue  = false;
        isBlack = false;
    }
}

// void FLOOR_SENSOR::tof_of_bottom_read(void) {

// }