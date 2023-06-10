// #include <dummy_rp2040.h>
#include <Arduino.h>
#include <Wire.h>
#include <VL53L0X.h>

#include <Adafruit_NeoPixel.h>

#define NUMPIXELS 1
#define NEO_PWR 11
#define NEOPIX 12
#define numOfSensors 2

Adafruit_NeoPixel pixels(NUMPIXELS, NEOPIX, NEO_GRB + NEO_KHZ800);
VL53L0X distanceSensor[numOfSensors];

const int xshutPin[2] = {A0, D10};  // Left Right
const int offset[2] = {0, 13};
const char firstAddr = 0x30;
bool isSensorActive = false;

bool isSilver = false;
const int silverThreshold = 8;

void distanceSensorInit(void) {
    pinMode(xshutPin[0], OUTPUT);
    pinMode(xshutPin[1], OUTPUT);
    digitalWrite(xshutPin[0], LOW);
    digitalWrite(xshutPin[1], LOW);

    for (int i = 0; i < numOfSensors; i++) {
        digitalWrite(xshutPin[i], HIGH);  // VL53L0Xの電源をON
        distanceSensor[i].setTimeout(100);

        if (!distanceSensor[i].init()) {  // ERROR
            Serial.println("ERR1: Failed to detect and initialize sensor!");

            pixels.setBrightness(255);
            while (1) {
                pixels.setPixelColor(0, 255, 0, 0);
                pixels.show();
                delay(100);

                pixels.setPixelColor(0, 0, 0, 0);
                pixels.show();
                delay(100);
            }
        }

        distanceSensor[i].setAddress(firstAddr + i);  // 順にアドレスを割り当て

        // 測定距離を広げる
        distanceSensor[i].setSignalRateLimit(0.1);
        distanceSensor[i].setVcselPulsePeriod(VL53L0X::VcselPeriodPreRange, 18);
        distanceSensor[i].setVcselPulsePeriod(VL53L0X::VcselPeriodFinalRange,
                                              14);

        distanceSensor[i].startContinuous();  // 計測開始
    }

    isSensorActive = true;
}

void setup() {
    Serial.begin(9600);

    Wire.begin();  // I2C通信を開通
    Wire.setClock(1000000);

    pixels.begin();
    pinMode(NEO_PWR, OUTPUT);
    digitalWrite(NEO_PWR, HIGH);

    distanceSensorInit();
}

void loop() {
    int rawData[2] = {0};
    for (int i = 0; i < numOfSensors; i++) {
        rawData[i] =
            distanceSensor[i].readRangeContinuousMillimeters() - offset[i];
    }

    delay(10);

    static uint16_t silverTimer = 0;

    if (rawData[0] < silverThreshold || rawData[1] < silverThreshold) {
        isSilver = true;
        silverTimer = millis();
    } else if (millis() - silverTimer > 100) {
        isSilver = false;
    }

    // print rawData
    Serial.print("rawData: ");
    Serial.print(rawData[0]);
    Serial.print("\t");
    Serial.print(rawData[1]);
    Serial.print("\t");
    Serial.print("isSilver: ");
    Serial.println(isSilver);
}

void setup1(void) {
    const int userLED[3] = {16, 17, 25};
    for (int i = 0; i < 3; i++) {
        pinMode(userLED[i], OUTPUT);
        digitalWrite(userLED[i], HIGH);
    }

    digitalWrite(userLED[2], LOW);
}

void loop1(void) {
    if (isSensorActive && !isSilver) {
        if ((millis() / 25) % 2 == 0 && (millis() / 300) % 10 == 0) {
            pixels.setPixelColor(0, 0, 80, 255);
            pixels.setBrightness(150);
            pixels.show();
        } else {
            pixels.setBrightness(0);
            pixels.show();
        }
    } else if (isSilver) {
        pixels.setPixelColor(0, 255, 255, 0);
        pixels.setBrightness(150);
        pixels.show();
    }
}