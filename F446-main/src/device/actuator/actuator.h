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

Adafruit_NeoPixel topLED(32, PC1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel rightLED(7, PB13, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel leftLED(7, PA15, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel uiLED(14, PB14, NEO_GRB + NEO_KHZ800);
LED led(&topLED, &rightLED, &leftLED, &uiLED);

#endif