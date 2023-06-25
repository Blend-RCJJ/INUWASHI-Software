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

    int img;
    if (data.status == 0) {
        img = settingMode;
    } else {
        img = 7;
    }

    if (img != _mode) {
        showSettingImage(img);
    }
    _mode = img;
    display.publish();

    switch (img) {
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
        case 7:
            runningUI();
            break;
    }

    _isTouched = touch.isTouched;
}

void UI_KIT::runningUI(void) {
    display.createSprite(150, 30);
    uint16_t orange = sprite.color565(255, 195, 60);
    sprite.fillScreen(orange);
    sprite.setTextColor(TFT_BLACK, orange);
    sprite.loadFont(bold25);
    sprite.setCursor(0, 2);
    sprite.print("Exploring");
    display.publish(46, 142);

    display.createSprite(70, 20);
    sprite.fillScreen(orange);
    sprite.setTextColor(TFT_BLACK, orange);
    sprite.loadFont(bold25);
    sprite.setCursor(0, 2);
    sprite.loadFont(regular15);
    int minute = (millis() - data.runningTimer) / 60000;
    int second = ((millis() - data.runningTimer) % 60000) / 1000;
    int centisecond = ((millis() - data.runningTimer) % 1000) / 10;
    sprite.print(minute);
    sprite.print(":");
    if (second < 10) {
        sprite.print("0");
    }
    sprite.print(second);
    sprite.print(".");
    if (centisecond < 10) {
        sprite.print("0");
    }
    sprite.print(centisecond);
    display.publish(221, 150);

    display.createSprite(80, 40);
    sprite.loadFont(bold40);
    sprite.fillScreen(TFT_WHITE);
    sprite.setTextColor(TFT_BLACK, TFT_WHITE);
    sprite.setCursor(0, 0);
    sprite.print(data.x);
    display.publish(84, 28);
    display.createSprite(80, 40);
    sprite.fillScreen(TFT_WHITE);
    sprite.setTextColor(TFT_BLACK, TFT_WHITE);
    sprite.setCursor(0, 0);
    sprite.print(data.y);
    display.publish(84, 81);

display.createSprite(90, 30);
    sprite.loadFont(bold20);
    sprite.fillScreen(TFT_WHITE);
    sprite.setTextColor(TFT_BLACK, TFT_WHITE);
    sprite.setCursor(0, 0);
    sprite.print(data.coordinateX);
    sprite.print("mm");
    display.publish(36, 201 + 3);
display.createSprite(90, 30);
    sprite.loadFont(bold20);
    sprite.fillScreen(TFT_WHITE);
    sprite.setTextColor(TFT_BLACK, TFT_WHITE);
    sprite.setCursor(0, 0);
    sprite.print(data.coordinateY);
    sprite.print("mm");
    display.publish(135, 201 + 3);
    display.createSprite(70, 30);
    sprite.loadFont(bold20);
    sprite.fillScreen(TFT_WHITE);
    sprite.setTextColor(TFT_BLACK, TFT_WHITE);
    sprite.setCursor(0, 0);
    sprite.print(data.gyro);
    sprite.print("°");
    display.publish(238, 201 + 3);
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