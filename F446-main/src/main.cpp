/** main.cpp
 * これは聖なるメインプログラム
 * あっぱれ！！あっぱれ！！
 */

// ヘッダファイルの読み込み

#include "Arduino.h"

#include "./kit/RTOS-Kit.h"
RTOS_Kit app;

#include "./core.h"

HardwareSerial uart1(PA10, PA9);

extern HardwareSerial uart1;

void setup() {
    initDevice();

    uart1.setRx(PA10);
    uart1.setTx(PA9);
    uart1.begin(115200);

    uart1.println("hello world");
}

void loop() {
    gyro.read();
    uart1.println(gyro.deg);
}