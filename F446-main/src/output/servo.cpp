#include "servo.h"

SMS_STS serialServo;

extern HardwareSerial uart1;

SERVO::SERVO(HardwareSerial *ptr) {
    serialPtr = ptr;
    serialPtr->begin(baudRate);
    serialServo.pSerial = serialPtr;

    // serialServo.WheelMode(1);
    for (int i = 1; i <= 4; i++) {
        serialServo.unLockEprom(i);
        serialServo.EnableTorque(i, 1);
        serialServo.LockEprom(i);
    }

    serialServo.unLockEprom(5);
    serialServo.EnableTorque(5, 1);
    serialServo.LockEprom(5);
}

void SERVO::directDrive(int id, int percent, int acceleration) {
    if (id != 4) {
        int sendData;
        sendData = percent * maximumSpeed / 100;
        sendData = constrain(sendData, -maximumSpeed, maximumSpeed);

        serialServo.WriteSpe(id + 1, sendData, acceleration);
    } else {
        int sendData;
        sendData = percent * 80;
        sendData = constrain(sendData, -8000, 8000);

        serialServo.WriteSpe(5, sendData, acceleration);
    }
}

void SERVO::driveAngularVelocity(int velocity, int angularVelocity) {
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

void SERVO::drive(int velocity, int angle, int gyro) {
    const double Kp = -2.5;

    // 0-360変換
    while (angle < 0) {
        angle += 360;
    }
    angle %= 360;

    int angularVelocity = gyro - angle;

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

void SERVO::stop(void) {
    driveAngularVelocity(0, 0);
}