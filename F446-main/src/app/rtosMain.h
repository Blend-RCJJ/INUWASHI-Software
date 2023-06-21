#ifndef _RTOS_MAIN_H_
#define _RTOS_MAIN_H_

#include "../device/device.h"
#include "../kit/RTOS-Kit.h"
#include "./rtosIO.h"
#include "./rtosLocation.h"
#include "./rtosVictim.h"

extern RTOS_Kit app;

int robotStaus = 0;

#define SPEED 50
#define WAIT 500
#define FORWARD 2700
#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3
#define MAX_DISTANCE 800
#define FEEDBACK 300000  // 帰還開始時間(ms)

const int radius = 20;
bool virtualWall[MAP_ORIGIN * 2][MAP_ORIGIN * 2] = {false};
bool isRightWallApp = false;
bool oldstatus = false;

void rightWallApp(App);
void leftWallApp(App);
void monitorApp(App);
void adjustmentApp(App);
void DepthFirstSearchApp(App);
void AstarApp(App);
void adjustmentApp(App);

void mainApp(App) {
    app.start(ledApp);
    app.start(sensorApp);
    app.start(monitorApp);
    app.start(servoApp);
    // app.start(rightWallApp);
    // app.start(DepthFirstSearchApp);
    // app.start(AstarApp);
    // app.start(adjustmentApp);
    while (1) {
        uart1.print(loadcell.load[0]);
        uart1.print("\t");
        uart1.println(loadcell.load[1]);
            //     if (oldstatus) {
            //         app.start(rightWallApp);
            //         app.start(locationApp);
            //         oldstatus = false;
            //     }
            // } else {
            //     app.stop(rightWallApp);
            //     app.stop(locationApp);

            //     servo.suspend = true;
            //     oldstatus     = true;

            // app.restart(victimNotifyApp);
            // app.delay(12000);
            // app.stop(ledApp);
        // }
        app.delay(period);
    }
}

