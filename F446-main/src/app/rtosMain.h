#ifndef _RTOS_MAIN_H_
#define _RTOS_MAIN_H_

#include "../device/device.h"

extern RTOS_Kit app;

void mainApp(App) {
    gyro.read();
    servo.drive(100, 0);

    app.delay(10);
}

#endif