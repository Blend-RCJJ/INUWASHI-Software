#ifndef _SEARCH_H_
#define _SEARCH_H_

#include "../device/device.h"
#include "../kit/RTOS-Kit.h"
#include "./algorithm.h"
#include "./rtosIO.h"
#include "./rtosLocation.h"
#include "./rtosVictim.h"

extern RTOS_Kit app;

#define SPEED 50
#define WAIT 500
#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3

const int radius                                 = 20;
bool virtualWall[MAP_ORIGIN * 2][MAP_ORIGIN * 2] = {false};
bool isRightWallApp                              = false;
bool oldstatus                                   = false;
static int oldmillis                             = 0;
int checkPointX                                  = MAP_ORIGIN;
int checkPointY                                  = MAP_ORIGIN;
static double oldCoordinateX                     = 0;
static double oldCoordinateY                     = 0;
static bool locationIsChanged                    = false;

void rightWallApp(App) {
    static bool DFS = false;
    app.delay(WAIT);
    while (1) {
        servo.velocity = SPEED;
        servo.suspend  = false;
        isRightWallApp = true;
        oldCoordinateX = location.coordinateX;
        oldCoordinateY = location.coordinateY;
        DFS            = false;
        app.delay(period);

        if (tof.val[0] < 130 && !gyro.slope) {  // 前に壁が来た時の処理
            oldmillis      = millis();
            checkPointX    = location.x;
            checkPointY    = location.y;
            DFS            = true;
            servo.velocity = 0;
            servo.suspend  = true;
            app.delay(WAIT);
            servo.suspend = false;
            servo.angle -= 90;
            app.delay(WAIT);
        }
        if (virtualWall[location.x + MAP_ORIGIN][location.y + MAP_ORIGIN + 1] &&
            gyro.North) {
            if (tof.isNotRight && !location
                                       .mapData[location.x + MAP_ORIGIN + 1]
                                               [location.y + MAP_ORIGIN]
                                       .isPassed) {
                oldmillis      = millis();
                checkPointX    = location.x;
                checkPointY    = location.y;
                DFS            = true;
                servo.velocity = 0;
                servo.suspend  = true;
                app.delay(WAIT);
                servo.suspend = false;
                servo.angle += 90;
                app.delay(WAIT);
                servo.velocity = SPEED;
                while (abs(location.coordinateX - oldCoordinateX) < 300 &&
                       abs(location.coordinateY - oldCoordinateY) < 300) {
                    if (tof.val[0] < 140) {
                        break;
                    }
                    servo.velocity = SPEED;
                    app.delay(period);
                }
                servo.suspend = true;
                app.delay(WAIT);
                servo.suspend = false;
            } else if (tof.isNotLeft &&
                       !location
                            .mapData[location.x + MAP_ORIGIN - 1]
                                    [location.y + MAP_ORIGIN]
                            .isPassed) {
                oldmillis      = millis();
                checkPointX    = location.x;
                checkPointY    = location.y;
                DFS            = true;
                servo.velocity = 0;
                servo.suspend  = true;
                app.delay(WAIT);
                servo.suspend = false;
                servo.angle -= 90;
                app.delay(WAIT);
                servo.velocity = SPEED;
                while (abs(location.coordinateX - oldCoordinateX) < 300 &&
                       abs(location.coordinateY - oldCoordinateY) < 300) {
                    if (tof.val[0] < 140) {
                        break;
                    }
                    servo.velocity = SPEED;
                    app.delay(period);
                }
                servo.suspend = true;
                app.delay(WAIT);
                servo.suspend = false;
            } else {
                app.delay(period);
            }
        } else if (virtualWall[location.x + MAP_ORIGIN]
                              [location.y + MAP_ORIGIN - 1] &&
                   gyro.South) {
            if (tof.isNotRight && !location
                                       .mapData[location.x + MAP_ORIGIN - 1]
                                               [location.y + MAP_ORIGIN]
                                       .isPassed) {
                oldmillis      = millis();
                checkPointX    = location.x;
                checkPointY    = location.y;
                DFS            = true;
                servo.velocity = 0;
                servo.suspend  = true;
                app.delay(WAIT);
                servo.suspend = false;
                servo.angle += 90;
                app.delay(WAIT);
                servo.velocity = SPEED;
                while (abs(location.coordinateX - oldCoordinateX) < 300 &&
                       abs(location.coordinateY - oldCoordinateY) < 300) {
                    if (tof.val[0] < 140) {
                        break;
                    }
                    servo.velocity = SPEED;
                    app.delay(period);
                }
                servo.suspend = true;
                app.delay(WAIT);
                servo.suspend = false;
            } else if (tof.isNotLeft &&
                       !location
                            .mapData[location.x + MAP_ORIGIN + 1]
                                    [location.y + MAP_ORIGIN]
                            .isPassed) {
                oldmillis      = millis();
                checkPointX    = location.x;
                checkPointY    = location.y;
                DFS            = true;
                servo.velocity = 0;
                servo.suspend  = true;
                app.delay(WAIT);
                servo.suspend = false;
                servo.angle -= 90;
                app.delay(WAIT);
                servo.velocity = SPEED;
                while (abs(location.coordinateX - oldCoordinateX) < 300 &&
                       abs(location.coordinateY - oldCoordinateY) < 300) {
                    if (tof.val[0] < 140) {
                        break;
                    }
                    servo.velocity = SPEED;
                    app.delay(period);
                }
                servo.suspend = true;
                app.delay(WAIT);
                servo.suspend = false;
            } else {
                app.delay(period);
            }
        } else if (virtualWall[location.x + MAP_ORIGIN + 1]
                              [location.y + MAP_ORIGIN] &&
                   gyro.East) {
            if (tof.isNotRight && !location
                                       .mapData[location.x + MAP_ORIGIN]
                                               [location.y + MAP_ORIGIN - 1]
                                       .isPassed) {
                oldmillis      = millis();
                checkPointX    = location.x;
                checkPointY    = location.y;
                DFS            = true;
                servo.velocity = 0;
                servo.suspend  = true;
                app.delay(WAIT);
                servo.suspend = false;
                servo.angle += 90;
                app.delay(WAIT);
                servo.velocity = SPEED;
                while (abs(location.coordinateX - oldCoordinateX) < 300 &&
                       abs(location.coordinateY - oldCoordinateY) < 300) {
                    if (tof.val[0] < 140) {
                        break;
                    }
                    servo.velocity = SPEED;
                    app.delay(period);
                }
                servo.suspend = true;
                app.delay(WAIT);
                servo.suspend = false;
            } else if (tof.isNotLeft &&
                       !location
                            .mapData[location.x + MAP_ORIGIN]
                                    [location.y + MAP_ORIGIN + 1]
                            .isPassed) {
                oldmillis      = millis();
                checkPointX    = location.x;
                checkPointY    = location.y;
                DFS            = true;
                servo.velocity = 0;
                servo.suspend  = true;
                app.delay(WAIT);
                servo.suspend = false;
                servo.angle -= 90;
                app.delay(WAIT);
                servo.velocity = SPEED;
                while (abs(location.coordinateX - oldCoordinateX) < 300 &&
                       abs(location.coordinateY - oldCoordinateY) < 300) {
                    if (tof.val[0] < 140) {
                        break;
                    }
                    servo.velocity = SPEED;
                    app.delay(period);
                }
                servo.suspend = true;
                app.delay(WAIT);
                servo.suspend = false;
            } else {
                app.delay(period);
            }
        } else if (virtualWall[location.x + MAP_ORIGIN - 1]
                              [location.y + MAP_ORIGIN] &&
                   gyro.West) {
            if (tof.isNotRight && !location
                                       .mapData[location.x + MAP_ORIGIN]
                                               [location.y + MAP_ORIGIN + 1]
                                       .isPassed) {
                oldmillis      = millis();
                checkPointX    = location.x;
                checkPointY    = location.y;
                DFS            = true;
                servo.velocity = 0;
                servo.suspend  = true;
                app.delay(WAIT);
                servo.suspend = false;
                servo.angle += 90;
                app.delay(WAIT);
                servo.velocity = SPEED;
                while (abs(location.coordinateX - oldCoordinateX) < 300 &&
                       abs(location.coordinateY - oldCoordinateY) < 300) {
                    if (tof.val[0] < 140) {
                        break;
                    }
                    servo.velocity = SPEED;
                    app.delay(period);
                }
                servo.suspend = true;
                app.delay(WAIT);
                servo.suspend = false;

            } else if (tof.isNotLeft &&
                       !location
                            .mapData[location.x + MAP_ORIGIN]
                                    [location.y + MAP_ORIGIN - 1]
                            .isPassed) {
                oldmillis      = millis();
                checkPointX    = location.x;
                checkPointY    = location.y;
                DFS            = true;
                servo.velocity = 0;
                servo.suspend  = true;
                app.delay(WAIT);
                servo.suspend = false;
                servo.angle -= 90;
                app.delay(WAIT);
                servo.velocity = SPEED;
                while (abs(location.coordinateX - oldCoordinateX) < 300 &&
                       abs(location.coordinateY - oldCoordinateY) < 300) {
                    if (tof.val[0] < 140) {
                        break;
                    }
                    servo.velocity = SPEED;
                    app.delay(period);
                }
                servo.suspend = true;
                app.delay(WAIT);
                servo.suspend = false;
            } else {
                app.delay(period);
            }
        } else if (!virtualWall[location.x + MAP_ORIGIN]
                               [location.y + MAP_ORIGIN + 1] &&
                   gyro.North &&
                   (virtualWall[location.x + MAP_ORIGIN - 1]
                               [location.y + MAP_ORIGIN] ||
                    tof.isWestWall) &&
                   (virtualWall[location.x + MAP_ORIGIN + 1]
                               [location.y + MAP_ORIGIN] ||
                    tof.isEastWall) &&
                   (virtualWall[location.x + MAP_ORIGIN]
                               [location.y + MAP_ORIGIN - 1] ||
                    tof.isSouthWall)) {
            if (!tof.isNorthWall) {
                oldmillis      = millis();
                checkPointX    = location.x;
                checkPointY    = location.y;
                DFS            = true;
                servo.velocity = SPEED;
                  while (abs(location.coordinateX - oldCoordinateX) < 300 &&
                       abs(location.coordinateY - oldCoordinateY) < 300) {
                    if(tof.val[0] < 140){
                        break;
                    }
                    servo.velocity = SPEED;
                    app.delay(period);
                }
            }
        } else if (!virtualWall[location.x + MAP_ORIGIN]
                               [location.y + MAP_ORIGIN - 1] &&
                   gyro.South &&
                   (virtualWall[location.x + MAP_ORIGIN + 1]
                               [location.y + MAP_ORIGIN] ||
                    tof.isEastWall) &&
                   (virtualWall[location.x + MAP_ORIGIN - 1]
                               [location.y + MAP_ORIGIN] ||
                    tof.isWestWall) &&
                   (virtualWall[location.x + MAP_ORIGIN]
                               [location.y + MAP_ORIGIN + 1] ||
                    tof.isNorthWall)) {
            if (!tof.isSouthWall) {
                oldmillis      = millis();
                checkPointX    = location.x;
                checkPointY    = location.y;
                DFS            = true;
                servo.velocity = SPEED;
                 while (abs(location.coordinateX - oldCoordinateX) < 300 &&
                       abs(location.coordinateY - oldCoordinateY) < 300) {
                    if(tof.val[0] < 140){
                        break;
                    }
                    servo.velocity = SPEED;
                    app.delay(period);
                }
            }
        } else if (!virtualWall[location.x + MAP_ORIGIN + 1]
                               [location.y + MAP_ORIGIN] &&
                   gyro.East &&
                   (virtualWall[location.x + MAP_ORIGIN]
                               [location.y + MAP_ORIGIN - 1] ||
                    tof.isSouthWall) &&
                   (virtualWall[location.x + MAP_ORIGIN]
                               [location.y + MAP_ORIGIN + 1] ||
                    tof.isNorthWall) &&
                   (virtualWall[location.x + MAP_ORIGIN - 1]
                               [location.y + MAP_ORIGIN] ||
                    tof.isWestWall)) {
            if (!tof.isEastWall) {
                oldmillis      = millis();
                checkPointX    = location.x;
                checkPointY    = location.y;
                DFS            = true;
                servo.velocity = SPEED;
                  while (abs(location.coordinateX - oldCoordinateX) < 300 &&
                       abs(location.coordinateY - oldCoordinateY) < 300) {
                    if(tof.val[0] < 140){
                        break;
                    }
                    servo.velocity = SPEED;
                    app.delay(period);
                }
            }
        } else if (!virtualWall[location.x + MAP_ORIGIN - 1]
                               [location.y + MAP_ORIGIN] &&
                   gyro.West &&
                   (virtualWall[location.x + MAP_ORIGIN]
                               [location.y + MAP_ORIGIN + 1] ||
                    tof.isNorthWall) &&
                   (virtualWall[location.x + MAP_ORIGIN]
                               [location.y + MAP_ORIGIN - 1] ||
                    tof.isSouthWall) &&
                   (virtualWall[location.x + MAP_ORIGIN + 1]
                               [location.y + MAP_ORIGIN] ||
                    tof.isEastWall)) {
            if (!tof.isWestWall) {
                oldmillis      = millis();
                checkPointX    = location.x;
                checkPointY    = location.y;
                DFS            = true;
                servo.velocity = SPEED;
                  while (abs(location.coordinateX - oldCoordinateX) < 300 &&
                       abs(location.coordinateY - oldCoordinateY) < 300) {
                    if(tof.val[0] < 140){
                        break;
                    }
                    servo.velocity = SPEED;
                    app.delay(period);
                }
            }
        } else {
            app.delay(period);
        }

        if (!DFS) {
            if (tof.isNotRight && !gyro.slope) {  // 右壁が消えた時の処理
                servo.velocity = 0;
                servo.suspend  = true;
                app.delay(WAIT);
                servo.suspend = false;
                servo.angle += 90;
                servo.velocity = 0;
                servo.suspend  = true;
                app.delay(WAIT);
                servo.suspend = false;
                while (abs(location.coordinateX - oldCoordinateX) < 300 &&
                       abs(location.coordinateY - oldCoordinateY) < 300) {
                    if (tof.val[0] < 140) {
                        break;
                    }
                    servo.velocity = SPEED;
                    app.delay(period);
                }
            }
        }
    }
}