void rightWallApp(App) {
    static bool DFS = false;
    app.delay(WAIT);
    while (1) {
        servo.velocity = SPEED;
        servo.suspend = false;
        isRightWallApp = true;
        DFS = false;
        app.delay(period);

        if (tof.val[0] < 140 && !gyro.slope) {  // 前に壁が来た時の処理
            DFS = true;
            servo.velocity = 0;
            servo.suspend = true;
            app.delay(WAIT);
            servo.suspend = false;
            servo.angle -= 90;
            app.delay(WAIT);
        }

        if (virtualWall[location.x + MAP_ORIGIN][location.y + MAP_ORIGIN + 1] &&
            gyro.North) {
            if (tof.isNotLeft && !location
                                      .mapData[location.x + MAP_ORIGIN - 1]
                                              [location.y + MAP_ORIGIN]
                                      .isPassed) {
                DFS = true;
                servo.velocity = 0;
                servo.suspend = true;
                app.delay(WAIT);
                servo.suspend = false;
                servo.angle -= 90;
                app.delay(WAIT);
                servo.velocity = SPEED;
                app.delay(FORWARD);
                servo.suspend = true;
                app.delay(WAIT);
                servo.suspend = false;
            } else if (tof.isNotRight &&
                       !location
                            .mapData[location.x + MAP_ORIGIN + 1]
                                    [location.y + MAP_ORIGIN]
                            .isPassed) {
                DFS = true;
                servo.velocity = 0;
                servo.suspend = true;
                app.delay(WAIT);
                servo.suspend = false;
                servo.angle += 90;
                app.delay(WAIT);
                servo.velocity = SPEED;
                app.delay(FORWARD);
                servo.suspend = true;
                app.delay(WAIT);
                servo.suspend = false;
            } else {
                app.delay(10);
            }
        } else if (virtualWall[location.x + MAP_ORIGIN]
                              [location.y + MAP_ORIGIN - 1] &&
                   gyro.South) {
            if (tof.isNotRight && !location
                                       .mapData[location.x + MAP_ORIGIN - 1]
                                               [location.y + MAP_ORIGIN]
                                       .isPassed) {
                DFS = true;
                servo.velocity = 0;
                servo.suspend = true;
                app.delay(WAIT);
                servo.suspend = false;
                servo.angle += 90;
                app.delay(WAIT);
                servo.velocity = SPEED;
                app.delay(FORWARD);
                servo.suspend = true;
                app.delay(WAIT);
                servo.suspend = false;
            } else if (tof.isNotRight &&
                       !location
                            .mapData[location.x + MAP_ORIGIN + 1]
                                    [location.y + MAP_ORIGIN]
                            .isPassed) {
                DFS = true;
                servo.velocity = 0;
                servo.suspend = true;
                app.delay(WAIT);
                servo.suspend = false;
                servo.angle -= 90;
                app.delay(WAIT);
                servo.velocity = SPEED;
                app.delay(FORWARD);
                servo.suspend = true;
                app.delay(WAIT);
                servo.suspend = false;
            } else {
                app.delay(10);
            }
        } else if (virtualWall[location.x + MAP_ORIGIN + 1]
                              [location.y + MAP_ORIGIN] &&
                   gyro.East) {
            if (tof.isNotRight && !location
                                       .mapData[location.x + MAP_ORIGIN]
                                               [location.y + MAP_ORIGIN + 1]
                                       .isPassed) {
                DFS = true;
                servo.velocity = 0;
                servo.suspend = true;
                app.delay(WAIT);
                servo.suspend = false;
                servo.angle -= 90;
                app.delay(WAIT);
                servo.velocity = SPEED;
                app.delay(FORWARD);
                servo.suspend = true;
                app.delay(WAIT);
                servo.suspend = false;
            } else if (tof.isNotRight &&
                       !location
                            .mapData[location.x + MAP_ORIGIN]
                                    [location.y + MAP_ORIGIN - 1]
                            .isPassed) {
                DFS = true;
                servo.velocity = 0;
                servo.suspend = true;
                app.delay(WAIT);
                servo.suspend = false;
                servo.angle -= 90;
                app.delay(WAIT);
                servo.velocity = SPEED;
                app.delay(FORWARD);
                servo.suspend = true;
                app.delay(WAIT);
                servo.suspend = false;
            } else {
                app.delay(10);
            }
        } else if (virtualWall[location.x + MAP_ORIGIN - 1]
                              [location.y + MAP_ORIGIN] &&
                   gyro.West) {
            if (tof.isNotRight && !location
                                       .mapData[location.x + MAP_ORIGIN]
                                               [location.y + MAP_ORIGIN + 1]
                                       .isPassed) {
                DFS = true;
                servo.velocity = 0;
                servo.suspend = true;
                app.delay(WAIT);
                servo.suspend = false;
                servo.angle += 90;
                app.delay(WAIT);
                servo.velocity = SPEED;
                app.delay(FORWARD);
                servo.suspend = true;
                app.delay(WAIT);
                servo.suspend = false;

            } else if (tof.isNotRight &&
                       !location
                            .mapData[location.x + MAP_ORIGIN]
                                    [location.y + MAP_ORIGIN - 1]
                            .isPassed) {
                DFS = true;
                servo.velocity = 0;
                servo.suspend = true;
                app.delay(WAIT);
                servo.suspend = false;
                servo.angle -= 90;
                app.delay(WAIT);
                servo.velocity = SPEED;
                app.delay(FORWARD);
                servo.suspend = true;
                app.delay(WAIT);
                servo.suspend = false;
            } else {
                app.delay(10);
            }
        }
        if (!DFS) {
            if (tof.isNotRight && !gyro.slope) {  // 右壁が消えた時の処理
                servo.velocity = 0;
                servo.suspend = true;
                app.delay(WAIT);
                servo.suspend = false;
                servo.angle += 90;
                servo.velocity = 0;
                servo.suspend = true;
                app.delay(WAIT);
                servo.suspend = false;
                servo.velocity = SPEED;
                app.delay(FORWARD);  // 次のタイルまで前進
            }
        }
    }
}

void leftWallApp(App) {
    while (1) {
        servo.velocity = SPEED;
        servo.suspend = false;
        isRightWallApp = false;
        app.delay(period);

        if (tof.isNotLeft && !gyro.slope) {  // 左壁が消えた時の処理
            servo.velocity = 0;
            servo.suspend = true;
            app.delay(WAIT);
            servo.suspend = false;
            servo.angle -= 90;
            servo.velocity = 0;
            servo.suspend = true;
            app.delay(WAIT);
            servo.suspend = false;
            servo.velocity = SPEED;
            app.delay(FORWARD);  // 次のタイルまで前進
        }

        if (tof.val[0] < 140 && !gyro.slope) {  // 前に壁が来た時の処理
            servo.velocity = 0;
            servo.suspend = true;
            app.delay(WAIT);
            servo.suspend = false;
            servo.angle += 90;
            app.delay(WAIT);
        }
    }
}

