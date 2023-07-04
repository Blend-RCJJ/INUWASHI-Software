#ifndef _SEARCH_H_
#define _SEARCH_H_

#include "../device/device.h"
#include "../kit/RTOS-Kit.h"
#include "./algorithm.h"
#include "./rtosIO.h"
#include "./rtosLocation.h"
#include "./rtosVictim.h"

extern RTOS_Kit app;

#define SPEED 100
#define WAIT 500
#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3

const double radius                              = 26.5;
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
        uart3.println("右壁探索中...");
        servo.velocity = SPEED;
        servo.suspend  = false;
        isRightWallApp = true;
        oldCoordinateX = location.coordinateX;
        oldCoordinateY = location.coordinateY;
        DFS            = false;
        app.delay(period);

        if (tof.val[0] < 130) {  // 前に壁が来た時の処理
            oldmillis      = millis();
            checkPointX    = location.x;
            checkPointY    = location.y;
            DFS            = true;
            servo.velocity = 0;
            servo.suspend  = true;
            app.delay(WAIT);
            servo.suspend = false;
            servo.angle -= 90;
            servo.isCorrectingAngle = 0;
            app.delay(WAIT * 2);
            servo.velocity = SPEED;
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
                servo.isCorrectingAngle = 0;
                app.delay(WAIT * 2);
                servo.velocity = SPEED;
                while (abs(location.coordinateX - oldCoordinateX) < 300 &&
                       abs(location.coordinateY - oldCoordinateY) < 300) {
                    if (tof.val[0] < 130) {
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
                servo.isCorrectingAngle = 0;
                app.delay(WAIT * 2);
                servo.velocity = SPEED;
                while (abs(location.coordinateX - oldCoordinateX) < 300 &&
                       abs(location.coordinateY - oldCoordinateY) < 300) {
                    if (tof.val[0] < 130) {
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
            app.delay(period);
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
                servo.isCorrectingAngle = 0;
                app.delay(WAIT * 2);
                servo.velocity = SPEED;
                while (abs(location.coordinateX - oldCoordinateX) < 300 &&
                       abs(location.coordinateY - oldCoordinateY) < 300) {
                    if (tof.val[0] < 130) {
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
                servo.isCorrectingAngle = 0;
                app.delay(WAIT * 2);
                servo.velocity = SPEED;
                while (abs(location.coordinateX - oldCoordinateX) < 300 &&
                       abs(location.coordinateY - oldCoordinateY) < 300) {
                    if (tof.val[0] < 130) {
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
            app.delay(period);
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
                servo.isCorrectingAngle = 0;
                app.delay(WAIT * 2);
                servo.velocity = SPEED;
                while (abs(location.coordinateX - oldCoordinateX) < 300 &&
                       abs(location.coordinateY - oldCoordinateY) < 300) {
                    if (tof.val[0] < 130) {
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
                servo.isCorrectingAngle = 0;
                app.delay(WAIT * 2);
                servo.velocity = SPEED;
                while (abs(location.coordinateX - oldCoordinateX) < 300 &&
                       abs(location.coordinateY - oldCoordinateY) < 300) {
                    if (tof.val[0] < 130) {
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
            app.delay(period);
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
                servo.isCorrectingAngle = 0;
                app.delay(WAIT * 2);
                servo.velocity = SPEED;
                while (abs(location.coordinateX - oldCoordinateX) < 300 &&
                       abs(location.coordinateY - oldCoordinateY) < 300) {
                    if (tof.val[0] < 130) {
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
                servo.isCorrectingAngle = 0;
                app.delay(WAIT * 2);
                servo.velocity = SPEED;
                while (abs(location.coordinateX - oldCoordinateX) < 300 &&
                       abs(location.coordinateY - oldCoordinateY) < 300) {
                    if (tof.val[0] < 130) {
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
            app.delay(period);
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
                while (abs(location.coordinateX - oldCoordinateX) < 200 &&
                       abs(location.coordinateY - oldCoordinateY) < 200) {
                    if (tof.val[0] < 130) {
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
                while (abs(location.coordinateX - oldCoordinateX) < 200 &&
                       abs(location.coordinateY - oldCoordinateY) < 200) {
                    if (tof.val[0] < 130) {
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
                while (abs(location.coordinateX - oldCoordinateX) < 200 &&
                       abs(location.coordinateY - oldCoordinateY) < 200) {
                    if (tof.val[0] < 130) {
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
                while (abs(location.coordinateX - oldCoordinateX) < 200 &&
                       abs(location.coordinateY - oldCoordinateY) < 200) {
                    if (tof.val[0] < 130) {
                        break;
                    }
                    servo.velocity = SPEED;
                    app.delay(period);
                }
            }
        }
        if (!DFS) {
            if (tof.isNotRight) {  // 右壁が消えた時の処理
                servo.velocity = 0;
                servo.suspend  = true;
                app.delay(WAIT);
                servo.suspend = false;
                servo.angle += 90;
                servo.isCorrectingAngle = 0;
                servo.velocity          = 0;
                servo.suspend           = true;
                app.delay(WAIT * 2);
                servo.suspend = false;
                while (abs(location.coordinateX - oldCoordinateX) < 250 &&
                       abs(location.coordinateY - oldCoordinateY) < 250) {
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
        uart3.println("左壁探索中...");
        app.stop(rightWallApp);
        servo.velocity = SPEED;
        servo.suspend  = false;
        isRightWallApp = false;
        app.delay(period);

        if (tof.isNotLeft) {  // 左壁が消えた時の処理
            servo.velocity = 0;
            servo.suspend  = true;
            app.delay(WAIT);
            servo.suspend = false;
            servo.angle -= 90;
            servo.isCorrectingAngle = 0;
            servo.velocity          = 0;
            servo.suspend           = true;
            app.delay(WAIT * 2);
            servo.suspend  = false;
            servo.velocity = SPEED;
            while (abs(location.coordinateX - oldCoordinateX) < 250 &&
                   abs(location.coordinateY - oldCoordinateY) < 250) {
                if (tof.val[0] < 160) {
                    break;
                }
                servo.velocity = SPEED;
                app.delay(period);
            }  // 次のタイルまで前進
        }

        if (tof.val[0] < 130) {  // 前に壁が来た時の処理
            servo.velocity = 0;
            servo.suspend  = true;
            app.delay(WAIT);
            servo.suspend = false;
            servo.angle += 90;
            servo.isCorrectingAngle = 0;
            app.delay(WAIT * 2);
            servo.velocity = SPEED;
        }
    }
}

void adjustmentApp(App) {
    while (1) {
        static bool isHit = false;
        if (tof.val[4] + tof.val[12] < 300) {
            if (tof.val[4] > tof.val[12]) {
                servo.isCorrectingAngle = 7;
            }
            if (tof.val[12] > tof.val[4]) {
                servo.isCorrectingAngle = -7;
            }
            app.delay(50);
        } else {
            if (tof.val[12] < 120) {
                servo.isCorrectingAngle = 7;
            }
            if (tof.val[4] < 120) {
                servo.isCorrectingAngle = -7;
            }
        }

        if (tof.val[4] > 300 && tof.val[12] < 300) {
            if (tof.val[12] > 120) {
                servo.isCorrectingAngle = -7;
            }
        }
        if (tof.val[12] > 300 && tof.val[4] < 300) {
            if (tof.val[4] > 120) {
                servo.isCorrectingAngle = 7;
            }
        }

        if (loadcell.status == RIGHT) {
            app.stop(servoApp);
            servo.driveAngularVelocity(-30, -45);
            app.delay(500);
            servo.driveAngularVelocity(-30, 45);
            app.delay(500);
            isHit = false;
        }
        if (loadcell.status == LEFT) {
            app.stop(servoApp);
            servo.driveAngularVelocity(-30, 45);
            app.delay(500);
            servo.driveAngularVelocity(-30, -45);
            app.delay(500);
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
    static bool oldstate  = false;
    static int waitmillis = 0;
    while (1) {
        floorSensor.colorJudgment();
        app.delay(period);
        if (oldstate && millis() - 5000 < waitmillis) {
            app.delay(period);
        } else if (oldstate) {
            oldstate = false;
        } else if (floorSensor.isBlue && !oldstate) {
            app.stop(rightWallApp);
            oldCoordinateX = location.coordinateX;
            oldCoordinateY = location.coordinateY;
            while (abs(location.coordinateX - oldCoordinateX) < 150 &&
                   abs(location.coordinateY - oldCoordinateY) < 150) {
                if (tof.val[0] < 140) {
                    break;
                }
                servo.velocity = SPEED;
                app.delay(period);
            }
            servo.suspend = true;
            servo.rescueKit(3, RIGHT);
            app.delay(5500);
            servo.suspend = false;
            app.restart(rightWallApp);
            waitmillis = millis();
            oldstate   = true;
        }

        if (floorSensor.isBlack) {
            servo.suspend = true;
            app.stop(rightWallApp);
            app.delay(period);
            servo.suspend  = false;
            servo.velocity = -SPEED;
            app.delay(WAIT * 2);
            servo.angle -= 90;
            servo.isCorrectingAngle = 0;
            app.delay(WAIT);
            oldCoordinateX = location.coordinateX;
            oldCoordinateY = location.coordinateY;
            while (abs(location.coordinateX - oldCoordinateX) < 300 &&
                   abs(location.coordinateY - oldCoordinateY) < 300) {
                if (tof.val[0] < 140) {
                    break;
                }
                servo.velocity = SPEED;
                app.delay(period);
            }  // 次のタイルまで前進
            servo.suspend = true;
            app.delay(500);
            servo.suspend = false;
            app.restart(rightWallApp);
        }
    }
}

#endif