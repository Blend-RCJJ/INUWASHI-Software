#ifndef _SERIAL_SERVO_H
#define _SERIAL_SERVO_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "./SCServo/SCServo.h"

class SERIAL_SERVO {
   public:
    SERIAL_SERVO(HardwareSerial *ptr);
    HardwareSerial *serialPtr;

    const int maximumSpeed = 7000;
    const int baudRate = 1000000;
    void directDrive(int id, int percent, int acceleration = 0);
    void drive(int velocity, int angle, int gyroDeg);
    void driveAngularVelocity(int velocity, int angularVelocity);

    void stop(void);

    int velocity = 0;
    int angle = 0;

    int rightWheelSpeed = 0;
    int leftWheelSpeed = 0;

   private:
};

#endif