void adjustmentApp(App) {
    while (1) {
        static bool isHit = false;
        app.delay(period);
        if (isRightWallApp) {
            if (tof.val[3] < 120) {
                servo.isCorrectingAngle = -3;  // 接近しすぎたら離れる
            } else if (tof.val[3] < 230 && tof.val[2] < 265) {
                if (radius + tof.val[3] + 30 <
                    0.8660254038 *
                        (radius + tof.val[2])) {   // √3/2(tofが30°間隔)
                    servo.isCorrectingAngle += 1;  // 一度ずつ補正
                }
                if (radius + tof.val[3] - 30 >
                    0.8660254038 * (radius + tof.val[2])) {
                    servo.isCorrectingAngle -= 1;
                }
            }
        } else {
            if (tof.val[9] < 120) {
                servo.isCorrectingAngle = 3;
            } else if (tof.val[9] < 230 && tof.val[10] < 265) {
                if (radius + tof.val[9] + 25 <
                    0.8660254038 *
                        (radius + tof.val[8])) {  // √3/2　//NOTE
                                                  // 新機体は1/√2(0.7071067812)
                    servo.isCorrectingAngle += 1;  // 一度ずつ補正
                }
                if (radius + tof.val[9] - 25 >
                    0.8660254038 * (radius + tof.val[8])) {
                    servo.isCorrectingAngle -= 1;
                }
            }
        }

        if (loadcell.status == RIGHT) {
            app.stop(servoApp);
            servo.driveAngularVelocity(-30, 45);
            app.delay(WAIT);
            servo.driveAngularVelocity(-30, -45);
            app.delay(WAIT);
            isHit = false;
        }
        if (loadcell.status == LEFT) {
            app.stop(servoApp);
            servo.driveAngularVelocity(-30, -45);
            app.delay(WAIT);
            servo.driveAngularVelocity(-30, 45);
            app.delay(WAIT);
            isHit = false;
        }
        if (!isHit) {
            servo.velocity = SPEED;
            app.start(servoApp);
            isHit = true;
        }
    }
}

