#ifndef _OUTPUT_H_
#define _OUTPUT_H_

#include "Arduino.h"

#include "buzzer.h"
#include "led.h"
#include "sts3032.h"

Output buzzerPin = Output(PB6);
BUZZER buzzer(&buzzerPin);

HardwareSerial uart5(PD2, PC12);
STS3032 servo(&uart5);

#endif