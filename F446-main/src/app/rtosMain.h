#ifndef _RTOS_MAIN_H_
#define _RTOS_MAIN_H_

#include "../device/device.h"
#include "./rtosIO.h"

extern RTOS_Kit app;

void mainApp(App) {
    app.start(sensorReadingApp);
    app.start(servoApp);
    
    while (1) {
    }
}

#endif