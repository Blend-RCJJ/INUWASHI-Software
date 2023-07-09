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
#define WAIT 250
#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3
#define RETURN_TIME 300000  // 帰還開始時間(ms)
#define DISTANCE 95

bool virtualWall[MAP_ORIGIN * 2][MAP_ORIGIN * 2] = {false};
bool isRightWallApp                              = false;
bool oldstatus                                   = false;
static int oldmillis                             = 0;
int checkPointX                                  = MAP_ORIGIN;
int checkPointY                                  = MAP_ORIGIN;
static double oldCoordinateX                     = 0;
static double oldCoordinateY                     = 0;
static bool locationIsChanged                    = false;
static bool END                                  = false;
bool mazeSearch                                  = true;

void AstarApp(App);
void adjustmentApp(App);

int readRescueKitNum(void) {
    while (true) {
        if (uart2.available()) {
            char tmp = uart2.read();
            switch (tmp) {
                case '0':
                    return 0;
                    break;
                case '1':
                    return 1;
                    break;
                case '2':
                    return 2;
                    break;
                case '3':
                    return 3;
                    break;

                default:
                    break;
            }
        }
    }
}

void drop(void) {
    servo.suspend = true;
    app.delay(WAIT);
    servo.suspend      = false;
    servo.velocity     = 0;
    camera[0].Hcounter = 0;
    camera[0].Scounter = 0;
    camera[0].Ucounter = 0;
    servo.angle -= 90;
    app.delay(WAIT * 2);
    servo.angle -= 10;
    app.delay(WAIT * 2);
    servo.angle += 20;
    app.delay(WAIT * 2);
    servo.angle -= 10;
    app.delay(WAIT * 2);

    if (camera[0].Hcounter > camera[0].Scounter &&
        camera[0].Hcounter > camera[0].Ucounter) {
        uart2.println('3');
    } else if (camera[0].Scounter > camera[0].Hcounter &&
               camera[0].Scounter > camera[0].Ucounter) {
        uart2.println('2');
    } else if (camera[0].Ucounter > camera[0].Hcounter &&
               camera[0].Ucounter > camera[0].Scounter) {
        uart2.println('1');
    } else {
        uart2.println('0');
    }

    app.stop(servoApp);
    servo.driveAngularVelocity(-30, -45);
    app.delay(500);
    servo.driveAngularVelocity(-30, 45);
    app.delay(300);
    servo.driveAngularVelocity(30, 45);
    app.delay(500);
    servo.driveAngularVelocity(30, -45);
    app.delay(300);
    app.start(servoApp);

    servo.rescueKit(readRescueKitNum(), RIGHT);
}

void clearBuffer(void) {
    while (uart2.available()) {
        uart2.read();
    }
}

