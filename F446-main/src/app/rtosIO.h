#ifndef _RTOS_IO_H_
#define _RTOS_IO_H_

#include "../device/device.h"

extern RTOS_Kit app;

const int period = 10;  // 制御周期

void sensorReadingApp(App) {
    ui.read();
    tof.read();
    gyro.read();
    camera.read();
    loadcell.read();
    floorSensor.read();

    app.delay(period);
}

void servoApp(App) {
    if (servo.suspend == true) {
        if (servo.isAngleCorrectionEnabled == true) {
            servo.drive(servo.velocity, servo.angle);
        } else {
            servo.driveAngularVelocity(servo.velocity, servo.angularVelocity);
        }
    }

    app.delay(period);
}

#endif