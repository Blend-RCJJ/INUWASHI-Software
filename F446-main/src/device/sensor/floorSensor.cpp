#include "floorSensor.h"

extern Adafruit_NeoPixel stripFloor;

void FLOOR_SENSOR::init(void) {
    stripFloor.begin();
    stripFloor.setBrightness(brightness);
    stripFloor.show();
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