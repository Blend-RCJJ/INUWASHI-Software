#ifndef _RTOS_MAIN_H_
#define _RTOS_MAIN_H_

#include "../device/device.h"
#include "../kit/RTOS-Kit.h"
#include "./rtosIO.h"

extern RTOS_Kit app;

#define SPEED 50
#define WAIT 500
#define FORWARD 2300
#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3
#define MAX_DISTANCE 800
#define FEEDBACK 30000  // 帰還開始時間(ms)

bool NorthWall = false;
bool EastWall  = false;
bool SouthWall = false;
bool WestWall = false;  // NOTE 絶対方位とA*で使うのでグローバル変数にしてます
const int radius = 20;

void rightWallApp(App);
void leftWallApp(App);
void absoluteDirection(App);
void monitorApp(App);
void adjustmentApp(App);

void mainApp(App) {
    app.start(sensorApp);
    // app.start(monitorApp);
    app.start(servoApp);
    app.start(adjustmentApp);
    app.start(rightWallApp);
    // app.start(leftWallApp);
    // app.start(monitorApp);

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

// void AstarApp(App) {  // FIXME 自己位置推定ないから動きません
//     app.delay(WAIT);
//     int Ndistance = MAX_DISTANCE;
//     int Edistance = MAX_DISTANCE;
//     int Sdistance = MAX_DISTANCE;
//     int Wdistance = MAX_DISTANCE;  // 値の初期化(最大値に設定)
//     bool status   = true;
//     app.delay(WAIT);
//     const int initialWall[4] = {(NorthWall), (EastWall), (SouthWall),
//                                 (WestWall)};  //(0,0)の壁の状態を記憶
//     while (1) {
//         app.delay(100);
//         if (millis() > FEEDBACK && servo.velocity == 50) {
//             if (status) {
//                 servo.velocity = 0;
//                 app.stop(rightWallApp);
//                 app.stop(leftWallApp);
//                 app.delay(WAIT);
//                 status = false;
//             }
//             app.delay(period);
//         MEASURE_DISTANCE:  // 最短経路の算出
//             if (!location.x && !location.y && initialWall[NORTH] == NorthWall
//             &&
//                 initialWall[EAST] == EastWall &&
//                 initialWall[SOUTH] == SouthWall &&
//                 initialWall[WEST] ==
//                     WestWall) {  //(0,0)かつスタート時の壁情報と一致
//                 servo.velocity = 0;
//                 servo.suspend  = true;
//                 app.stop(servoApp);
//                 app.delay(20000);
//             }

//             if (!NorthWall) {
//                 Ndistance = location.x * location.x +
//                             (location.y + 1) * (location.y + 1);
//             } else {
//                 Ndistance = MAX_DISTANCE;
//             }
//             if (!EastWall) {
//                 Edistance = (location.x + 1) * (location.x + 1) +
//                             location.y * location.y;
//             } else {
//                 Edistance = MAX_DISTANCE;
//             }
//             if (!SouthWall) {
//                 Sdistance = location.x * location.x +
//                             (location.y - 1) * (location.y - 1);
//             } else {
//                 Sdistance = MAX_DISTANCE;
//             }
//             if (!WestWall) {
//                 Wdistance = (location.x - 1) * (location.x - 1) +
//                             location.y * location.y;
//             } else {
//                 Wdistance = MAX_DISTANCE;
//             }
//         MOVE_COORDINATE
//             :  // FIXME
//                //
//                1マスぴったり進む方法が確立されていない&坂道来た時どうする？
//             if (Ndistance < Edistance && Ndistance < Sdistance &&
//                 Ndistance < Wdistance) {
//                 servo.angle    = 0;
//                 servo.velocity = 50;
//                 app.delay(2900);
//                 servo.velocity = 0;
//                 app.delay(1000);
//                 SouthWall = true;
//                 goto MEASURE_DISTANCE;

//             } else if (Sdistance < Edistance && Sdistance < Wdistance) {
//                 servo.angle    = 180;
//                 servo.velocity = 50;
//                 app.delay(2900);
//                 servo.velocity = 0;
//                 app.delay(1000);
//                 NorthWall = true;
//                 goto MEASURE_DISTANCE;

//             } else if (Edistance < Wdistance) {
//                 servo.angle    = 90;
//                 servo.velocity = 50;
//                 app.delay(2900);
//                 servo.velocity = 0;
//                 app.delay(1000);
//                 WestWall = true;
//                 goto MEASURE_DISTANCE;

//             } else {
//                 servo.angle    = 270;
//                 servo.velocity = 50;
//                 app.delay(2900);
//                 servo.velocity = 0;
//                 app.delay(1000);
//                 EastWall = true;
//                 goto MEASURE_DISTANCE;
//             }
//         } else {
//             app.delay(10);
//         }
//     }
// }

void monitorApp(App) {
    while (1) {
        uart3.print(radius + tof.val[9]);
        uart3.print(" ");
        uart3.println(0.8660254038 * (radius + tof.val[8]));
        app.delay(500);
    }
}

void adjustmentApp(App) {
    while (1) {
        app.delay(period);
        if(tof.val[3] < 230){
            if(radius + tof.val[3] + 20 < 0.8660254038 * (radius + tof.val[2])){//√3/2
                servo.correctingAngle += 1;//一度ずつ補正
            }
        }
    }
}

#endif