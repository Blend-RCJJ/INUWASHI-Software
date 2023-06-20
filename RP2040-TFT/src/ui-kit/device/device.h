#ifndef _DEVICE_H_
#define _DEVICE_H_

// touch screen
#include "touchscreen.h"
XPT2046_Touchscreen touchscreenDevice(7);
TOUCHSCREEN touch(&touchscreenDevice,7);

// display
#include "display.h"
TFT_eSPI tft = TFT_eSPI();
TFT_eSprite sprite = TFT_eSprite(&tft);
DISPLAY_DEVICE display(&tft, &sprite);

#endif  // _DEVICE_H_