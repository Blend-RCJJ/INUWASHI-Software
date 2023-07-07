#include "gyro.h"

GYRO::GYRO(Adafruit_BNO055 *p) {
    sensorPtr = p;
}

void GYRO::init(void) {
    sensorPtr->begin(OPERATION_MODE_IMUPLUS);

    int eeAddress = 0;
    long bnoID;
    bool foundCalib = false;

    EEPROM.get(eeAddress, bnoID);

    adafruit_bno055_offsets_t calibrationData;
    sensor_t sensor;

    sensorPtr->getSensor(&sensor);

    // if (bnoID == sensor.sensor_id) {
    //     eeAddress += sizeof(long);
    //     EEPROM.get(eeAddress, calibrationData);
    //     sensorPtr->setSensorOffsets(calibrationData);
    //     foundCalib = true;
    // }

    uint8_t system_status, self_test_results, system_error;
    system_status = self_test_results = system_error = 0;
    sensorPtr->getSystemStatus(&system_status, &self_test_results,
                               &system_error);

    sensorPtr->setExtCrystalUse(true);
}

int GYRO::read(void) {
    sensors_event_t event;
    sensorPtr->getEvent(&event);

    if (isGyroDisabled) {  // 地磁気
        magnetic = event.magnetic.x;
        deg      = (int)(magnetic - offset + 360) % 360;
    } else {
        deg = (int)(event.orientation.x - offset + 360) % 360;
    }

    slope = (int)(event.orientation.y - slopeOffset + 360) % 360;

    if (slope >= 180) {
        slope -= 360;
    }
    slope *= -1;

    if (abs(slope) <= 8) {
        slope = 0;
    }
    direction();

    return deg;
}

void GYRO::setOffset(void) {
    sensors_event_t event;
    sensorPtr->getEvent(&event);
    offset = event.magnetic.x;

    if (isGyroDisabled) {  // 地磁気
        offset = event.magnetic.x;
    } else {
        offset = event.orientation.x;
    }

    slopeOffset = event.orientation.y;
}

void GYRO::direction(void) {
    if (deg >= 350 || deg < 10) {
        North = true;
    } else {
        North = false;
    }

    if (deg >= 80 && deg < 100) {
        East = true;
    } else {
        East = false;
    }

    if (deg >= 170 && deg < 190) {
        South = true;
    } else {
        South = false;
    }

    if (deg >= 260 && deg < 280) {
        West = true;
    } else {
        West = false;
    }
}