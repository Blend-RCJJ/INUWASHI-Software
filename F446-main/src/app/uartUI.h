#ifndef _UI_KIT_H_
#define _UI_KIT_H_

#include <Arduino.h>

#include "../device/device.h"
#include "./rtosLocation.h"

void settingWrite() {
    // flag
    uart4.write('U');
    uart4.write('I');

    // mode
    uart4.write(13);  // setting 13 byte

    // gyro
    uart4.write(highByte(gyro.deg));
    uart4.write(lowByte(gyro.deg));

    uart4.write(0);

    // led buzz
    uart4.write(0B11111111);

    // load cell
    uart4.write(loadcell.load[0]);
    uart4.write(loadcell.load[1]);

    // tof
    uart4.write(highByte(tof.val[0]));
    uart4.write(lowByte(tof.val[0]));

    // floor
    uart4.write(182);
    uart4.write(28);
    uart4.write(88);
    uart4.write(0);

    // check sum
    uart4.write(0);
}

void runningWrite(void) {
    // flag
    uart4.write('U');
    uart4.write('I');

    // mode
    uart4.write(8);  // running 8 byte

    // gyro
    uart4.write(highByte(gyro.deg));
    uart4.write(lowByte(gyro.deg));

    // coordinate
//send in 2 byte
    uart4.write(highByte((int)location.coordinateX));
    uart4.write(lowByte((int)location.coordinateX));

    uart4.write(highByte((int)location.coordinateY));
    uart4.write(lowByte((int)location.coordinateY));

    // wall
    uart4.write(0);

    // check sum
    uart4.write(0);
}

#endif