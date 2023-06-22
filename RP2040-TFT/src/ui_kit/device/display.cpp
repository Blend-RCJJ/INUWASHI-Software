#include "display.h"

DISPLAY_DEVICE::DISPLAY_DEVICE(TFT_eSPI* tftPtr, TFT_eSprite* spritePtr) {
    pinMode(backlightPin, OUTPUT);
    // digitalWrite(backlightPin, HIGH);

    digitalWrite(backlightPin, LOW);

    this->tftPtr = tftPtr;
    this->spritePtr = spritePtr;
}

void DISPLAY_DEVICE::init(void) {
    spritePtr->createSprite(320, 240);
    spritePtr->setColorDepth(5);

    tftPtr->begin();
    tftPtr->setRotation(1);

    pinMode(TFT_CS, OUTPUT);
}

void DISPLAY_DEVICE::setSPIClockFast(void) {
    SPI.beginTransaction(SPISettings(SPI_FREQUENCY, MSBFIRST, TFT_SPI_MODE));
}

void DISPLAY_DEVICE::setBackgroundImage(const uint16_t* imagePtr) {
    spritePtr->pushImage(0, 0, 320, 240, imagePtr);
}

void DISPLAY_DEVICE::publish(int x, int y) {
    setSPIClockFast();
    spritePtr->pushSprite(x, y);
    spritePtr->deleteSprite();
    digitalWrite(backlightPin, LOW);
}

void DISPLAY_DEVICE::createSprite(int x, int y) {
    spritePtr->createSprite(x, y);
    spritePtr->setColorDepth(5);
}