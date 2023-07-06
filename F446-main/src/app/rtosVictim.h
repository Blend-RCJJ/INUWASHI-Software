#ifndef _RTOS_VICTIM_H_
#define _RTOS_VICTIM_H_

#include "../device/device.h"
#include "../kit/RTOS-Kit.h"
#include "./algorithm/location.h"

extern RTOS_Kit app;

extern bool isRightWallApp;
extern void rightWallApp(App);
extern void leftWallApp(App);
extern void DepthFirstSearchApp(App);
extern void floorApp(App);

#define SPEED 100

void victimNotifyApp(App) {
    while (1) {
        int rescueKitNum = 0;

        while (1) {
            if (victim.isRightOrLeft != 0 && ui.toggle == true) {
                if (victim.place[location.x + 20][location.y + 20] == false) {
                    if (victim.isRightOrLeft == RIGHT && tof.val[4] < 140 &&
                        tof.val[5] < 200) {
                        break;
                    }

                    if (victim.isRightOrLeft == LEFT && tof.val[12] < 140 &&
                        tof.val[11] < 200) {
                        break;
                    }
                }
            }

            app.delay(10);
        }

        app.stop(rightWallApp);
        app.stop(leftWallApp);
        app.stop(DepthFirstSearchApp);
        app.stop(floorApp);

        victim.place[location.x + 20][location.y + 20] = true;
        victim.isDetected                              = true;

        servo.velocity = 0;
        servo.suspend  = true;

        switch (victim.id) {
            case VICTIM_H:
                buzzer.sambaII();
                break;

            case VICTIM_S:
                buzzer.tokyoOndo();
                break;

            case VICTIM_U:
                buzzer.sakura();
                break;

            case VICTIM_RED:
                buzzer.shoten();
                break;

            case VICTIM_YELLOW:
                buzzer.shogun();
                break;

            case VICTIM_GREEN:
                buzzer.yuyake();
                break;

            default:
                break;
        }

        switch (victim.id) {
            case VICTIM_H:
                rescueKitNum = 3;
                break;

            case VICTIM_S:
                rescueKitNum = 2;
                break;

            case VICTIM_RED:
                rescueKitNum = 1;
                break;

            case VICTIM_YELLOW:
                rescueKitNum = 1;
                break;

            default:
                break;
        }

        app.delay(100);
        buzzer.rescueKit(rescueKitNum);
        servo.rescueKit(rescueKitNum, victim.isRightOrLeft);
        app.delay(100);

        servo.suspend  = false;
        servo.velocity = SPEED;

        victim.isDetected = false;

        app.restart(DepthFirstSearchApp);
        app.restart(floorApp);
        // if (isRightWallApp) {
        app.start(rightWallApp);
        // } else {
        //     app.start(leftWallApp);
        // }
    }
}

#endif