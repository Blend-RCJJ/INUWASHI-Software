#ifndef _OUTPUT_H_
#define _OUTPUT_H_

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "buzzer.h"
#include "led.h"
#include "serialServo.h"

SPEAKER buzzer;

HardwareSerial uart5(PD2, PC12);
// SERIAL_SERVO faewfaewa(&uart5);

#endif