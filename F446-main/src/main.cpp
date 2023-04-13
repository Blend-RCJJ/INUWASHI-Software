/** main.cpp
 * これは聖なるメインプログラム
 * あっぱれ！！あっぱれ！！
 */

// ヘッダファイルの読み込み

#include <Arduino.h>
#include <EEPROM.h>

#include "./kit/RTOS-Kit.h"
RTOS_Kit app;

#include "./device.h"

void setup() {
    initDevice();

    uart1.println("hello world");
}

void loop() {
    gyro.read();
    uart1.println(millis());

    servo.drive(100, 0);
}