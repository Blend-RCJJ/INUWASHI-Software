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
#define RETURN_TIME 300000  // 帰還開始時間(ms)

bool virtualWall[MAP_ORIGIN * 2][MAP_ORIGIN * 2] = {false};
bool isRightWallApp                              = false;
bool oldstatus                                   = false;
static int oldmillis                             = 0;
int checkPointX                                  = MAP_ORIGIN;
int checkPointY                                  = MAP_ORIGIN;
static double oldCoordinateX                     = 0;
static double oldCoordinateY                     = 0;
static bool locationIsChanged                    = false;

void AstarApp(App);
void adjustmentApp(App);

void rightWallApp(App) {
    static bool DFS = false;
    int count       = 0;
    int val8        = 0;
    int val0        = 0;
    app.delay(WAIT);
    while (1) {
        // uart3.println("右壁探索中...");
        servo.suspend  = false;
        servo.velocity = SPEED;
        DFS           = false;
        app.delay(period);
        if (abs(gyro.slope >= 10)) {
            servo.suspend  = false;
            servo.velocity = SPEED;
        }
        while (count == 1) {
            app.delay(300);
            count = 0;
        }

        while (count == 0) {
            val8  = tof.val[8];
            val0  = tof.val[0];
            count = 2;
            app.delay(10);
        }

        if (tof.val[4] > 200) {
            count = 2;
            if (val8 > 600) {
                if ((val0 - 100) > tof.val[0]) {
                    servo.velocity = 0;
                    servo.stop();
                    app.delay(500);
                    servo.angle += 90;
                    servo.velocity = 0;
                    servo.stop();
                    app.delay(500);
                    count          = 0;
                    servo.velocity = SPEED;
                    app.delay(1500);
                }
            } else if ((val8 + 100) < tof.val[8]) {
                servo.velocity = 0;
                servo.stop();
                app.delay(500);
                servo.angle += 90;
                servo.velocity = 0;
                servo.stop();
                app.delay(500);
                count          = 0;
                servo.velocity = SPEED;
                app.delay(1500);
            }

        } else {
            count = 0;
            app.delay(10);
        }
        if (tof.val[0] < 120) {
            servo.velocity = 0;
            servo.stop();
            app.delay(500);
            servo.angle -= 90;
            count = 1;
            app.delay(900);
        }
        if (virtualWall[location.x + MAP_ORIGIN][location.y + MAP_ORIGIN
        + 1]
        &&
            gyro.North) {
            if (tof.isNotRight && !location
                                       .mapData[location.x + MAP_ORIGIN +
                                       1]
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
                while (abs(location.coordinateX - oldCoordinateX) < 280
                &&
                       abs(location.coordinateY - oldCoordinateY) < 280)
                       {
                    if (tof.val[0] < 125) {
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
                while (abs(location.coordinateX - oldCoordinateX) < 280
                &&
                       abs(location.coordinateY - oldCoordinateY) < 280)
                       {
                    if (tof.val[0] < 125) {
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
                                       .mapData[location.x + MAP_ORIGIN -
                                       1]
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
                while (abs(location.coordinateX - oldCoordinateX) < 280
                &&
                       abs(location.coordinateY - oldCoordinateY) < 280)
                       {
                    if (tof.val[0] < 125) {
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
                while (abs(location.coordinateX - oldCoordinateX) < 280
                &&
                       abs(location.coordinateY - oldCoordinateY) < 280)
                       {
                    if (tof.val[0] < 125) {
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
                                               [location.y + MAP_ORIGIN -
                                               1]
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
                while (abs(location.coordinateX - oldCoordinateX) < 280
                &&
                       abs(location.coordinateY - oldCoordinateY) < 280)
                       {
                    if (tof.val[0] < 125) {
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
                while (abs(location.coordinateX - oldCoordinateX) < 280
                &&
                       abs(location.coordinateY - oldCoordinateY) < 280)
                       {
                    if (tof.val[0] < 125) {
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
                                               [location.y + MAP_ORIGIN +
                                               1]
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
                while (abs(location.coordinateX - oldCoordinateX) < 280
                &&
                       abs(location.coordinateY - oldCoordinateY) < 280)
                       {
                    if (tof.val[0] < 125) {
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
                while (abs(location.coordinateX - oldCoordinateX) < 280
                &&
                       abs(location.coordinateY - oldCoordinateY) < 280)
                       {
                    if (tof.val[0] < 125) {
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
                while (abs(location.coordinateX - oldCoordinateX) < 200
                &&
                       abs(location.coordinateY - oldCoordinateY) < 200)
                       {
                    if (tof.val[0] < 150) {
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
                while (abs(location.coordinateX - oldCoordinateX) < 200
                &&
                       abs(location.coordinateY - oldCoordinateY) < 200)
                       {
                    if (tof.val[0] < 150) {
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
                while (abs(location.coordinateX - oldCoordinateX) < 200
                &&
                       abs(location.coordinateY - oldCoordinateY) < 200)
                       {
                    if (tof.val[0] < 150) {
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
                while (abs(location.coordinateX - oldCoordinateX) < 200
                &&
                       abs(location.coordinateY - oldCoordinateY) < 200)
                       {
                    if (tof.val[0] < 150) {
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
        // uart3.println("左壁探索中...");
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

        if (tof.val[0] < 120) {  // 前に壁が来た時の処理
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
                servo.isCorrectingAngle = 5;
            }
            if (tof.val[12] > tof.val[4]) {
                servo.isCorrectingAngle = -5;
            }
            app.delay(50);
        } else {
            if (tof.val[12] < 120) {
                servo.isCorrectingAngle = 5;
            }
            if (tof.val[4] < 120) {
                servo.isCorrectingAngle = -5;
            }
        }

        if (tof.val[4] > 300 && tof.val[12] < 300) {
            if (tof.val[12] > 120) {
                servo.isCorrectingAngle = -5;
            }
        }
        if (tof.val[12] > 300 && tof.val[4] < 300) {
            if (tof.val[4] > 120) {
                servo.isCorrectingAngle = 5;
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
    static bool oldstate    = false;
    static int waitmillis   = 0;
    static int blackCounter = 0;
    static int blueCounter  = 0;
    static int whiteCounter = 0;
    while (1) {
        floorSensor.colorJudgment();
        app.delay(period);
        if (floorSensor.isBlack) {
            blackCounter++;
        }

        if (floorSensor.isBlue) {
            blueCounter++;
        }

        if (floorSensor.isWhite) {
            blackCounter = 0;
            blueCounter  = 0;
        }

        if ((blackCounter > 4 || blueCounter > 4) && abs(gyro.slope) >= 10) {
            whiteCounter = 0;
            app.stop(rightWallApp);
            app.stop(leftWallApp);
            app.stop(AstarApp);
            app.delay(period);
            servo.suspend  = false;
            servo.velocity = -SPEED;
            app.delay(WAIT * 2);
            servo.angle -= 90;
            servo.isCorrectingAngle = 0;
            app.delay(WAIT);
            oldCoordinateX = location.coordinateX;
            oldCoordinateY = location.coordinateY;
            while (abs(location.coordinateX - oldCoordinateX) < 280 &&
                   abs(location.coordinateY - oldCoordinateY) < 280) {
                if (tof.val[0] < 130) {
                    break;
                }
                servo.velocity = SPEED;
                app.delay(period);
            }  // 次のタイルまで前進
            servo.suspend = true;
            app.delay(500);
            servo.suspend = false;
            app.start(rightWallApp);
            blackCounter = 0;
            blueCounter  = 0;
        }

        if (floorSensor.isBlack && blackCounter > 0 && abs(gyro.slope) < 10) {
        BLACK:
            servo.suspend = true;
            app.stop(rightWallApp);
            app.stop(leftWallApp);
            app.stop(AstarApp);
            app.delay(period);
            servo.suspend  = false;
            servo.velocity = -SPEED;
            app.delay(WAIT * 2);
            servo.angle -= 90;
            servo.isCorrectingAngle = 0;
            app.delay(WAIT);
            oldCoordinateX = location.coordinateX;
            oldCoordinateY = location.coordinateY;
            while (abs(location.coordinateX - oldCoordinateX) < 280 &&
                   abs(location.coordinateY - oldCoordinateY) < 280) {
                if (tof.val[0] < 130) {
                    break;
                }
                servo.velocity = SPEED;
                app.delay(period);
            }  // 次のタイルまで前進
            servo.suspend = true;
            app.delay(500);
            servo.suspend = false;
            app.start(rightWallApp);
            blackCounter = 0;
        }

        if (oldstate && millis() - 3000 < waitmillis) {
            app.delay(period);
        } else if (oldstate) {
            oldstate = false;
        } else if (floorSensor.isBlue && !oldstate && blueCounter > 3 &&
                   !floorSensor.isBlack && abs(gyro.slope <= 5)) {
            app.stop(rightWallApp);
            app.stop(leftWallApp);
            app.stop(AstarApp);
            oldCoordinateX = location.coordinateX;
            oldCoordinateY = location.coordinateY;
            while (abs(location.coordinateX - oldCoordinateX) < 150 &&
                   abs(location.coordinateY - oldCoordinateY) < 150) {
                floorSensor.colorJudgment();
                if (tof.val[0] < 125) {
                    break;
                }
                if (floorSensor.isBlack) {
                    goto BLACK;
                    break;
                }
                servo.velocity = SPEED;
                app.delay(period);
            }
            servo.suspend          = true;
            unsigned long temptime = millis();
            while (millis() - temptime < 5500) {
                floorSensor.colorJudgment();
                if (floorSensor.isBlack) {
                    goto BLACK;
                    break;
                }

                app.delay(period);
            }
            servo.suspend  = false;
            servo.velocity = SPEED;
            app.start(rightWallApp);
            waitmillis  = millis();
            oldstate    = true;
            blueCounter = 0;
        }
    }
}

#endif