// FIXME: 汚すぎる
#include "location.h"

extern HardwareSerial uart1;

Location_Kit::Location_Kit(/* args */) {
}

void Location_Kit::updateOdometory(int rightWheelSpeed, int leftWheelSpeed,
                                   int angle, int slope) {
    double vec = (rightWheelSpeed + leftWheelSpeed) / 2.0;
    double vecX = vec * sin(radians(angle));
    double vecY = vec * cos(radians(angle));

    coordinateX += vecX * period * velocityConstant * cos(radians(slope));
    coordinateY += vecY * period * velocityConstant * cos(radians(slope));
}

void Location_Kit::updateObservationData(int *vecX, int *vecY, int angle) {
    int sensorX = 0;
    int sensorY = 0;

    // 北に一番近いセンサの判定
    int minY = 360;
    for (int i = 0; i < 16; i++) {
        if (min(abs((360 - round(i * 22.5)) - angle),
                360 - abs((360 - round(i * 22.5)) - angle)) < minY) {
            minY = min(abs((360 - round(i * 22.5)) - angle),
                       360 - abs((360 - round(i * 22.5)) - angle));
            minIndex = i;
        }
    }

    // センサから得られた両壁の幅
    const int sensorDir = 55;
    widthX = abs(vecX[(minIndex + 4) % 16]) + abs(vecX[(minIndex + 12) % 16]) +
             sensorDir;
    widthY = abs(vecY[minIndex]) + abs(vecY[(minIndex + 8) % 16]) + sensorDir;

    // 両壁に挟まれてる判定（信頼できる値かどうか？）
    trustX = false;
    trustY = false;
    if (abs(coordinateX - (round(coordinateX / 300.0) * 300.0)) <= 80) {
        if (290 < widthX && widthX < 310) {
            trustX = true;
            coordinateX = round(coordinateX / 300.0) * 300.0 +
                          abs(vecX[(minIndex + 12) % 16]) - 130;

            lastCorrection = millis();
            lastTrustX = millis();
        }
        if (590 < widthX && widthX < 610) {
            trustX = true;

            int temp;

            if (abs(vecX[(minIndex + 4) % 16]) <
                abs(vecX[(minIndex + 12) % 16])) {
                temp = round(coordinateX / 300.0) * 300.0 +
                       (300 - abs(vecX[(minIndex + 3) % 16]) - 40) - 130;
            } else {
                temp = round(coordinateX / 300.0) * 300.0 +
                       abs(vecX[(minIndex + 12) % 16]) - 130;
            }

            if (abs(coordinateX - temp) < 150) {
                coordinateX = temp;
            }

            lastCorrection = millis();
            lastTrustX = millis();
        }
    }
    if (abs(coordinateY - (round(coordinateY / 300.0) * 300.0)) <= 80) {
        if (290 < widthY && widthY < 310) {
            trustY = true;
            coordinateY = round(coordinateY / 300.0) * 300.0 +
                          abs(vecY[(minIndex + 8) % 16]) - 130;
            lastCorrection = millis();
            lastTrustY = millis();
        }
        if (590 < widthY && widthY < 610) {
            trustY = true;
            int temp;
            if (abs(vecY[minIndex]) < abs(vecY[(minIndex + 8) % 16])) {
                temp = round(coordinateY / 300.0) * 300.0 +
                       (300 - abs(vecY[minIndex]) - 40) - 130;
            } else {
                temp = round(coordinateY / 300.0) * 300.0 +
                       abs(vecY[(minIndex + 8) % 16]) - 130;
            }
            if (abs(coordinateY - temp) < 150) {
                coordinateY = temp;
            }

            lastCorrection = millis();
            lastTrustY = millis();
        }
    }

    // L字判定
    

    x = round(coordinateX / 300.0);
    y = round(coordinateY / 300.0);
}

// Location_Kit location;