void leftWallApp(App) {
    while (1) {
        servo.velocity = SPEED;
        servo.suspend  = false;
        isRightWallApp = false;
        app.delay(period);

        if (tof.isNotLeft && !gyro.slope) {  // 左壁が消えた時の処理
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
            while (abs(location.coordinateX - oldCoordinateX) < 300 &&
                   abs(location.coordinateY - oldCoordinateY) < 300) {
                if (tof.val[0] < 140) {
                    break;
                }
                servo.velocity = SPEED;
                app.delay(period);
            }  // 次のタイルまで前進
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

void adjustmentApp(App) {
    while (1) {
        static bool isHit = false;
        if (isRightWallApp) {
            if (tof.val[3] < 110) {
                servo.isCorrectingAngle -= 1;  // 接近しすぎたら離れる
                app.delay(period * 10);
            } else if (tof.val[3] < 230 && tof.val[2] < 265) {
                if (radius + tof.val[3] + 30 <
                    0.8660254038 *
                        (radius + tof.val[2])) {   // √3/2(tofが30°間隔)
                    servo.isCorrectingAngle += 1;  // 一度ずつ補正
                } else {
                    servo.isCorrectingAngle = 0;
                }
                if (radius + tof.val[3] - 30 >
                    0.8660254038 * (radius + tof.val[2])) {
                    servo.isCorrectingAngle -= 1;
                } else {
                    servo.isCorrectingAngle = 0;
                }
            }
        } else {
            if (tof.val[9] < 110) {
                servo.isCorrectingAngle += 1;  // 接近しすぎたら離れる
                app.delay(period * 10);
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
            app.delay(300);
            servo.driveAngularVelocity(-30, -45);
            app.delay(300);
            isHit = false;
        }
        if (loadcell.status == LEFT) {
            app.stop(servoApp);
            servo.driveAngularVelocity(-30, -45);
            app.delay(300);
            servo.driveAngularVelocity(-30, 45);
            app.delay(300);
            isHit = false;
        }
        if (!isHit) {
            servo.velocity = SPEED;
            app.start(servoApp);
            isHit = true;
        }
        app.delay(period);
    }
}

void floorApp(App) {
    static bool oldstate = false;
    while (1) {
        floorSensor.colorJudgment();
        app.delay(period);
        if (floorSensor.isBlue && !oldstate) {
            app.stop(rightWallApp);
            servo.suspend = true;
            app.delay(5500);
            servo.suspend = false;
            app.start(rightWallApp);
            oldstate = true;
        } else if (oldstate) {
            app.delay(5000);
            oldstate = false;
        }

        if (floorSensor.isBlack) {
            servo.suspend = true;
            app.stop(rightWallApp);
            servo.velocity = -SPEED;
            app.delay(WAIT);
            servo.suspend = false;
            app.delay(WAIT);
            servo.angle -= 90;
            servo.velocity = SPEED;
            app.delay(2804);
            app.start(rightWallApp);
        }
    }
}

#endif