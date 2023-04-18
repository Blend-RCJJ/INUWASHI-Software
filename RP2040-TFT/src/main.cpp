#include <Arduino.h>

#include <SPI.h>
#include <TFT_eSPI.h>

#define TFT_GREY 0x5AEB
TFT_eSPI tft = TFT_eSPI();

void setup(void) {
    tft.init();
    tft.setRotation(0);

    tft.fillScreen(TFT_GREY);
    tft.fillScreen(TFT_RED);
    tft.fillScreen(TFT_BLUE);
}

void loop() {
}

// #include <Arduino.h>
// #include <SPI.h>
// #include <Adafruit_SPIDevice.h>
// #include <Adafruit_GFX.h>
// #include <Adafruit_ILI9341.h>

// #include "./img/matsuken.h"
// #include "./img/shirosuke.h"
// #include "./img/shirokuma.h"
// #include "./img/samba.h"
// #include "./img/blend.h"

// #include <XPT2046_Touchscreen.h>

// #define ARR_SIZE 76800

// // SPI0の場合
// #define TFT_CS 17    // CS
// #define TFT_RST 22   // Reset
// #define TFT_DC 28    // D/C
// #define TFT_MOSI 19  // SDI(MOSI)
// #define TFT_MISO 16  // SDI(MOSI)
// #define TFT_SCK 18   // SCK

// #define TOUCH_CS 20

// XPT2046_Touchscreen ts(TOUCH_CS);

// Adafruit_ILI9341 tft = Adafruit_ILI9341(&SPI, TFT_DC, TFT_CS, TFT_RST);

// void showImage(const uint16_t *imagePtr) {
//     uint16_t *imageData;
//     imageData = new uint16_t[ARR_SIZE];

//     for (int i = 0; i < ARR_SIZE; i++) {
//         imageData[i] = imagePtr[i];
//     }

//     tft.drawRGBBitmap(0, 0, imageData, 320, 240);

//     delete[] imageData;
// }

// void setup() {
//     Serial.begin(115200);
//     tft.begin(10000000);
//     tft.setRotation(1);

//     ts.begin();
//     ts.setRotation(3);

//     delay(100);
// }

// void loop(void) {
//     boolean bTouch = ts.touched();
//     static bool _status = false;
//     if (bTouch == true) {
//         TS_Point tPoint = ts.getPoint();

//         Serial.print("x:");
//         Serial.print(tPoint.x);
//         Serial.print("\ty:");
//         Serial.println(tPoint.y);

//         showImage(image_data_matsuken);
//     } else {
//         showImage(image_data_samba);
//     }

//     if (_status != bTouch) {
//         if (bTouch == true) {
//             showImage(image_data_matsuken);
//         } else {
//             showImage(image_data_samba);
//         }

//         _status = bTouch;
//     }
// }