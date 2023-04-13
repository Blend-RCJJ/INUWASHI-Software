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

#include "./app/rtosMain.h"

void setup() {
    initDevice();

    app.create(mainApp);
    app.start(mainApp);

    app.startRTOS();
}

void loop() {
    /** ここには何も書かない
     * RTOS管理下にあるので書いても意味ないです
     */
}