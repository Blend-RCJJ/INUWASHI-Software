#ifndef _RTOS_MAIN_H_
#define _RTOS_MAIN_H_

#include "../device/device.h"
#include "../kit/RTOS-Kit.h"
#include "./rtosIO.h"

extern RTOS_Kit app;

#define SPEED 50
#define WAIT 500
#define FORWARD 2300

bool NorthWall = false;
bool EastWall  = false;
bool SouthWall = false;
bool WestWall  = false;

void rightWallApp(App);
void leftWallApp(App);
void absoluteDirection(App);

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
        app.delay(period);

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
        app.delay(period);

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

void absoluteDirectionApp(App) {  // 絶対方位で壁を見るApp
    while (1) {
        app.delay(100);
        if (gyro.deg > 350 || gyro.deg < 10) {
            if (tof.val[0] > 230) {
                NorthWall = false;
            } else {
                NorthWall = true;
            }

            if (tof.val[3] > 230) {
                EastWall = false;
            } else {
                EastWall = true;
            }

            if (tof.val[6] > 230) {
                SouthWall = false;
            } else {
                SouthWall = true;
            }

            if (tof.val[9] > 230) {
                WestWall = false;
            } else {
                WestWall = true;
            }
        } else if (gyro.deg > 80 && gyro.deg < 100) {
            if (tof.val[9] > 230) {
                NorthWall = false;
            } else {
                NorthWall = true;
            }

            if (tof.val[0] > 230) {
                EastWall = false;
            } else {
                EastWall = true;
            }

            if (tof.val[3] > 230) {
                SouthWall = false;
            } else {
                SouthWall = true;
            }

            if (tof.val[6] > 230) {
                WestWall = false;
            } else {
                WestWall = true;
            }
        } else if (gyro.deg > 170 && gyro.deg < 190) {
            if (tof.val[6] > 230) {
                NorthWall = false;
            } else {
                NorthWall = true;
            }

            if (tof.val[9] > 230) {
                EastWall = false;
            } else {
                EastWall = true;
            }

            if (tof.val[0] > 230) {
                SouthWall = false;
            } else {
                SouthWall = true;
            }

            if (tof.val[3] > 230) {
                WestWall = false;
            } else {
                WestWall = true;
            }
        } else if (gyro.deg > 260 && gyro.deg < 280) {
            if (tof.val[3] > 230) {
                NorthWall = false;
            } else {
                NorthWall = true;
            }

            if (tof.val[6] > 230) {
                EastWall = false;
            } else {
                EastWall = true;
            }

            if (tof.val[9] > 230) {
                SouthWall = false;
            } else {
                SouthWall = true;
            }

            if (tof.val[0] > 230) {
                WestWall = false;
            } else {
                WestWall = true;
            }
        } else {
            app.delay(period * 10);  // A*との兼ね合いで制御周期落としてる
        }
    }
}

#endif