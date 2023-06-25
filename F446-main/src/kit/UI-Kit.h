#ifndef _UI_KIT_H_
#define _UI_KIT_H_

#include <Arduino.h>

#include "../device/device.h"
#include "../app/rtosLocation.h"

class UI_Kit {
   public:
    HardwareSerial* uartPtr;

    UI_Kit(HardwareSerial* uartPtr) {
        this->uartPtr = uartPtr;
    }

    void settingWrite() {
        // flag
        uartPtr->write('U');
        uartPtr->write('I');

        // mode
        uartPtr->write(13);  // setting 13 byte

        // gyro
        uartPtr->write(highByte(gyro.deg));
        uartPtr->write(lowByte(gyro.deg));

        uartPtr->write(0);

        // led buzz
        uartPtr->write(0B11111111);

        // load cell
        uartPtr->write(loadcell.load[0]);
        uartPtr->write(loadcell.load[1]);

        // tof
        uartPtr->write(highByte(tof.val[0]));
        uartPtr->write(lowByte(tof.val[0]));

        // floor
        uartPtr->write(182);
        uartPtr->write(28);
        uartPtr->write(88);
        uartPtr->write(0);

        // check sum
        uartPtr->write(0);
    }

    void runningWrite(void) {
        // flag
        uartPtr->write('U');
        uartPtr->write('I');

        // mode
        uartPtr->write(8);  // running 8 byte

        // gyro
        uartPtr->write(highByte(gyro.deg));
        uartPtr->write(lowByte(gyro.deg));

        // coordinate
        uartPtr->write(highByte((int)location.coordinateX));
        uartPtr->write(lowByte((int)location.coordinateX));

        uartPtr->write(highByte((int)location.coordinateY));
        uartPtr->write(lowByte((int)location.coordinateY));

        // wall
        uartPtr->write(0);

        // check sum
        uartPtr->write(0);
    }

   private:
};

#endif