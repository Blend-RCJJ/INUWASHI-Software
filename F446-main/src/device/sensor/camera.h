/** camera.h
 * カメラの入力監視を行います。一つのカメラに一つのインスタンスって感じ。ちょっと修正したい。
 */

#ifndef _CAMERA_H_
#define _CAMERA_H_

#include <Arduino.h>

#define VICTIM_H 'H'
#define VICTIM_U 'U'
#define VICTIM_S 'S'
#define VICTIM_RED 'R'
#define VICTIM_GREEN 'G'
#define VICTIM_YELLOW 'Y'
#define NO_VICTIM 'N'

class CAMERA {
   public:
    HardwareSerial *serialPtr;
    CAMERA(HardwareSerial *ptr);

    bool isVictimDetected = true;
    int data = 'N';

    void read(void);

   private:
};

#endif