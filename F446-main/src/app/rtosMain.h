#ifndef _RTOS_MAIN_H_
#define _RTOS_MAIN_H_

#include "../device/device.h"
#include "../kit/RTOS-Kit.h"
#include "./rtosIO.h"
#include "./rtosLocation.h"
#include "./rtosVictim.h"
#include "./algorithm.h"
#include "./search.h"

extern RTOS_Kit app;

int robotStaus = 0;

#define SPEED 50
#define WAIT 500
#define FORWARD 2500
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
    app.start(rightWallApp);
    app.start(DepthFirstSearchApp);
    app.start(AstarApp);
    app.start(adjustmentApp);
    static bool status = false;
    while (1) {
        if (ui.toggle) {
            if (status) {
                app.start(rightWallApp);
                app.start(locationApp);
                app.start(floorApp);
                status = false;
            }
        } else {
            app.stop(rightWallApp);
            app.stop(locationApp);
            app.stop(floorApp);

            servo.suspend = true;
            status     = true;
        }
        app.delay(period);
    }
}

#endif