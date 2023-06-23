#ifndef _ALGORITHM_H_
#define _ALGORITHM_H_

#include "../device/device.h"
#include "../kit/RTOS-Kit.h"
#include "./rtosIO.h"
#include "./rtosLocation.h"
#include "./rtosVictim.h"
#include "./search.h"

extern RTOS_Kit app;

#define SPEED 80
#define WAIT 500
#define FORWARD 2500
#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3
#define MAX_DISTANCE 800
#define FEEDBACK 300000  // 帰還開始時間(ms)

void rightWallApp(App);
void leftWallApp(App);
void monitorApp(App);
void adjustmentApp(App);
void DepthFirstSearchApp(App);

void AstarApp(App) {  // NOTE 動いた
    app.delay(WAIT);
    int Ndistance       = MAX_DISTANCE;
    int Edistance       = MAX_DISTANCE;
    int Sdistance       = MAX_DISTANCE;
    int Wdistance       = MAX_DISTANCE;  // 値の初期化(最大値に設定)
    bool virtualWall[4] = {false};
    bool status         = true;
    app.delay(WAIT);
    const int initialWall[4] = {(tof.isNorthWall), (tof.isEastWall),
                                (tof.isSouthWall),
                                (tof.isWestWall)};  //(0,0)の壁の状態を記憶
    while (1) {
        app.delay(100);
        if (millis() > FEEDBACK && servo.velocity == 50) {
            if (status) {
                buzzer.bootSound();
                servo.velocity = 0;
                servo.suspend  = true;
                app.stop(rightWallApp);
                app.stop(leftWallApp);
                app.stop(DepthFirstSearchApp);
                app.delay(WAIT);
                servo.suspend = false;
                status        = false;
            }
            app.delay(period);
        MEASURE_DISTANCE:  // 最短経路の算出
            oldCoordinateX = location.coordinateX;
            oldCoordinateY = location.coordinateY;
            if ((-1 <= location.x && location.x <= 1) &&
                (-1 <= location.y && location.y <= 1) &&
                initialWall[NORTH] == tof.isNorthWall &&
                initialWall[EAST] == tof.isEastWall &&
                initialWall[SOUTH] == tof.isSouthWall &&
                initialWall[WEST] ==
                    tof.isWestWall) {  //(0,0)かつスタート時の壁情報と一致+-1まで許容
                servo.velocity = 0;
                servo.suspend  = true;
                app.stop(servoApp);
                app.delay(20000);
            }

            if (!tof.isNorthWall && !virtualWall[NORTH]) {
                Ndistance = location.x * location.x +
                            (location.y + 1) * (location.y + 1);
            } else {
                Ndistance = MAX_DISTANCE;
            }
            if (!tof.isEastWall && !virtualWall[EAST]) {
                Edistance = (location.x + 1) * (location.x + 1) +
                            location.y * location.y;
            } else {
                Edistance = MAX_DISTANCE;
            }
            if (!tof.isSouthWall && !virtualWall[SOUTH]) {
                Sdistance = location.x * location.x +
                            (location.y - 1) * (location.y - 1);
            } else {
                Sdistance = MAX_DISTANCE;
            }
            if (!tof.isWestWall && !virtualWall[WEST]) {
                Wdistance = (location.x - 1) * (location.x - 1) +
                            location.y * location.y;
            } else {
                Wdistance = MAX_DISTANCE;
            }
            for (int i = 0; i < 4; i++) {
                if (virtualWall[i]) {
                    virtualWall[i] = false;
                }
            }
        MOVE_COORDINATE:  // FIXME
            // 1マスぴったり進む方法が確立されていない&坂道来た時どうする？
            if (Ndistance < Edistance && Ndistance < Sdistance &&
                Ndistance < Wdistance) {
                servo.angle = 0 + servo.isCorrectingAngle;
                while (abs(location.coordinateX - oldCoordinateX) < 300 &&
                       abs(location.coordinateY - oldCoordinateY) < 300) {
                    if (tof.val[0] < 140) {
                        goto MEASURE_DISTANCE;
                        break;
                    }
                    servo.velocity = SPEED;
                    app.delay(period);
                }
                servo.velocity = 0;
                servo.suspend  = true;
                app.delay(WAIT);
                servo.suspend  = false;
                virtualWall[2] = true;  // 後方に仮想壁
                goto MEASURE_DISTANCE;

            } else if (Sdistance < Edistance && Sdistance < Wdistance) {
                servo.angle    = 180 + servo.isCorrectingAngle;
                servo.velocity = 50;
                while (abs(location.coordinateX - oldCoordinateX) < 300 &&
                       abs(location.coordinateY - oldCoordinateY) < 300) {
                    if (tof.val[0] < 140) {
                        goto MEASURE_DISTANCE;
                        break;
                    }
                    servo.velocity = SPEED;
                    app.delay(period);
                }
                servo.velocity = 0;
                servo.suspend  = true;
                app.delay(WAIT);
                servo.suspend  = false;
                virtualWall[0] = true;
                goto MEASURE_DISTANCE;

            } else if (Edistance < Wdistance) {
                servo.angle    = 90 + servo.isCorrectingAngle;
                servo.velocity = 50;
                while (abs(location.coordinateX - oldCoordinateX) < 300 &&
                       abs(location.coordinateY - oldCoordinateY) < 300) {
                    if (tof.val[0] < 140) {
                        goto MEASURE_DISTANCE;
                        break;
                    }
                    servo.velocity = SPEED;
                    app.delay(period);
                }
                servo.velocity = 0;
                servo.suspend  = true;
                app.delay(WAIT);
                servo.suspend  = false;
                virtualWall[3] = true;
                goto MEASURE_DISTANCE;

            } else {
                servo.angle    = 270 + servo.isCorrectingAngle;
                servo.velocity = 50;
                while (abs(location.coordinateX - oldCoordinateX) < 300 &&
                       abs(location.coordinateY - oldCoordinateY) < 300) {
                    if (tof.val[0] < 140) {
                        goto MEASURE_DISTANCE;
                        break;
                    }
                    servo.velocity = SPEED;
                    app.delay(period);
                }
                servo.velocity = 0;
                servo.suspend  = true;
                app.delay(WAIT);
                servo.suspend  = false;
                virtualWall[1] = true;
                goto MEASURE_DISTANCE;
            }
        } else {
            app.delay(period * 5);
        }
    }
}

