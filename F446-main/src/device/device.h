#ifndef _DEVICE_H_
#define _DEVICE_H_

#include <Arduino.h>
#include <Wire.h>

#include "./sensor/sensor.h"
#include "./actuator/actuator.h"

HardwareSerial uart1(PA10, PA9);
HardwareSerial uart3(PC5, PB10);

void initUART(void) {
    uart1.setRx(PA10);
    uart1.setTx(PA9);
    uart1.begin(115200);
    uart3.begin(115200);
}

void initI2C(void) {
    Wire.setSDA(PB9);
    Wire.setSCL(PB8);
    Wire.begin();
}

void initDevice(void) {
    buzzer.bootSound();

    led.bootIllumination();

    initI2C();
    initUART();

    loadcell.init();

    gyro.init();
    gyro.setOffset();

    led.initCompleteIllumination();
    delay(200);

    // // delay(1`)

    buzzer.bootSound();
}

#endif
