#ifndef _DEVICE_H_
#define _DEVICE_H_

// NeoPixel
#include "neopixel.h"
#define NEO_PWR 11
#define NEOPIX 12
Adafruit_NeoPixel pixels(1, NEOPIX, NEO_GRB + NEO_KHZ800);
LED led(&pixels, NEO_PWR);

//touch screen
#include "touchscreen.h"
XPT2046_Touchscreen touchscreenDevice(7);
TOUCHSCREEN touch(&touchscreenDevice,7);


#endif  // _DEVICE_H_