void monitorApp(App) {
    while (1) {
        // for (int i = 0; i < 16; i++) {
        //     uart1.print(tof.val[i]);
        //     uart1.print("\t");
        // }
        // uart1.println("\t");
        app.delay(100);
    }
}

void DepthFirstSearchApp(App) {  // NOTE 二方向以上進める座標を記録する変数
                                 // "JCT"
    static bool JCT[MAP_ORIGIN * 2][MAP_ORIGIN * 2] = {false};
    static bool turn                                = false;
    app.delay(WAIT);
    while (1) {
        virtualWall[location.x + MAP_ORIGIN][location.y + MAP_ORIGIN] =
            true;  // 仮想壁
        app.delay(period);

        if (tof.val[0] > 450 && (tof.val[4] > 230 || tof.val[12] > 230)) {
            JCT[location.x + MAP_ORIGIN][location.y + MAP_ORIGIN] = true;
        }
        if (!isRightWallApp &&
            JCT[location.x + MAP_ORIGIN][location.y + MAP_ORIGIN] &&
            (tof.val[4] > 230 || tof.val[12] > 230)) {
            servo.suspend = true;
            app.delay(WAIT);
            servo.suspend = false;
            app.stop(leftWallApp);
            app.start(rightWallApp);
        }

        if (!tof.isNotFront) {
            app.stop(rightWallApp);
            app.stop(adjustmentApp);
            servo.suspend = true;
            app.delay(WAIT);
            servo.suspend = false;
            servo.angle += 90;
            servo.velocity = 0;
            app.delay(WAIT * 2);
            servo.suspend = true;
            app.delay(WAIT);
            servo.suspend = false;
            servo.angle += 90;
            app.delay(WAIT * 3);
            app.start(leftWallApp);
            app.restart(adjustmentApp);
            app.delay(period);

        }  // 前方+左右に壁があったら反転して左壁追従

        if (checkPointX == location.x && checkPointY == location.y &&
            oldmillis + 10000 < millis()) {  // DFS開始地点に戻ってきたら反転
            oldmillis   = millis();
            checkPointX = MAP_ORIGIN;
            checkPointY = MAP_ORIGIN;
            app.delay(period);
            app.stop(rightWallApp);
            servo.angle += 180;
            app.delay(WAIT * 2);
            app.start(rightWallApp);
        }
    }
}

#endif