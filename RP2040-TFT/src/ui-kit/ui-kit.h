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

    void init(void);
    void showSettingImage(int status);

    void touchUpdate(void);

    bool goToHome = false;
    void homeScreenGesture(void);

   private:
    const uint16_t* settingImagePtr[7] = {
        ui_top, ui_camera, ui_led, ui_buzzer, ui_loadcell, ui_tof, ui_floor};
};

void UI_KIT::init(void) {
    touch.begin();
    display.init();
    display.publish();

    display.setBackgroundImage(image_data_blend);
    display.publish();
    delay(500);
}

void UI_KIT::showSettingImage(int status) {
    display.setBackgroundImage(settingImagePtr[status]);
    display.publish();
}

void UI_KIT::touchUpdate(void) {
    touch.read();
    homeScreenGesture();

    Serial.print(touch.point.y);
    Serial.print("\t");
}

void UI_KIT::homeScreenGesture(void) {
    static bool _isTouched = false;
    static bool flag = false;

    static int yWhenFlagged = 0;
    static unsigned long timeWhenFlagged = 0;

    if (touch.isTouched && !_isTouched) {
        if (touch.point.y > 180) {
            yWhenFlagged = touch.point.y;
            timeWhenFlagged = millis();
            flag = true;

        } else {
            flag = false;
        }
    } else if (!touch.isTouched) {
        flag = false;
    }

    if (touch.point.y < yWhenFlagged - 10 && flag) {
        if (millis() - timeWhenFlagged < 100) {
            goToHome = true;
        }
        flag = false;
    }

    _isTouched = touch.isTouched;

    Serial.print(touch.isTouched);
    Serial.print("\t");
    Serial.print(touch.point.y);
    Serial.print("\t");
    Serial.print(flag);
    Serial.print("\t");
    Serial.print(yWhenFlagged);
    Serial.println();
}

#endif