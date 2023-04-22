#include <Arduino.h>
#include <TFT_eSPI.h>
#include <XPT2046_Touchscreen.h>

TFT_eSPI tft = TFT_eSPI();
XPT2046_Touchscreen ts(20);

#include "img/blend.h"
#include "img/shirosuke.h"
#include "img/shirokuma.h"

#define ARR_SIZE 76800

void showImage(const uint16_t *imagePtr) {
    uint16_t *imageData;
    imageData = new uint16_t[ARR_SIZE];

    for (int i = 0; i < ARR_SIZE; i++) {
        imageData[i] = imagePtr[i];
    }

    tft.pushImage(0, 0, 320, 240, imageData);

    delete[] imageData;
}

void showBootImage(void) {
    tft.fillScreen(TFT_BLACK);

    showImage(image_data_blend);
    delay(500);
    showImage(image_data_shirokuma);
    delay(500);
    showImage(image_data_shirosuke);
    delay(500);
}

void setup() {
    Serial.begin(115200);
    tft.begin();
    tft.setRotation(1);
    tft.setSwapBytes(true);

    ts.begin();
    ts.setRotation(3);

    showBootImage();
}

void loop() {
    bool bTouch = ts.touched();
    TS_Point p = ts.getPoint();

    delay(10);

    if (bTouch) {
        Serial.print("x:");
        Serial.print(p.x);
        Serial.print("\ty:");
        Serial.println(p.y);

        SPI.beginTransaction(
            SPISettings(SPI_FREQUENCY, MSBFIRST, TFT_SPI_MODE));
        SPI.endTransaction();

        showImage(image_data_shirokuma);

        tft.setCursor(0, 0);
        tft.setTextColor(TFT_RED);
        tft.setTextSize(8);ｆｆ
        tft.print(p.x);
        tft.setCursor(0, 15 * 4);
        tft.print(p.y);
    } else {
        Serial.println("No YUBI!!!!!");
        SPI.beginTransaction(
            SPISettings(SPI_FREQUENCY, MSBFIRST, TFT_SPI_MODE));
        SPI.endTransaction();

        showImage(image_data_blend);
    }
}

// /*
//   The TFT_eSPI library incorporates an Adafruit_GFX compatible
//   button handling class, this sketch is based on the Arduin-o-phone
//   example.

//   This example diplays a keypad where numbers can be entered and
//   send to the Serial Monitor window.

//   The sketch has been tested on the ESP8266 (which supports SPIFFS)

//   The minimum screen size is 320 x 240 as that is the keypad size.
// */

// // The SPIFFS (FLASH filing system) is used to hold touch screen
// // calibration data

// // #include "FS.h"

// #include <SPI.h>
// #include <TFT_eSPI.h>  // Hardware-specific library

// TFT_eSPI tft = TFT_eSPI();  // Invoke custom library

// // This is the file name used to store the calibration data
// // You can change this to create new calibration files.
// // The SPIFFS file name must start with "/".
// #define CALIBRATION_FILE "/TouchCalData2"

// // Set REPEAT_CAL to true instead of false to run calibration
// // again, otherwise it will only be done once.
// // Repeat calibration if you change the screen rotation.
// #define REPEAT_CAL false

// // Keypad start position, key sizes and spacing
// #define KEY_X 40  // Centre of key
// #define KEY_Y 96
// #define KEY_W 62  // Width and height
// #define KEY_H 30
// #define KEY_SPACING_X 18  // X and Y gap
// #define KEY_SPACING_Y 20
// #define KEY_TEXTSIZE 1  // Font size multiplier

// // Using two fonts since numbers are nice when bold
// #define LABEL1_FONT &FreeSansOblique12pt7b  // Key label font 1
// #define LABEL2_FONT &FreeSansBold12pt7b     // Key label font 2

// // Numeric display box size and location
// #define DISP_X 1
// #define DISP_Y 10
// #define DISP_W 238
// #define DISP_H 50
// #define DISP_TSIZE 3
// #define DISP_TCOLOR TFT_CYAN

// // Number length, buffer for storing it and character index
// #define NUM_LEN 12
// char numberBuffer[NUM_LEN + 1] = "";
// uint8_t numberIndex = 0;

// // We have a status line for messages
// #define STATUS_X 120  // Centred on this
// #define STATUS_Y 65

// // Create 15 keys for the keypad
// char keyLabel[15][5] = {"New", "Del", "Send", "1", "2", "3", "4", "5",
//                         "6",   "7",   "8",    "9", ".", "0", "#"};
// uint16_t keyColor[15] = {TFT_RED,  TFT_DARKGREY, TFT_DARKGREEN, TFT_BLUE,
//                          TFT_BLUE, TFT_BLUE,     TFT_BLUE,      TFT_BLUE,
//                          TFT_BLUE, TFT_BLUE,     TFT_BLUE,      TFT_BLUE,
//                          TFT_BLUE, TFT_BLUE,     TFT_BLUE};

// // Invoke the TFT_eSPI button class and create all the button objects
// TFT_eSPI_Button key[15];

// void touch_calibrate() {
//     uint16_t calData[5];
//     uint8_t calDataOK = 1;

//     if (calDataOK && !REPEAT_CAL) {
//         // calibration data valid
//         tft.setTouch(calData);
//     } else {
//         // data not valid so recalibrate
//         tft.fillScreen(TFT_BLACK);
//         tft.setCursor(20, 0);
//         tft.setTextFont(2);
//         tft.setTextSize(1);
//         tft.setTextColor(TFT_WHITE, TFT_BLACK);

//         tft.println("Touch corners as indicated");

//         tft.setTextFont(1);
//         tft.println();

//         if (REPEAT_CAL) {
//             tft.setTextColor(TFT_RED, TFT_BLACK);
//             tft.println("Set REPEAT_CAL to false to stop this running
//             again!");
//         }

//         tft.calibrateTouch(calData, TFT_MAGENTA, TFT_BLACK, 15);

//         tft.setTextColor(TFT_GREEN, TFT_BLACK);
//         tft.println("Calibration complete!");
//     }
// }
// //------------------------------------------------------------------------------------------

// void setup() {
//     // Use serial port
//     Serial.begin(9600);

//     // Initialise the TFT screen
//     tft.init();

//     // Set the rotation before we calibrate
//     tft.setRotation(1);

//     // Calibrate the touch screen and retrieve the scaling factors
//     //   touch_calibrate();

//     // Clear the screen
//     tft.fillScreen(TFT_BLACK);

//     // Draw keypad background
//     tft.fillRect(0, 0, 240, 320, TFT_DARKGREY);

//     // Draw number display area and frame
//     tft.fillRect(DISP_X, DISP_Y, DISP_W, DISP_H, TFT_BLACK);
//     tft.drawRect(DISP_X, DISP_Y, DISP_W, DISP_H, TFT_WHITE);

//     // Draw keypad
//     //   drawKeypad();
//     touch_calibrate();

//     pinMode(LED_BUILTIN, OUTPUT);
// }

// void loop(void) {
//     uint16_t t_x = 0, t_y = 0;
//     bool pressed = tft.getTouch(&t_x, &t_y);

//     digitalWrite(LED_BUILTIN, pressed);
// }
