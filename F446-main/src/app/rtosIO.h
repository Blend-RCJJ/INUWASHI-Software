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
        delay(3);
        floorSensor.redVal = analogRead(PC0);

        floorSensor.setFloorColor(floorSensor.green);
        delay(3);
        floorSensor.greenVal = analogRead(PC0);

        floorSensor.setFloorColor(floorSensor.blue);
        delay(3);
        floorSensor.blueVal = analogRead(PC0);
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