#ifndef _DISPLAY_H_
#define _DISPLAY_H_

#include <Arduino.h>
#include <TFT_eSPI.h>

#define ARR_SIZE 76800

class DISPLAY_DEVICE {
   public:
    TFT_eSPI* tftPtr;
    TFT_eSprite* spritePtr;

    DISPLAY_DEVICE(TFT_eSPI* tftPtr, TFT_eSprite* spritePtr);

    void init(void);
    void setSPIClockFast(void);

    void publish(void);
    void setBackgroundImage(const uint16_t *imagePtr);

   private:
    const int backlightPin = 29;
};

#endif