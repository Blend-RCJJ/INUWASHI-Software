#ifndef _RTOS_LCOATION_H_
#define _RTOS_LCOATION_H_

#include "../device/device.h"
#include "../kit/RTOS-Kit.h"
#include "./algorithm/location.h"

Location_Kit location;
extern RTOS_Kit app;

void mapUpdate(void) {
    int tempX = constrain(location.x + MAP_ORIGIN, 3, MAP_ORIGIN * 2 - 3);

    int tempY = constrain(location.y + MAP_ORIGIN, 3, MAP_ORIGIN * 2 - 3);

    if (location.mapData[tempX][tempY].isPassed == false) {
        location.mapData[tempX][tempY].isPassed = true;
        location.mapData[tempX][tempY].isDetected = true;
        location.mapData[tempX][tempY].firstPassedTime = millis();
    }

    if ((millis() - location.mapData[tempX][tempY].firstPassedTime) < 3000 &&
        (millis() - location.mapData[tempX][tempY].firstPassedTime) > 1000 &&
        abs(gyro.slope) == 0) {
        int judgeGain[2] = {400, 240};

        if (millis() - location.lastTrustY <= 20000) {
            if (tof.val[location.minIndex] > judgeGain[0] &&
                tof.val[(location.minIndex + 1) % 12] > judgeGain[1] &&
                tof.val[(location.minIndex + 15) % 12] > judgeGain[1]) {
                location.mapData[tempX][tempY + 1].isDetected = true;
            }

            if (tof.val[(location.minIndex + 6) % 12] > judgeGain[0] &&
                tof.val[(location.minIndex + 5) % 12] > judgeGain[1] &&
                tof.val[(location.minIndex + 7) % 12] > judgeGain[1]) {
                location.mapData[tempX][tempY - 1].isDetected = true;
            }
        }

        if (millis() - location.lastTrustX <= 20000) {
            if (tof.val[(location.minIndex + 3) % 12] > judgeGain[0] &&
                tof.val[(location.minIndex + 4) % 12] > judgeGain[1] &&
                tof.val[(location.minIndex + 2) % 12] > judgeGain[1]) {
                location.mapData[tempX + 1][tempY].isDetected = true;
            }
            if (tof.val[(location.minIndex + 9) % 12] > judgeGain[0] &&
                tof.val[(location.minIndex + 10) % 12] > judgeGain[1] &&
                tof.val[(location.minIndex + 8) % 12] > judgeGain[1]) {
                location.mapData[tempX - 1][tempY].isDetected = true;
            }
        }
    }
}

void locationApp(App) {
    while (1) {
        for (int i = 0; i < 100; i++) {
            location.updateOdometory(servo.rightWheelSpeed,
                                     servo.leftWheelSpeed, gyro.deg,
                                     gyro.slope);

            app.delay(location.period);
            mapUpdate();
        }

        location.updateObservationData(tof.vecX, tof.vecY, gyro.deg);
    }
}

#endif