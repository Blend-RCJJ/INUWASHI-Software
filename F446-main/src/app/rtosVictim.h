#ifndef _RTOS_VICTIM_H_
#define _RTOS_VICTIM_H_

#include "../device/device.h"
#include "../kit/RTOS-Kit.h"

extern RTOS_Kit app;

void victimNotifyApp(App) {
    static int id = 0;  // NOTE:　仮だから他の用途に使うな
    static int victimID[6] = {VICTIM_H,   VICTIM_S,      VICTIM_U,
                              VICTIM_RED, VICTIM_YELLOW, VICTIM_GREEN};

    int rescueKitNum = 0;

    victim.isDetected = true;
    victim.id = id;

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

    victim.isDetected = false;

    while (1) {
        app.delay(1000);
    }
}

#endif