void rightWallApp(App) {
RESTART:
    mazeSearch = true;
    clearBuffer();

    while (1) {
        app.delay(period);
        if (!ui.toggle) {
            goto RESTART;
        }
        if (mazeSearch) {
            oldCoordinateX = location.coordinateX;
            oldCoordinateY = location.coordinateY;
            while (abs(location.coordinateX - oldCoordinateX) < 350 &&
                   abs(location.coordinateY - oldCoordinateY) < 350) {
                if (tof.val[0] < 130) {
                    servo.velocity = -SPEED;
                    app.delay(100);
                    servo.suspend  = true;
                    servo.velocity = 0;
                    break;
                }
                servo.velocity = SPEED;
                app.delay(period);
            }

            servo.suspend = true;
            app.delay(WAIT);
            servo.suspend = false;
            servo.angle += 90;
            app.delay(WAIT * 4);
            oldCoordinateX = location.coordinateX;
            oldCoordinateY = location.coordinateY;

            while (abs(location.coordinateX - oldCoordinateX) < 350 &&
                   abs(location.coordinateY - oldCoordinateY) < 350) {
                if (tof.val[0] < 130) {
                    servo.velocity = -SPEED;
                    app.delay(100);
                    servo.suspend  = true;
                    servo.velocity = 0;
                    break;
                }
                servo.velocity = SPEED;
                app.delay(period);
            }

            servo.suspend = true;
            app.delay(WAIT);
            servo.suspend = false;
            servo.angle += 90;
            app.delay(WAIT * 4);
            oldCoordinateX = location.coordinateX;
            oldCoordinateY = location.coordinateY;

            while (abs(location.coordinateX - oldCoordinateX) < 350 &&
                   abs(location.coordinateY - oldCoordinateY) < 350) {
                if (tof.val[0] < DISTANCE) {
                    servo.velocity = -SPEED;
                    app.delay(100);
                    servo.suspend  = true;
                    servo.velocity = 0;
                    break;
                }
                servo.velocity = SPEED;
                app.delay(period);
            }

            drop();
            // 色…1,文字…2
            servo.angle -= 90;
            app.delay(WAIT * 4);
            oldCoordinateX = location.coordinateX;
            oldCoordinateY = location.coordinateY;

            while (abs(location.coordinateX - oldCoordinateX) < 1500 &&
                   abs(location.coordinateY - oldCoordinateY) < 1500) {
                if (tof.val[0] < DISTANCE) {
                    servo.velocity = -SPEED;
                    app.delay(100);
                    servo.suspend  = true;
                    servo.velocity = 0;
                    break;
                }
                servo.velocity = SPEED;
                app.delay(period);
            }

            drop();

            // 色…4,文字…3
            servo.angle -= 90;
            app.delay(WAIT * 4);
            oldCoordinateX = location.coordinateX;
            oldCoordinateY = location.coordinateY;

            while (abs(location.coordinateX - oldCoordinateX) < 300 &&
                   abs(location.coordinateY - oldCoordinateY) < 300) {
                if (tof.val[8] > 470) {
                    servo.velocity = -SPEED;
                    app.delay(100);
                    servo.suspend  = true;
                    servo.velocity = 0;
                    break;
                }
                servo.velocity = SPEED;
                app.delay(period);
            }

            servo.suspend = true;
            app.delay(WAIT);
            servo.suspend = false;
            servo.angle += 90;
            app.delay(WAIT * 4);
            oldCoordinateX = location.coordinateX;
            oldCoordinateY = location.coordinateY;

            while (abs(location.coordinateX - oldCoordinateX) < 750 &&
                   abs(location.coordinateY - oldCoordinateY) < 750) {
                if (tof.val[0] < DISTANCE) {
                    servo.velocity = -SPEED;
                    app.delay(100);
                    servo.suspend  = true;
                    servo.velocity = 0;
                    break;
                }
                servo.velocity = SPEED;
                app.delay(period);
            }

            servo.suspend = true;
            app.delay(WAIT);
            servo.suspend = false;
            servo.angle += 90;
            app.delay(WAIT * 4);
            oldCoordinateX = location.coordinateX;
            oldCoordinateY = location.coordinateY;

            while (abs(location.coordinateX - oldCoordinateX) < 350 &&
                   abs(location.coordinateY - oldCoordinateY) < 350) {
                if (tof.val[0] < DISTANCE) {
                    servo.velocity = -SPEED;
                    app.delay(100);
                    servo.suspend  = true;
                    servo.velocity = 0;
                    break;
                }
                servo.velocity = SPEED;
                app.delay(period);
            }

            drop();

            // 色…3,文字…4
            servo.angle -= 90;
            app.delay(WAIT * 4);
            oldCoordinateX = location.coordinateX;
            oldCoordinateY = location.coordinateY;

            while (abs(location.coordinateX - oldCoordinateX) < 1200 &&
                   abs(location.coordinateY - oldCoordinateY) < 1200) {
                if (tof.val[0] < DISTANCE) {
                    servo.velocity = -SPEED;
                    app.delay(100);
                    servo.suspend  = true;
                    servo.velocity = 0;
                    break;
                }
                servo.velocity = SPEED;
                app.delay(period);
            }

            drop();

            // 色…2,文字…1
            servo.angle -= 90;
            app.delay(WAIT);
            oldCoordinateX = location.coordinateX;
            oldCoordinateY = location.coordinateY;

            while (abs(location.coordinateX - oldCoordinateX) < 300 &&
                   abs(location.coordinateY - oldCoordinateY) < 300) {
                if (tof.val[8] > 470) {
                    servo.suspend  = true;
                    servo.velocity = 0;
                    break;
                }
                servo.velocity = SPEED;
                app.delay(period);
            }

            oldCoordinateX = 0;
            oldCoordinateY = 0;

            servo.suspend  = true;
            servo.velocity = 0;
            app.delay(WAIT * 4);
            servo.suspend = false;
            servo.angle += 90;
            app.delay(WAIT * 4);

            servo.velocity = SPEED;
            app.delay(1800);
            servo.suspend  = true;
            servo.velocity = 0;
            app.delay(WAIT * 4);
            servo.suspend = false;
            servo.angle += 90;
            app.delay(WAIT * 4);

            servo.velocity = SPEED;
            app.delay(1200);
            servo.suspend  = true;
            servo.velocity = 0;
            app.delay(WAIT);

            mazeSearch = false;
        } else {  // おかえりなさい
            servo.suspend = true;

            app.stop(ledApp);

            while (1) {
                for (int i = 0; i < 256; i+= 20) {
                    led.setBrightness(TOP, 255 - i);
                    led.setBrightness(UI, 255 - i);
                    led.setColor(TOP, led.yellow);
                    led.setColor(UI, led.yellow);
                    led.showAll();
                    app.delay(1);
                }
            }
        }
    }
}

void counter(void) {
    if (camera[0].data == 'H') {
        camera[0].Hcounter++;
    } else if (camera[0].data == 'S') {
        camera[0].Scounter++;
    } else if (camera[0].data == 'U') {
        camera[0].Ucounter++;
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

        // if (loadcell.status == RIGHT) {
        //     app.stop(servoApp);
        //     servo.driveAngularVelocity(-30, -45);
        //     app.delay(500);
        //     servo.driveAngularVelocity(-30, 45);
        //     app.delay(500);
        //     isHit = false;
        // }
        // if (loadcell.status == LEFT) {
        //     app.stop(servoApp);
        //     servo.driveAngularVelocity(-30, 45);
        //     app.delay(500);
        //     servo.driveAngularVelocity(-30, -45);
        //     app.delay(500);
        //     isHit = false;
        // }
        // if (!isHit) {
        //     servo.velocity = SPEED;
        //     app.start(servoApp);
        //     isHit = true;
        // }
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