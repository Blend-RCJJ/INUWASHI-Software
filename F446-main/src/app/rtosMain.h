#ifndef _RTOS_MAIN_H_
#define _RTOS_MAIN_H_

#include <Arduino.h>

#include "../device/device.h"
#include "../kit/RTOS-Kit.h"
#include "./algorithm.h"
#include "./rtosIO.h"
#include "./rtosLocation.h"
#include "./rtosVictim.h"
#include "./search.h"
#include "./uartUI.h"

extern RTOS_Kit app;
int robotStaus = 0;

#define SPEED 100
#define WAIT 500
#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3
#define MAX_DISTANCE 800
#define FEEDBACK 300000  // 帰還開始時間(ms)

void mainApp(App) {
    app.start(ledApp);
    app.start(sensorApp);
    app.start(monitorApp);
    app.start(servoApp);
    app.start(AstarApp);
    static bool status = false;
    while (1) {
        if (ui.toggle) {
            if (status) {
                    app.start(rightWallApp);
                    app.start(adjustmentApp);
                    app.start(locationApp);
                    app.start(DepthFirstSearchApp);
                    app.start(floorApp);
                    app.start(victimNotifyApp);
                    location.coordinateX = 0;
                    location.coordinateY = 0;
                    servo.suspend = false;
                    servo.velocity = SPEED;
                    status = false;
            }

            runningWrite();
        } else {
            app.stop(rightWallApp);
            app.stop(leftWallApp);
            app.stop(adjustmentApp);
            app.stop(locationApp);
            app.stop(DepthFirstSearchApp);
            app.stop(floorApp);
            app.stop(AstarApp);

            servo.suspend = true;
            servo.velocity = 0;
            status        = true;

            settingWrite();
        }

        app.delay(period);
    }
}

#endif