#ifndef _SERVO_H
#define _SERVO_H

#include <Arduino.h>

#include "./SCServo/SCServo.h"
class SERVO {
   public:
    SERVO(HardwareSerial *ptr);
    HardwareSerial *serialPtr;

    const int maximumSpeed = 7000;
    const int baudRate = 1000000;
    void directDrive(int id, int percent, int acceleration = 0);
    void drive(int velocity, int angle, int gyro);
    void driveAngularVelocity(int velocity, int angularVelocity);

    void stop(void);

    int velocity = 0;
    int angle = 0;

    int rightWheelSpeed = 0;
    int leftWheelSpeed = 0;

   private:
};

#endif