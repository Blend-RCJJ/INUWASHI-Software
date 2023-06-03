#ifndef _RTOS_UI_H_
#define _RTOS_UI_H_

#include "../device/device.h"
#include "../kit/RTOS-Kit.h"

extern RTOS_Kit app;

void victimDetectionUIApp(App) {
    buzzer.matsukenShogun();
    while (true) {
        app.delay(10000);
    }
}

#endif