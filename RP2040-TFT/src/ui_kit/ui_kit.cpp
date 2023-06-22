#include "ui_kit.h"

#include "./device/touchscreen.h"
XPT2046_Touchscreen touchscreenDevice(7);
TOUCHSCREEN touch(&touchscreenDevice, 7);

#include "./device/display.h"
TFT_eSPI tft = TFT_eSPI();
TFT_eSprite sprite = TFT_eSprite(&tft);
DISPLAY_DEVICE display(&tft, &sprite);

void UI_KIT::init(void) {
    touch.begin();
    display.init();
    display.publish();

    display.createSprite();
    display.setBackgroundImage(bootImage);
    display.publish();
    delay(1000);
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
}

void UI_KIT::publish(void) {
    static int _mode = 0;
    if (settingMode != _mode) {
        showSettingImage(settingMode);
    }
    _mode = settingMode;
    display.publish();

    if (settingMode == 0) {
        topUI();
    }

    _isTouched = touch.isTouched;
}

void UI_KIT::topUI(void) {
    display.createSprite(100, 40);
    static unsigned long offset = 0;
    int val = ((millis() - offset) / 50) % 360;

    sprite.loadFont(bold40);
    sprite.fillScreen(TFT_WHITE);
    sprite.setTextColor(TFT_BLACK, TFT_WHITE);
    sprite.setCursor(0, 0);
    sprite.print(val);
    sprite.print("°");

    display.publish(25, 20);

    if (!_isTouched && touch.isTouched) {
        if (160 <= touch.point.x && touch.point.x <= 160 + 135) {
            if (31 <= touch.point.y && touch.point.y <= 31 + 18) {
                offset = millis();
            }
        }
    }
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

        if (xLine != 0 && yLine != 0) {
            settingMode = (xLine - 1) * 3 + yLine;
        }
    }
}