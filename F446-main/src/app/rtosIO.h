#ifndef _RTOS_IO_H_
#define _RTOS_IO_H_

#include "../device/device.h"
#include "../kit/RTOS-Kit.h"

#include "./algorithm/victim.h"
#include "../device/device.h"

extern RTOS_Kit app;

const int period = 10;  // 制御周期

extern int robotStatus;

void sensorApp(App) {
    floorSensor.init();

    while (1) {
        ui.read();
        gyro.read();
        tof.read();
        tof.calc(gyro.deg);

        victim.read();

        loadcell.read();
        
        floorSensor.setFloorColor(floorSensor.red);
        app.delay(2);
        floorSensor.redVal = analogRead(PC0);

        floorSensor.setFloorColor(floorSensor.blank);
        app.delay(2);
        floorSensor.blankVal = analogRead(PC0);

        floorSensor.setFloorColor(floorSensor.blue);
        app.delay(2);
        floorSensor.blueVal = analogRead(PC0);
    }
}

void servoApp(App) {
    while (1) {
        if (!servo.suspend) {
            if (servo.isAngleCorrectionEnabled) {
                servo.drive(servo.velocity,
                            servo.angle + servo.isCorrectingAngle);
            } else {
                servo.driveAngularVelocity(servo.velocity,
                                           servo.angularVelocity);
            }
        } else {
            servo.stop();
        }
        servo.angle %= 360;
        app.delay(1);
    }
}

double mapDouble(double x, double in_min, double in_max, double out_min,
                 double out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void ledApp(App) {
    int ledStatus = 0;
    int victimId = 0;
    unsigned long startTime = millis();
    for (int i = 0; i < 4; i++) {
        led.setColor(i, led.cyan);
        led.setBrightness(i, 255);
    }
    led.showAll();

    while (ui.toggle == 0) {
        app.delay(10);
    }

    while (1) {
        if (!victim.isDetected) {
            if (ledStatus != 1) {
                ledStatus = 1;
                led.setGlowColor();
                led.showAll();
            }
            victimId = 0;
        } else {
            ledStatus = 2;
            static bool blink = true;

            int brightness;
            if (blink) {
                brightness = 255;
            } else {
                brightness = 0;
            }

            for (int i = 0; i < 4; i++) {
                led.setBrightness(i, brightness);
                led.setColor(i, victim.color(victimId));
            }
            led.showAll();

            app.delay(500);
            blink = !blink;
        }

        app.delay(10);
    }
}

#endif