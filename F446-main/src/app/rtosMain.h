#ifndef _RTOS_MAIN_H_
#define _RTOS_MAIN_H_

#include "../device/device.h"
#include "../kit/RTOS-Kit.h"
#include "./rtosIO.h"

extern RTOS_Kit app;

#define SPEED 50
#define PERIOD 10
#define WAIT 500
#define FORWARD 2300

void rightWallApp(App);
void leftWallApp(App);

void mainApp(App) {
    app.start(sensorApp);
    app.start(servoApp);
    // app.start(rightWallApp);
    app.start(leftWallApp);

    while (1) {
        // servo.suspend = !ui.toggle;

        // servo.angle = 0;
        // servo.velocity = 100;

        // uart1.println(millis());  // NOTE: 生死確認
        app.delay(period);
    }
}

void rightWallApp(App) {
    while (1) {
        servo.velocity = SPEED;
        servo.suspend  = false;
        app.delay(PERIOD);

        if (tof.val[3] > 300 && tof.val[4] > 250 &&
            !gyro.slope) {  // 右壁が消えた時の処理
            servo.velocity = 0;
            servo.suspend  = true;
            app.delay(WAIT);
            servo.suspend = false;
            servo.angle += 90;
            servo.velocity = 0;
            servo.suspend  = true;
            app.delay(WAIT);
            servo.suspend  = false;
            servo.velocity = SPEED;
            app.delay(FORWARD);  // 次のタイルまで前進
        }

        if (tof.val[0] < 140 && !gyro.slope) {  // 前に壁が来た時の処理
            servo.velocity = 0;
            servo.suspend  = true;
            app.delay(WAIT);
            servo.suspend = false;
            servo.angle -= 90;
            app.delay(WAIT);
        }
    }
}

void leftWallApp(App) {
    while (1) {
        servo.velocity = SPEED;
        app.delay(PERIOD);

        if (tof.val[9] > 300 && tof.val[8] > 250 &&
            !gyro.slope) {  // 左壁が消えた時の処理
            servo.velocity = 0;
            servo.suspend  = true;
            app.delay(WAIT);
            servo.suspend = false;
            servo.angle -= 90;
            servo.velocity = 0;
            servo.suspend  = true;
            app.delay(WAIT);
            servo.suspend  = false;
            servo.velocity = SPEED;
            app.delay(FORWARD);  // 次のタイルまで前進
        }

        if (tof.val[0] < 140 && !gyro.slope) {  // 前に壁が来た時の処理
            servo.velocity = 0;
            servo.suspend  = true;
            app.delay(WAIT);
            servo.suspend = false;
            servo.angle += 90;
            app.delay(WAIT);
        }
    }
}

#endif