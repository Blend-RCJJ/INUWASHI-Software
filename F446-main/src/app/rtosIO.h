#ifndef _RTOS_IO_H_
#define _RTOS_IO_H_

#include "../device/device.h"

extern RTOS_Kit app;

const int period = 10;  // 制御周期

void sensorApp(App) {
    while (1) {
        ui.read();
        tof.read();
        gyro.read();
        // camera.read(); //FIXME: ポインタの設定違う
        loadcell.read();
        floorSensor.read();

        app.delay(period);
    }
}

void servoApp(App) {
    while (1) {
        if (!servo.suspend) {
            if (servo.isAngleCorrectionEnabled) {
                servo.drive(servo.velocity, servo.angle);
            } else {
                servo.driveAngularVelocity(servo.velocity,
                                           servo.angularVelocity);
            }
        } else {
            servo.stop();
        }

        app.delay(period);
    }
}

#endif