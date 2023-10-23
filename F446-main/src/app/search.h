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
void turnRight(void);
void turnLeft(void);
void turnReverse(void);

void rightWallApp(App) {
    double oldCoordinateX = 0;
    double oldCoordinateY = 0;
    while (1) {
        app.delay(period);
        servo.suspend = true;
        servo.velocity = 0;
        oldCoordinateX = location.coordinateX;
        oldCoordinateY = location.coordinateY;

        tof.wallCondition();

        switch (tof.wallStatus) {
            case 0:
                turnRight();
                break;
            case 1:
                turnRight();
                break;
            case 2:
                break;
            case 3:
                turnRight();
                break;
            case 4:
                turnRight();
                break;
            case 5:
                turnLeft();
                break;
            case 6:
                turnRight();
                break;
            case 7:
                turnRight();
                break;
            case 8:
                break;
            case 9:
                break;
            case 10:
                turnRight();
                break;
            case 11:
                turnLeft();
                break;
            case 12:
                turnReverse();
                break;
            case 13:
                turnRight();
                break;
            case 14:
                break;
            default:
                break;
        }
          while (abs(location.coordinateX - oldCoordinateX) < 280 &&
               abs(location.coordinateY - oldCoordinateY) < 280) {
            if (tof.val[0] < 130) {
                break;
            }
            servo.suspend = false;
            servo.velocity = SPEED;
            app.delay(period);
        }  // 次のタイルまで前進
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

void turnRight(void) {
    servo.suspend = true;
    app.delay(WAIT);
    servo.suspend = false;
    servo.angle += 90;
    servo.isCorrectingAngle = 0;
    app.delay(WAIT * 2);
}

void turnLeft(void) {
    servo.suspend = true;
    app.delay(WAIT);
    servo.suspend = false;
    servo.angle -= 90;
    servo.isCorrectingAngle = 0;
    app.delay(WAIT * 2);
}

void turnReverse(void) {
    servo.suspend = true;
    app.delay(WAIT);
    servo.suspend = false;
    servo.angle += 180;
    servo.isCorrectingAngle = 0;
    app.delay(WAIT * 3);
}
#endif