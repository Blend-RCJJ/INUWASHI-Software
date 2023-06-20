#ifndef _UI_KIT_
#define _UI_KIT_

#include <Arduino.h>
#include "./device/device.h"

// images
#include "./img/blend.h"
#include "./img/ui_image/ui_image.h"

#define MODE_TOP 0

class UI_KIT {
   public:
    UI_KIT(void) {
    }

    int status = 0;

    void init(void) {
        touch.begin();
        display.init();
        display.publish();

        display.setBackgroundImage(image_data_blend);
        display.publish();
        delay(500);
    }

    void showSettingImage(int status) {
        display.setBackgroundImage(settingImagePtr[status]);
        display.publish();
    }

   private:
    const uint16_t* settingImagePtr[7] = {
        ui_top, ui_camera, ui_led, ui_buzzer, ui_loadcell, ui_tof, ui_floor};
};

#endif
