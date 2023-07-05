#ifndef _INPUT_H_
#define _INPUT_H_

#include <Arduino.h>

#include <Wire.h>

#include "camera.h"
#include "distanceSensor.h"
#include "floorSensor.h"
#include "gyro.h"
#include "loadcell.h"
#include "switch.h"

Adafruit_BNO055 bno = Adafruit_BNO055(55, 0x28, &Wire);
Adafruit_NeoPixel stripFloor = Adafruit_NeoPixel(4, PB15, NEO_GRB + NEO_KHZ800);

HardwareSerial uart4(PA1, PA0);
DISTANCE_SENSOR tof(&uart4);

GYRO gyro(&bno);
SWITCH ui;
LOADCELL loadcell;
FLOOR_SENSOR floorSensor;

HardwareSerial uart2(PA3, PA2);
HardwareSerial uart6(PC7, PC6);
CAMERA camera[2] = {CAMERA(&uart6), CAMERA(&uart2)};  // 右左

#endif