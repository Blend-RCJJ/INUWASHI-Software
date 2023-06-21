#include "display.h"

DISPLAY_DEVICE::DISPLAY_DEVICE(TFT_eSPI* tftPtr, TFT_eSprite* spritePtr) {
    pinMode(backlightPin, OUTPUT);
    digitalWrite(backlightPin, HIGH);

    this->tftPtr = tftPtr;
    this->spritePtr = spritePtr;
}

void DISPLAY_DEVICE::init(void) {
    spritePtr->createSprite(320, 240);
    spritePtr->setColorDepth(7);

    tftPtr->begin();
    tftPtr->setAddrWindow(0, 0, 240, 320);
    tftPtr->setRotation(1);
    tftPtr->setSwapBytes(true);
}

void DISPLAY_DEVICE::setSPIClockFast(void) {
    SPI.beginTransaction(SPISettings(SPI_FREQUENCY, MSBFIRST, TFT_SPI_MODE));
    SPI.endTransaction();
}

void DISPLAY_DEVICE::setBackgroundImage(const uint16_t* imagePtr) {
    spritePtr->pushImage(0, 0, 320, 240, imagePtr);
}

void DISPLAY_DEVICE::publish(void) {
    setSPIClockFast();
    spritePtr->pushSprite(0, 0);
    digitalWrite(backlightPin, LOW);
}