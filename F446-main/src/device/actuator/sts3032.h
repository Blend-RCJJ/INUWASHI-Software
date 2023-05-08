#ifndef _STS3032_H_
#define _STS3032_H_

#include <Arduino.h>

#include "./SCServo/SCServo.h"
#include "../sensor/gyro.h"

extern GYRO gyro;

class STS3032 {
   public:
    STS3032(HardwareSerial *ptr);
    HardwareSerial *serialPtr;

    const int maximumSpeed = 7000;
    const int baudRate = 1000000;
    
    void directDrive(int id, int percent, int acceleration = 0);
    void drive(int velocity, int angle);
    void driveAngularVelocity(int velocity, int angularVelocity);
    void stop(void);

    int velocity = 0;
    int angle = 0;
    int isCorrectingAngle = 0;
    int angularVelocity = 0;

    int rightWheelSpeed = 0;
    int leftWheelSpeed = 0;

    bool isAngleCorrectionEnabled = true;
    bool suspend = true;

    void rescueKit(int num, int position);
    int sumOfRescueKit = 0;

   private:
};

#endif