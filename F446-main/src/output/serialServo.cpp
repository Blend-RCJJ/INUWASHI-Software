#include "serialServo.h"

SMS_STS sts3032;

SERIAL_SERVO::SERIAL_SERVO(HardwareSerial *ptr) {
    serialPtr = ptr;
    serialPtr->begin(baudRate);
    sts3032.pSerial = serialPtr;

    // sts3032.WheelMode(1);
    for (int i = 1; i <= 4; i++) {
        sts3032.unLockEprom(i);
        sts3032.EnableTorque(i, 1);
        sts3032.LockEprom(i);
    }

    sts3032.unLockEprom(5);
    sts3032.EnableTorque(5, 1);
    sts3032.LockEprom(5);
}

void SERIAL_SERVO::directDrive(int id, int percent, int acceleration) {
    if (id != 4) {
        int sendData;
        sendData = percent * maximumSpeed / 100;
        sendData = constrain(sendData, -maximumSpeed, maximumSpeed);

        sts3032.WriteSpe(id + 1, sendData, acceleration);
    } else {
        int sendData;
        sendData = percent * 80;
        sendData = constrain(sendData, -8000, 8000);

        sts3032.WriteSpe(5, sendData, acceleration);
    }
}

void SERIAL_SERVO::driveAngularVelocity(int velocity, int angularVelocity) {
    int data[2];
    data[0] = angularVelocity - velocity;
    data[1] = angularVelocity + velocity;

    rightWheelSpeed = -data[0];
    leftWheelSpeed = data[1];

    for (int i = 0; i < 2; i++) {
        data[i] = constrain(data[i], -100, 100);
    }

    for (int i = 0; i < 2; i++) {
        directDrive(i, data[0]);
    }

    for (int i = 2; i < 4; i++) {
        directDrive(i, data[1]);
    }
    // directDrive(4, 10);
}

void SERIAL_SERVO::drive(int velocity, int angle, int gyroDeg) {
    const double Kp = -2.5;

    // 0-360変換
    while (angle < 0) {
        angle += 360;
    }
    angle %= 360;

    int angularVelocity = gyroDeg - angle;

    //-180から180変換
    while (angularVelocity < 0) {
        angularVelocity += 360;
    }
    if (angularVelocity > 180) {
        angularVelocity -= 360;
    }

    if (abs(angularVelocity) > 40) {
        angularVelocity *= Kp;
        driveAngularVelocity(0, angularVelocity);
    } else {
        angularVelocity *= Kp;
        driveAngularVelocity(velocity, angularVelocity);
    }
}

void SERIAL_SERVO::stop(void) {
    driveAngularVelocity(0, 0);
}