void AstarApp(App) {  // NOTE 動いた
    app.delay(WAIT);
    int Ndistance = MAX_DISTANCE;
    int Edistance = MAX_DISTANCE;
    int Sdistance = MAX_DISTANCE;
    int Wdistance = MAX_DISTANCE;  // 値の初期化(最大値に設定)
    bool status = true;
    app.delay(WAIT);
    const int initialWall[4] = {(tof.isNorthWall), (tof.isEastWall),
                                (tof.isSouthWall),
                                (tof.isWestWall)};  //(0,0)の壁の状態を記憶
    while (1) {
        app.delay(100);
        if (millis() > FEEDBACK && servo.velocity == 50) {
            if (status) {
                servo.velocity = 0;
                servo.suspend = true;
                app.stop(rightWallApp);
                app.stop(leftWallApp);
                app.stop(DepthFirstSearchApp);
                // app.stop(adjustmentApp);
                app.delay(WAIT);
                servo.suspend = false;
                status = false;
            }
            app.delay(period);
        MEASURE_DISTANCE:  // 最短経路の算出
            if ((-1 <= location.x && location.x <= 1) &&
                (-1 <= location.y && location.y <= 1) &&
                initialWall[NORTH] == tof.isNorthWall &&
                initialWall[EAST] == tof.isEastWall &&
                initialWall[SOUTH] == tof.isSouthWall &&
                initialWall[WEST] ==
                    tof.isWestWall) {  //(0,0)かつスタート時の壁情報と一致+-1まで許容
                servo.velocity = 0;
                servo.suspend = true;
                app.stop(servoApp);
                app.delay(20000);
            }

            if (!tof.isNorthWall) {
                Ndistance = location.x * location.x +
                            (location.y + 1) * (location.y + 1);
            } else {
                Ndistance = MAX_DISTANCE;
            }
            if (!tof.isEastWall) {
                Edistance = (location.x + 1) * (location.x + 1) +
                            location.y * location.y;
            } else {
                Edistance = MAX_DISTANCE;
            }
            if (!tof.isSouthWall) {
                Sdistance = location.x * location.x +
                            (location.y - 1) * (location.y - 1);
            } else {
                Sdistance = MAX_DISTANCE;
            }
            if (!tof.isWestWall) {
                Wdistance = (location.x - 1) * (location.x - 1) +
                            location.y * location.y;
            } else {
                Wdistance = MAX_DISTANCE;
            }
        MOVE_COORDINATE:  // FIXME
            // 1マスぴったり進む方法が確立されていない&坂道来た時どうする？
            if (Ndistance < Edistance && Ndistance < Sdistance &&
                Ndistance < Wdistance) {
                servo.angle = 0 + servo.isCorrectingAngle;
                servo.velocity = 50;
                app.delay(FORWARD);
                servo.velocity = 0;
                servo.suspend = true;
                app.delay(WAIT);
                servo.suspend = false;
                tof.isSouthWall = true;  // 後方に仮想壁
                goto MEASURE_DISTANCE;

            } else if (Sdistance < Edistance && Sdistance < Wdistance) {
                servo.angle = 180 + servo.isCorrectingAngle;
                servo.velocity = 50;
                app.delay(FORWARD);
                servo.velocity = 0;
                servo.suspend = true;
                app.delay(WAIT);
                servo.suspend = false;
                tof.isNorthWall = true;
                goto MEASURE_DISTANCE;

            } else if (Edistance < Wdistance) {
                servo.angle = 90 + servo.isCorrectingAngle;
                servo.velocity = 50;
                app.delay(FORWARD);
                servo.velocity = 0;
                servo.suspend = true;
                app.delay(WAIT);
                servo.suspend = false;
                tof.isWestWall = true;
                goto MEASURE_DISTANCE;

            } else {
                servo.angle = 270 + servo.isCorrectingAngle;
                servo.velocity = 50;
                app.delay(FORWARD);
                servo.velocity = 0;
                servo.suspend = true;
                app.delay(WAIT);
                servo.suspend = false;
                tof.isEastWall = true;
                goto MEASURE_DISTANCE;
            }
        } else {
            app.delay(period * 5);
        }
    }
}

void monitorApp(App) {
    while (1) {
        // uart3.print(radius + tof.val[9]);
        // uart3.print(" ");
        // uart3.println(0.8660254038 * (radius + tof.val[8]));

        uart3.print(tof.isNorthWall);
        uart3.print("\t");
        uart3.print(tof.isEastWall);
        uart3.print("\t");
        uart3.print(tof.isSouthWall);
        uart3.print("\t");
        uart3.println(tof.isWestWall);
        app.delay(period);
    }
}

void DepthFirstSearchApp(App) {  // NOTE 二方向以上進める座標を記録する変数
                                 // "JCT"
    static bool JCT[MAP_ORIGIN * 2][MAP_ORIGIN * 2] = {false};
    app.delay(WAIT);
    while (1) {
        virtualWall[location.x + MAP_ORIGIN][location.y + MAP_ORIGIN] =
            true;  // 仮想壁
        app.delay(period);

        if (tof.val[0] > 450 && (tof.val[3] > 230 || tof.val[9] > 230)) {
            JCT[location.x + MAP_ORIGIN][location.y + MAP_ORIGIN] = true;
        }
        if (!isRightWallApp &&
            JCT[location.x + MAP_ORIGIN][location.y + MAP_ORIGIN] &&
            (tof.val[3] > 230 || tof.val[9] > 230)) {
            servo.suspend = true;
            app.delay(WAIT);
            servo.suspend = false;
            app.stop(leftWallApp);
            app.start(rightWallApp);
        }

        if (!tof.isNotFront) {
            app.stop(rightWallApp);
            servo.suspend = true;
            app.delay(WAIT);
            servo.suspend = false;
            servo.angle += 180;
            app.delay(WAIT * 3);
            app.start(leftWallApp);
        }  // 前方+左右に壁があったら反転して左壁追従
    }
}

#endif