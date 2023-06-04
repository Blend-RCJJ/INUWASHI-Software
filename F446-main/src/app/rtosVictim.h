#ifndef _RTOS_UI_H_
#define _RTOS_UI_H_

#include "../device/device.h"
#include "../kit/RTOS-Kit.h"

extern RTOS_Kit app;

void victimNotifyApp(App) {
    static int victim = 0;  // NOTE:　仮だから他の用途に使うな
    static int victimID[6] = {VICTIM_H,   VICTIM_S,      VICTIM_U,
                              VICTIM_RED, VICTIM_YELLOW, VICTIM_GREEN};

    int rescueKitNum = 0;

    switch (victimID[victim]) {
        case VICTIM_H:
            buzzer.sambaII();
            rescueKitNum = 3;
            break;

        case VICTIM_S:
            buzzer.tokyoOndo();
            rescueKitNum = 2;
            break;

        case VICTIM_U:
            buzzer.sakura();
            break;

        case VICTIM_RED:
            buzzer.shoten();
            rescueKitNum = 1;
            break;

        case VICTIM_YELLOW:
            buzzer.shogun();
            rescueKitNum = 1;
            break;

        case VICTIM_GREEN:
            buzzer.yuyake();
            break;

        default:
            break;
    }

    app.delay(500);
    buzzer.rescueKit(rescueKitNum);

    victim++;
    victim %= 6;

    while (1) {
        app.delay(1000);
    }
}

#endif