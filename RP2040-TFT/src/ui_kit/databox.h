#ifndef _DATA_BOX_H_
#define _DATA_BOX_H_

class DATA_BOX {
   public:
    int gyro = 0;
    bool gyroReset = false;

    void update(void) {
        gyro += 1;
        gyro %= 360;

        if(gyroReset) {
            gyro = 0;
            gyroReset = false;
        }
    }
};

#endif