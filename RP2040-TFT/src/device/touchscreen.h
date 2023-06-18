#ifndef _TOUCHSCREEN_H_
#define _TOUCHSCREEN_H_

#include <XPT2046_Touchscreen.h>

class COORDINATE {
   public:
    COORDINATE(int x, int y) {
        this->x = x;
        this->y = y;
    }

    int x;
    int y;

   private:
};

class TOUCHSCREEN {
   public:
    XPT2046_Touchscreen* ptr;

    TOUCHSCREEN(XPT2046_Touchscreen* ptr, const int csPin) {
        this->ptr = ptr;
        this->csPin = csPin;
    }

    void begin(void) {
        pinMode(csPin, OUTPUT);

        ptr->begin();
        ptr->setRotation(3);
    }

    COORDINATE raw = COORDINATE(0, 0);
    COORDINATE point = COORDINATE(0, 0);

    bool isTouched = false;

    void read(void) {
        digitalWrite(csPin, LOW);
        TS_Point p = ptr->getPoint();

        raw.x = p.x;
        raw.y = p.y;

        point.x =
            constrain(map(p.x, upperLeft.x, bottomRight.x, 0, 320), 0, 320);
        point.y =
            constrain(map(p.y, upperLeft.y, bottomRight.y, 0, 240), 0, 240);

        isTouched = ptr->touched();
        digitalWrite(csPin, HIGH);
    }

   private:
    COORDINATE upperLeft = COORDINATE(250, 250);
    COORDINATE bottomRight = COORDINATE(3700, 3800);

    int csPin;
};

#endif
