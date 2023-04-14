#ifndef _RTOS_MAIN_H_
#define _RTOS_MAIN_H_

#include "../device/device.h"
#include "./rtosIO.h"

extern RTOS_Kit app;

void mainApp(App) {
    app.start(sensorApp);
    app.start(servoApp);

    while (1) {
        servo.suspend = !ui.toggle;

        servo.angle = 0;
        servo.velocity = 100;

        uart1.println(millis());  // NOTE: 生死確認
        app.delay(period);
    }
}

#endif