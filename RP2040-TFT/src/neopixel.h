#ifndef _NEOPIXEL_H_
#define _NEOPIXEL_H_

#include <Adafruit_NeoPixel.h>

class LED {
   public:
    Adafruit_NeoPixel* ptr;
    LED(Adafruit_NeoPixel* ptr, int pwrPin) {
        this->ptr = ptr;

        pinMode(pwrPin, OUTPUT);
        digitalWrite(pwrPin, HIGH);
    }

    void normalSign(void) {
        ptr->setPixelColor(0, 0, 80, 255);
        ptr->setBrightness(150);
        ptr->show();
    }

    void errorSign(void) {
        ptr->setBrightness(150);

        while (true) {
            ptr->setPixelColor(0, (millis() / 200) % 2 * 255, 0, 0);
            ptr->show();
        }
    }

   private:
    const int brightness = 150;
    const unsigned long normalSignColor = 0x0050FF;
};

#endif