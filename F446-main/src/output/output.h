#ifndef _OUTPUT_H_
#define _OUTPUT_H_

#include "Arduino.h"

#include "buzzer.h"
#include "led.h"
#include "serialServo.h"

Output buzzerPin = Output(PB6);
BUZZER buzzer(&buzzerPin);

#endif