#ifndef _IOKIT_H_
#define _IOKIT_H_

#include "Arduino.h"

#define PULLUP 1
#define OPEN 0

class Output {
   public:
    Output(int pin);

    float operator=(float val);
    int operator<<=(int val);

    byte raw(void);

    operator float();

    void setPWM(int val);

   private:
    int _pinNumber;
    byte _pinStatus;

    void set(bool val);

#ifdef _STM32_DEF_
    bool _pwmExp = false;
#endif
};

class Input {
   public:
    Input(int pin);
    Input(int pin, bool pullup);

    bool digital(void);
    float analog(void);
    int raw(void);

    operator bool();

   private:
    int _pinNumber;
    byte _pinStatus;
};

#endif