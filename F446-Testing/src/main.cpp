#include <Arduino.h>

HardwareSerial uart1(PA10, PA9);

void setup() {
    uart1.begin(9600);
}

void loop() {
    uart1.println("hello world");
}