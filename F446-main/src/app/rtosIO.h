#ifndef _RTOS_IO_H_
#define _RTOS_IO_H_

#include "../device/device.h"
#include "../kit/RTOS-Kit.h"

extern RTOS_Kit app;

const int period = 10;  // 制御周期

void sensorApp(App) {
    while (1) {
        ui.read();
        gyro.read();
        tof.read();
        tof.calc(gyro.deg);
        // camera.read(); //FIXME: ポインタの設定違う
        loadcell.read();
        floorSensor.init();

        floorSensor.setFloorColor(floorSensor.red);
        app.delay(5);
        floorSensor.read();
        floorSensor.setFloorColor(floorSensor.green);
        app.delay(5);
        floorSensor.read();
        floorSensor.setFloorColor(floorSensor.blue);
        app.delay(5);
        floorSensor.read();

        app.delay(period);
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

        app.delay(period);
    }
}

#endif