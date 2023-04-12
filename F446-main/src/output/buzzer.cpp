#include "buzzer.h"

void BUZZER::beat(int freq, double beat) {
    int interval = 2;
    if (freq == 0) {
        mute();
    } else {
        setFrequency(freq);
    }
    delay((60000.0 / bpm) * beat - interval);
    mute();
    delay(interval);
}