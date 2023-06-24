#ifndef _UI_KIT_
#define _UI_KIT_

#include "./img/blend.h"
#include "./img/ui_image/ui_image.h"

#include "./font/bold20.h"
#include "./font/bold25.h"
#include "./font/bold40.h"
#include "./font/bold60.h"
#include "./font/regular15.h"

class UI_KIT {
   public:
    UI_KIT(void) {
    }

    int settingMode = 0;

    bool _isTouched = false;

    void init(void);
    void showSettingImage(int status);

    void touchUpdate(void);
    void homeScreenGesture(void);
    void selectSettingMode(void);

    void publish(void);

    void topUI(void);
    void cameraUI(void);
    void ledUI(void);
    void buzzerUI(void);
    void loadcellUI(void);
    void tofUI(void);
    void floorUI(void);
    void runningUI(void);

   private:
    const uint16_t* settingImagePtr[8] = {
        ui_top, ui_camera, ui_led, ui_buzzer, ui_loadcell, ui_tof, ui_floor, ui_running};
};

#endif