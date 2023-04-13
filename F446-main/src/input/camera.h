/** camera.h
 * カメラの入力監視を行います。一つのカメラに一つのインスタンスって感じ。ちょっと修正したい。
 */

#ifndef _CAMERA_H
#define _CAMERA_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#define VICTIM_H 'H'
#define VICTIM_U 'U'
#define VICTIM_S 'S'
#define VICTIM_RED 'R'
#define VICTIM_GREEN 'G'
#define VICTIM_YELLOW 'B'
#define NO_VICTIM 'N'

class CAMERA_INDEPENDENT {
   public:
    HardwareSerial *serialPtr;
    CAMERA_INDEPENDENT(HardwareSerial *ptr);

    bool isVictimDetected = true;
    int victimType = 0;
    int data = 'N';

    void read(void);

   private:
};

class CAMERA {
   public:
    HardwareSerial *leftPtr;
    HardwareSerial *rightPtr;

    bool isVictimDetected = false;

    CAMERA(HardwareSerial *_leftPtr, HardwareSerial *_rightPtr);

    CAMERA_INDEPENDENT right = CAMERA_INDEPENDENT(leftPtr);
    CAMERA_INDEPENDENT left = CAMERA_INDEPENDENT(rightPtr);

    void read(void);

   private:
};

#endif