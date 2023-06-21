// #include "./ui-kit.h"

// void UI_KIT::init(void) {
//     touch.begin();
//     display.init();
//     display.publish();

//     display.setBackgroundImage(image_data_blend);
//     display.publish();
//     delay(500);
// }

// void UI_KIT::showSettingImage(int status) {
//     display.setBackgroundImage(settingImagePtr[status]);
//     display.publish();
// }

// void UI_KIT::touchUpdate(void) {
//     touch.read();
//     homeScreenGesture();
// }

// void UI_KIT::homeScreenGesture(void) {
//     // static bool _isTouched = false;
//     // static bool flag = false;

//     // static int yWhenFlagged = 0;
//     // static unsigned long timeWhenFlagged = 0;

//     // if (touch.isTouched && _isTouched) {
//     //     if (touch.point.y > 300) {
//     //         yWhenFlagged = touch.point.y;
//     //         timeWhenFlagged = millis();
//     //         flag = 0;
//     //     }

//     // } else if (!touch.isTouched) {
//     //     flag = false;
//     // }

//     // if (millis() > timeWhenFlagged + 100 && flag) {
//     //     if (touch.point.y < yWhenFlagged - 200) {
//     //         goToHome = true;
//     //     }
//     // }

//     // _isTouched = touch.isTouched;
// }