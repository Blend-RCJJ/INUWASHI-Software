/** main.cpp
 * これは聖なるメインプログラム
 * あっぱれ！！あっぱれ！！
 */

// ヘッダファイルの読み込み

#include <Arduino.h>
#include <EEPROM.h>

#include "./kit/RTOS-Kit.h"
RTOS_Kit app;

#include "./device/device.h"

void setup() {
    initDevice();
}

void loop() {
    gyro.read();
    servo.drive(100, 0);
}