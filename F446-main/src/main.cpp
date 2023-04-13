/** main.cpp
 * これは聖なるメインプログラム
 * あっぱれ！！あっぱれ！！
 */

// ヘッダファイルの読み込み

#include "Arduino.h"

#include "./kit/RTOS-Kit.h"
RTOS_Kit app;

#include "./core.h"

HardwareSerial uart5(PD2, PC12);
// STS3032 faewfaewa(&uart5);

void setup() {
    initDevice();

    uart1.println("hello world");
}

void loop() {
    gyro.read();
    uart1.println(gyro.deg);
}