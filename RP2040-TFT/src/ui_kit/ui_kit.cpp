#include "ui_kit.h"

#include "./device/touchscreen.h"
XPT2046_Touchscreen touchscreenDevice(7);
TOUCHSCREEN touch(&touchscreenDevice, 7);

// display
#include "./device/display.h"
TFT_eSPI tft = TFT_eSPI();
TFT_eSprite sprite = TFT_eSprite(&tft);
DISPLAY_DEVICE display(&tft, &sprite);

void UI_KIT::init(void) {
    touch.begin();
    display.init();
    display.publish();

    display.setBackgroundImage(image_data_blend);
    display.publish();
    delay(500);
}

void UI_KIT::showSettingImage(int status) {
    display.createSprite();
    display.setBackgroundImage(settingImagePtr[status]);
}

void UI_KIT::touchUpdate(void) {
    touch.read();

    if (settingMode != 0) {
        homeScreenGesture();
    } else {
        selectSettingMode();
    }

    _isTouched = touch.isTouched;
}

void UI_KIT::publish(void) {
    static int _mode = 0;
    if (settingMode != _mode) {
        showSettingImage(settingMode);
    }
    _mode = settingMode;

    display.publish();
}

void UI_KIT::homeScreenGesture(void) {
    static bool flag = false;

    static int yWhenFlagged = 0;
    static unsigned long timeWhenFlagged = 0;

    if (touch.isTouched) {
        if (abs(2000 - touch.raw.x) < 800 && touch.raw.y > 3000 &&
            !_isTouched) {
            flag = true;
            yWhenFlagged = touch.raw.y;
            timeWhenFlagged = millis();
        }

        if (flag && millis() - timeWhenFlagged < 200) {
            if (touch.raw.y < yWhenFlagged - 300) {
                flag = false;
                settingMode = 0;
            }
        }
    }
}

void UI_KIT::selectSettingMode(void) {
    if (touch.isTouched && !_isTouched) {
        int xLine = 0;
        if (touch.point.y >= 64 && touch.point.y <= 64 + 70) {
            xLine = 1;
        } else if (touch.point.y >= 154 && touch.point.y <= 154 + 70) {
            xLine = 2;
        }

        int yLine = 0;
        if (touch.point.x >= 25 && touch.point.x <= 25 + 70) {
            yLine = 1;
        } else if (touch.point.x >= 125 && touch.point.x <= 125 + 70) {
            yLine = 2;
        } else if (touch.point.x >= 225 && touch.point.x <= 225 + 70) {
            yLine = 3;
        }

        settingMode = yLine + (xLine - 1) * 3;
    }
}