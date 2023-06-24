#include "ui_kit.h"

#include "./device/touchscreen.h"
#include "./device/display.h"
#include "./databox.h"

extern XPT2046_Touchscreen touchscreenDevice;
extern TOUCHSCREEN touch;
extern TFT_eSPI tft;
extern TFT_eSprite sprite;
extern DISPLAY_DEVICE display;
extern DATA_BOX data;

void UI_KIT::init(void) {
    touch.begin();
    display.init();

    display.createSprite();
    display.setBackgroundImage(bootImage);
    display.publish();

    data.init();
    delay(1000);
}

void UI_KIT::showSettingImage(int status) {
    display.createSprite();
    display.setBackgroundImage(settingImagePtr[status]);
}

void UI_KIT::touchUpdate(void) {
    touch.read();
}

void UI_KIT::publish(void) {
    data.update();

    static int _mode = -1;
    if (settingMode != _mode) {
        showSettingImage(settingMode);
    }
    _mode = settingMode;
    display.publish();

    switch(settingMode) {
        case 0:
            topUI();
            break;
        case 1:
            cameraUI();
            break;
        case 2:
            ledUI();
            break;
        case 3:
            buzzerUI();
            break;
        case 4:
            loadcellUI();
            break;
        case 5:
            tofUI();
            break;
        case 6:
            floorUI();
            break;
    }

    _isTouched = touch.isTouched;
}

void UI_KIT::cameraUI(void) {
    homeScreenGesture();
}

void UI_KIT::ledUI(void) {
    homeScreenGesture();
}

void UI_KIT::buzzerUI(void) {
    homeScreenGesture();
}

void UI_KIT::loadcellUI(void) {
    homeScreenGesture();
}

void UI_KIT::tofUI(void) {
    homeScreenGesture();
}

void UI_KIT::floorUI(void) {
    homeScreenGesture();
}

void UI_KIT::topUI(void) {
    selectSettingMode();

    display.createSprite(100, 40);

    sprite.loadFont(bold40);
    sprite.fillScreen(TFT_WHITE);
    sprite.setTextColor(TFT_BLACK, TFT_WHITE);
    sprite.setCursor(0, 0);
    sprite.print(data.gyro);
    sprite.print("°");

    display.publish(25, 18);

    if (!_isTouched && touch.isTouched) {
        if (160 <= touch.point.x && touch.point.x <= 160 + 135) {
            if (31 <= touch.point.y && touch.point.y <= 31 + 18) {
                data.gyroReset = true;
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