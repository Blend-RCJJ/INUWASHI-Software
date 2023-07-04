#ifndef _RTOS_VICTIM_H_
#define _RTOS_VICTIM_H_

#include "../device/device.h"
#include "../kit/RTOS-Kit.h"

extern RTOS_Kit app;

void victimNotifyApp(App) {
    int rescueKitNum = 0;
    int id = 0;

    switch (id) {
        case 0:
            buzzer.sambaII();
            rescueKitNum = 3;
            break;

        case 1:
            buzzer.tokyoOndo();
            rescueKitNum = 2;
            break;

        case 2:
            buzzer.sakura();
            break;

        case 3:
            buzzer.shoten();
            rescueKitNum = 1;
            break;

        case 4:
            buzzer.shogun();
            rescueKitNum = 1;
            break;

        case 5:
            buzzer.yuyake();
            break;

        default:
            break;
    }

    app.delay(500);
    buzzer.rescueKit(rescueKitNum);

    id++;
    id %= 6;

    while (1) {
        app.delay(1000);
    }
}

#endif