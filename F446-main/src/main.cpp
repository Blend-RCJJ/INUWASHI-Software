/** main.cpp
 * これは聖なるメインプログラム
 * あっぱれ！！あっぱれ！！
 */

// ヘッダファイルの読み込み

#include <Arduino.h>

#include "./kit/RTOS-Kit.h"
RTOS_Kit app;

#include "./device/device.h"
#include "./app/rtosMain.h"
#include "./app/rtosIO.h"

void setup() {
    initDevice();

    // 処理系統
    app.create(mainApp, firstPriority);
    app.create(rightWallApp);
    app.create(leftWallApp);

    // 入出力系統
    app.create(sensorApp, secondPriority);
    app.create(servoApp, secondPriority);

    app.start(mainApp);
    app.startRTOS();
}

void loop() {
    /** ここには何も書かない
     * RTOS管理下にあるので書いても意味ないです
     */
}