/** main.cpp
 * これは聖なるメインプログラム
 * あっぱれ！！あっぱれ！！
 */

// ヘッダファイルの読み込み

#include <Arduino.h>

#include "./kit/RTOS-Kit.h"
RTOS_Kit app;

#include "./app/rtosIO.h"
#include "./app/rtosMain.h"
#include "./device/device.h"

void setup() {
    initDevice();

    // 処理系統
    app.create(mainApp, firstPriority);
    app.create(rightWallApp);
    app.create(leftWallApp);
    app.create(absoluteDirectionApp);
    app.create(locationApp, firstPriority);

    // 入出力系統
    app.create(sensorApp, secondPriority);
    app.create(servoApp, secondPriority);
    app.create(monitorApp);

    app.start(mainApp);
    app.startRTOS();
}

void loop() {
    /** ここには何も書かない
     * RTOS管理下にあるので書いても意味ないです
     */
}