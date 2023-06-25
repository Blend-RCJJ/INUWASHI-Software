#include "buzzer.h"

#include "../../kit/RTOS-Kit.h"

extern RTOS_Kit app;

BUZZER::BUZZER(Output *pinPtr) {
    this->pinPtr = pinPtr;
}

void BUZZER::setFrequency(int freq) {
    if (isDisabled) return;

    analogWriteFrequency(freq);
    pinPtr->setPWM(60);
}

void BUZZER::mute(void) {
    pinPtr->setPWM(0);
}

void BUZZER::bootSound(void) {
    setFrequency(440);
    delay(100);
    setFrequency(880);
    delay(100);
    mute();
}

void BUZZER::beat(int freq, double beat) {
    int interval = 2;
    if (freq == 0) {
        mute();
    } else {
        setFrequency(freq);
    }

    unsigned long timer = millis() + (60000.0 / bpm) * beat - interval;
    while (millis() < timer) {
        app.delay(10);
    }
    mute();
    app.delay(interval);
}

void BUZZER::rescueKit(int kit) {
    bpm = 500;
    for (int j = 0; j < 2; j++) {
        for (int i = 0; i < kit; i++) {
            beat(FA, 1);
            beat(RA, 1);
            beat(DO_, 1);
        }
        beat(0, 2);
    }

    bpm = 200;
    if (kit == 0) {
        beat(MI_, 1);
        beat(SHI, 3);
    }
}

void BUZZER::sakura(void) {
    bpm = 200;
    beat(RA, 1);
    beat(RA, 1);
    beat(SHI, 0.5);
    beat(MI_, 0.5);
    beat(DO_, 0.5);
    beat(SHI, 0.5);

    beat(RA, 1);
    beat(RA, 1);
    beat(SHI, 0.5);
    beat(MI_, 0.5);
    beat(DO_, 0.5);
    beat(SHI, 0.5);

    beat(MI, 1);
    beat(FA, 1);
    beat(SHI, 0.5);
    beat(RA, 0.5);
    beat(FA, 1);

    beat(MI, 2);
}

void BUZZER::tokyoOndo(void) {
    bpm = 220;
    beat(RA, 0.5);
    beat(RA, 1);
    beat(SHI, 0.5);
    beat(DO_, 1);
    beat(SHI, 0.5);
    beat(MI_, 1);
    beat(MI_, 0.5);

    beat(DO_, 1.5);
    beat(SHI, 1);
    beat(DO_, 0.5);
    beat(RA, 1.5);
    beat(DO_, 1);
    beat(DO_, 0.5);

    beat(SHI, 1);
    beat(DO_, 0.5);
    beat(RA, 1);
    beat(FA, 0.5);
    beat(RA, 1);
    beat(SHI, 0.5);
    beat(FA, 1.5);

    beat(MI, 1.5);
    beat(SHI, 1.5);
    beat(SHI, 3);
}

void BUZZER::sambaII(void) {
    bpm = 140;
    beat(RAS, 0.5);
    beat(FA, 0.25);
    beat(RE, 0.25);
    beat(RA, 0.25);
    beat(FA, 0.25);
    beat(DO, 0.25);
    beat(SO, 0.25);
    beat(0, 0.25);
    beat(SO, 0.25);
    beat(0, 0.25);
    beat(SO, 0.25);
    beat(FA, 0.5);
    beat(FA, 0.5);
    beat(RAS, 0.5);
    beat(FA, 0.25);
    beat(RE, 0.25);
    beat(RA, 0.25);
    beat(FA, 0.25);
    beat(DO, 0.25);
    beat(SO, 0.25);
    beat(0, 0.25);
    beat(SO, 0.25);
    beat(0, 0.25);
    beat(SO, 0.25);
    beat(FA, 0.5);
    beat(FA, 0.5);
    beat(RAS, 0.5);
    beat(FA, 0.25);
    beat(RE, 0.25);
    beat(RA, 0.25);
    beat(FA, 0.25);
    beat(DO, 0.25);
    beat(SO, 0.25);
    beat(0, 0.25);
    beat(SO, 0.25);
    beat(0, 0.25);
    beat(SO, 0.25);
    beat(FA, 0.5);
    beat(FA, 0.5);
    beat(SO, 0.75);
    beat(RAS, 0.25);
    beat(RAS, 0.5);
    beat(RAS, 0.5);
    beat(0, 0.5);
}

void BUZZER::shoten(void) {
    bpm = 180;

    beat(RES, 1);
    beat(RES, 0.5);
    beat(RES, 1);
    beat(SOS, 0.5);
    beat(FA, 0.5);
    beat(RES, 0.5);

    beat(0, 1);
    beat(FA, 0.75);
    beat(0, 0.25);
    beat(FA, 0.75);
    beat(0, 0.25);
    beat(_FA, 1);

    beat(RES, 1);
    beat(RES, 0.5);
    beat(RES, 1);
    beat(SOS, 0.5);
    beat(FA, 0.5);
    beat(RES, 0.5);

    beat(0, 1);
    beat(FA, 0.75);
    beat(0, 0.25);
    beat(FA, 0.75);
    beat(0, 0.25);

    beat(DO_, 0.5);
    beat(RAS, 0.5);

    beat(SOS, 1);

    beat(0, 1);

    beat(SOS_, 0.5);
}

void BUZZER::yuyake(void) {
    bpm = 220;
    // 夕焼けこやけ
    beat(SO, 1);
    beat(MI, 1);
    beat(RE, 1);
    beat(DO, 1);

    beat(RE, 1);
    beat(RE, 1);
    beat(DO, 1);
    beat(RE, 1);

    beat(MI, 1);
    beat(SO, 1);
    beat(RA, 1);
    beat(SO, 1);

    beat(DO_, 2);
}

void BUZZER::shogun(void) {
    bpm = 160;
    beat(_SO, 1.5);
    beat(_SO, 0.5);
    beat(DO, 2);

    beat(SO, 0.5);
    beat(FA, 1);
    beat(RES, 0.5);
    beat(RE, 2);

    beat(DO, 1);
    beat(RES, 1);
    beat(RAS, 1.5);
    beat(DO_, 0.5);

    beat(SO, 3);
}

// this is the function that plays 暴れん坊将軍
void BUZZER::matsukenShogun(void) {
    bpm         = 170;
    int counter = 0;
SHOGUN_INTRO:
    beat(RES, 1.5);
    beat(RE, 1.5);
    beat(DO, 2);

    beat(RES, 0.5);
    beat(RE, 0.5);
    beat(DO, 0.5);
    beat(RES, 0.5);
    beat(RE, 0.5);
    beat(DO, 0.5);

    beat(SO, 1.5);
    beat(SO, 1.5);
    beat(SO, 3);
    beat(0, 1);

    beat(FA, 0.25);
    beat(MI, 0.25);
    beat(RE, 0.25);
    beat(0, 0.25);

SHOGUN_A:
    beat(_SO, 1.5);
    beat(_SO, 0.5);
    beat(DO, 2);

    beat(SO, 0.5);
    beat(FA, 1);
    beat(RES, 0.5);
    beat(RE, 2);

    beat(DO, 1);
    beat(RES, 1);
    beat(RAS, 1.5);
    beat(DO_, 0.5);

    beat(SO, 3);
    beat(0, 1);

    beat(_SO, 1.5);
    beat(_SO, 0.5);
    beat(DO, 2);

    beat(RES, 0.5);
    beat(RE, 1);
    beat(_RAS, 0.5);
    beat(DO, 2);

    beat(SO, 1);
    beat(FA, 0.5);
    beat(RES, 0.5);
    beat(RE, 1.5);
    beat(SO, 0.5);

    beat(DO, 3);
    beat(0, 1);

SHOGUN_B:
    beat(SOS, 0.5);
    beat(FA, 0.5);
    beat(0, 0.5);

    beat(SOS, 0.5);
    beat(FA, 0.5);
    beat(0, 0.5);

    beat(SOS, 0.5);
    beat(FA, 3.5);
    beat(0, 1);

    beat(SO, 0.5);
    beat(RES, 0.5);
    beat(0, 0.5);

    beat(SO, 0.5);
    beat(RES, 0.5);
    beat(0, 0.5);

    beat(SO, 0.5);
    beat(RES, 3.5);
    beat(0, 1);

    beat(FA, 0.5);
    beat(SOS, 0.5);
    beat(0, 0.5);
    beat(SOS, 2);
    beat(0, 0.5);

    beat(RES, 0.5);
    beat(SO, 0.5);
    beat(0, 0.5);
    beat(SO, 2);
    beat(0, 0.5);

    beat(RE, 1);
    beat(RE, 1.5);
    beat(RAS, 1);
    beat(SOS, 0.5);

    beat(SO, 3);
    beat(0, 1);

SHOGUN_C:

    beat(_SO, 1.5);
    beat(_SO, 0.5);
    beat(DO, 2);

    beat(SO, 0.5);
    beat(FA, 1);
    beat(RES, 0.5);
    beat(RE, 2);

    beat(DO, 1);
    beat(RES, 1);
    beat(RAS, 1.5);
    beat(DO_, 0.5);

    beat(SO, 3);
    beat(0, 1);

    beat(_SO, 1.5);
    beat(_SO, 0.5);
    beat(DO, 2);

    beat(RES, 0.5);
    beat(RE, 1);
    beat(_RAS, 0.5);
    beat(DO, 2);

    if (counter == 1) {
        bpm *= 0.8;
    }

    beat(SO, 1);
    beat(FA, 0.5);
    beat(RES, 0.5);

    if (counter == 1) {
        bpm *= 0.8;
    }

    beat(RE, 0.75);
    beat(_RAS, 0.75);
    beat(_SO, 0.5);

    if (counter == 1) {
        bpm = 50;
    }

    beat(DO, 3);
    beat(0, 1);

    if (counter == 1) {
        return;
    }

SHOGUN_2:

    beat(DO, 0.25);
    beat(RE, 0.25);
    beat(RES, 0.25);
    beat(FA, 0.25);
    beat(SO, 0.5);
    beat(0, 0.5);
    beat(DO, 0.25);
    beat(RE, 0.25);
    beat(RES, 0.25);
    beat(FA, 0.25);
    beat(SO, 0.5);
    beat(0, 0.5);

    beat(DO, 0.25);
    beat(RE, 0.25);
    beat(RES, 0.25);
    beat(FA, 0.25);
    beat(SO, 2);
    beat(0, 1);

    beat(SOS, 0.5);
    beat(SO, 0.5);
    beat(SOS, 0.5);
    beat(SO, 0.5);
    beat(SOS, 0.5);
    beat(FA, 0.5);
    beat(0, 0.5);
    beat(SO, 3.5);
    beat(0, 1);

    beat(DO, 0.25);
    beat(RE, 0.25);
    beat(RES, 0.25);
    beat(FA, 0.25);
    beat(SO, 0.5);
    beat(0, 0.5);
    beat(DO, 0.25);
    beat(RE, 0.25);
    beat(RES, 0.25);
    beat(FA, 0.25);
    beat(SO, 0.5);
    beat(0, 0.5);

    beat(DO, 0.25);
    beat(RE, 0.25);
    beat(RES, 0.25);
    beat(FA, 0.25);
    beat(SO, 2);
    beat(0, 1);

    beat(RE, 1);
    beat(RES, 1);
    beat(FA, 1);
    beat(FAS, 1);

    beat(SO, 0.5);
    beat(SOS, 0.5);
    beat(RA, 0.5);
    beat(RAS, 0.5);
    beat(SHI, 0.5);
    beat(DO_, 0.5);
    beat(DOS_, 0.5);
    beat(RE_, 0.5);

    beat(RES_, 1.5);
    beat(RE_, 1.5);
    beat(DO_, 2);

    beat(RES_, 0.5);
    beat(RE_, 0.5);
    beat(DO_, 0.5);
    beat(RES_, 0.5);
    beat(RE_, 0.5);
    beat(DO_, 0.5);

    beat(SO_, 1.5);
    beat(SO_, 1.5);
    beat(SO_, 3);
    beat(0, 1);
    beat(FA, 0.25);
    beat(MI, 0.25);
    beat(RE, 0.25);
    beat(0, 0.25);

    counter = 1;
    goto SHOGUN_A;
}

void BUZZER::matsukenSamba(void) {
    bpm = 127;
SAMBA_INTRO:
    beat(FA, 1);
    beat(0, 7);
    beat(FA, 1);
    beat(0, 7);
    beat(FA, 1);
    beat(0, 7);
    beat(FA, 1);
    beat(0, 7);
    beat(RAS, 0.5);
    beat(FA, 0.25);
    beat(RE, 0.25);
    beat(RA, 0.25);
    beat(FA, 0.25);
    beat(DO, 0.25);
    beat(SO, 0.25);
    beat(0, 0.25);
    beat(SO, 0.25);
    beat(0, 0.25);
    beat(SO, 0.25);
    beat(FA, 0.5);
    beat(FA, 0.5);
    beat(RAS, 0.5);
    beat(FA, 0.25);
    beat(RE, 0.25);
    beat(RA, 0.25);
    beat(FA, 0.25);
    beat(DO, 0.25);
    beat(SO, 0.25);
    beat(0, 0.25);
    beat(SO, 0.25);
    beat(0, 0.25);
    beat(SO, 0.25);
    beat(FA, 0.5);
    beat(FA, 0.5);
    beat(RAS, 0.5);
    beat(FA, 0.25);
    beat(RE, 0.25);
    beat(RA, 0.25);
    beat(FA, 0.25);
    beat(DO, 0.25);
    beat(SO, 0.25);
    beat(0, 0.25);
    beat(SO, 0.25);
    beat(0, 0.25);
    beat(SO, 0.25);
    beat(FA, 0.5);
    beat(FA, 0.5);
    beat(SO, 0.75);
    beat(RAS, 0.25);
    beat(RAS, 0.5);
    beat(RAS, 0.5);
    beat(0, 0.5);
SAMBA_A:
    beat(_RAS, 0.5);
    beat(DO, 0.5);
    beat(RE, 0.5);
    beat(RE, 1.5);
    beat(DO, 0.5);
    beat(0, 0.5);
    beat(_RA, 0.5);
    beat(_RAS, 0.5);
    beat(DO, 0.5);
    beat(DO, 1.5);
    beat(_RAS, 0.5);
    beat(0, 0.5);
    beat(_SO, 0.5);
    beat(_RA, 0.5);
    beat(_RAS, 0.5);
    beat(_RAS, 0.5);
    beat(_RAS, 0.5);
    beat(_RAS, 0.5);
    beat(_DO, 0.5);
    beat(_DO, 0.5);
    beat(_RAS, 0.5);
    beat(_RA, 0.5);
    beat(_SO, 0.5);
    beat(_FA, 1);
    beat(0, 1.5);
    beat(_RAS, 0.5);
    beat(DO, 0.5);
    beat(RE, 0.5);
    beat(RE, 0.75);
    beat(RE, 0.25);
    beat(RE, 0.5);
    beat(DO, 0.5);
    beat(DO, 0.5);
    beat(_RA, 0.5);
    beat(_RAS, 0.5);
    beat(DO, 0.5);
    beat(DO, 0.75);
    beat(DO, 0.25);
    beat(DO, 0.5);
    beat(_RAS, 0.5);
    beat(0, 0.5);
    beat(_SO, 0.5);
    beat(_RA, 0.5);
    beat(_RAS, 0.5);
    beat(_RAS, 0.25);
    beat(0, 0.25);
    beat(_DO, 0.25);
    beat(_DO, 0.25);
    beat(_DO, 0.5);
    beat(_RAS, 0.5);
    beat(_RAS, 0.5);
    beat(_RA, 0.5);
    beat(_SO, 0.5);
    beat(_RA, 0.5);
    beat(_RAS, 0.5);
    beat(FA, 0.25);
    beat(RE, 0.25);
    beat(RA, 0.25);
    beat(FA, 0.25);
    beat(DO, 0.25);
    beat(SO, 0.25);
    beat(0, 0.25);
    beat(SO, 0.25);
    beat(0, 0.25);
    beat(SO, 0.25);
    beat(FA, 0.5);
    beat(FA, 0.5);
    beat(SO, 0.75);
    beat(RAS, 0.25);
    beat(RAS, 0.5);
    beat(RAS, 0.5);
    beat(0, 0.5);  // 光る汗がはじけ飛ぶ
SAMBA_B:
    beat(_FA, 0.5);
    beat(_SO, 0.5);
    beat(_FA, 0.5);
    beat(_SO, 0.75);
    beat(_SO, 0.25);
    beat(_SO, 0.5);
    beat(_RAS, 0.5);
    beat(0, 0.5);
    beat(_SO, 0.5);
    beat(_FA, 0.5);
    beat(_SO, 0.5);
    beat(_RE, 0.75);
    beat(_RE, 0.25);
    beat(_RE, 0.5);
    beat(_DO, 0.5);
    beat(0, 0.5);
    beat(_DO, 0.5);
    beat(_RE, 0.5);
    beat(_REF, 0.5);
    beat(_FA, 0.5);
    beat(_FA, 0.5);
    beat(_FA, 0.25);
    beat(_SO, 0.25);
    beat(0, 0.25);
    beat(_RA, 0.25);
    beat(_RA, 0.5);
    beat(_SO, 0.5);
    beat(_DO, 0.25);
    beat(0, 0.25);
    beat(_SO, 0.25);
    beat(_FA, 0.25);
    beat(_FA, 0.5);  // 熱い風に体預け、心ゆくまで踊れば
    beat(0, 2);
    beat(_FA, 0.5);
    beat(_FA, 0.5);
    beat(_REF, 0.5);
    beat(_DO, 0.5);
    beat(_RE, 0.5);
    beat(_RE, 0.5);
    beat(_RA, 0.5);
    beat(0, 0.5);
    beat(_RA, 0.5);
    beat(_SO, 0.5);
    beat(_RA, 0.5);
    beat(_RAS, 0.5);
    beat(DO, 0.5);
    beat(_RAS, 0.5);
    beat(_SO, 0.5);
    beat(0, 0.5);
    beat(_SO, 0.5);
    beat(_RA, 0.5);
    beat(_RAS, 0.5);
    beat(RE, 0.5);
    beat(RE, 0.25);
    beat(RE, 0.25);
    beat(RE, 0.5);
    beat(RE, 0.5);
    beat(RE, 0.5);
    beat(DO, 0.5);
    beat(_RAS, 0.25);
    beat(_SO, 0.5);
    beat(DO, 0.25);
    beat(DO, 4);
    beat(FA, 0.25);
    beat(0, 0.5);
    beat(FA, 0.25);
    beat(0, 0.5);
    beat(FA, 0.5);
    beat(FA, 1);  // 胸にあふれるこのリズム
SAMBA_SABI:
    beat(FA, 1);
    beat(_SO, 3);
    beat(_RAS, 1);
    beat(RE, 4);
    beat(0, 2);
    beat(DO, 0.5);
    beat(DO, 0.5);
    beat(DO, 0.5);
    beat(RE, 0.5);
    beat(DO, 0.75);
    beat(_FA, 0.25);
    beat(_FA, 0.5);
    beat(_RAS, 0.5);
    beat(_RAS, 1);
    beat(_RA, 1);
    beat(_SO, 3);
    beat(_RAS, 1);
    beat(RE, 4);
    beat(0, 2);
    beat(FA, 0.5);
    beat(FA, 0.5);
    beat(FA, 0.5);
    beat(FA, 0.5);
    beat(FA, 0.75);
    beat(RE, 0.25);
    beat(RE, 0.5);
    beat(SO, 1);
    beat(SO, 2);
    beat(0, 2.5);
    beat(_SO, 1);
    beat(_FA, 0.5);
    beat(_REF, 0.5);
    beat(_REF, 0.25);
    beat(_REF, 0.25);
    beat(0, 0.5);
    beat(_SO, 0.5);
    beat(_RAS, 0.75);
    beat(_RA, 0.25);
    beat(0, 0.5);
    beat(_SO, 0.5);
    beat(_FA, 0.5);
    beat(_FA, 0.5);
    beat(_FA, 0.5);
    beat(_RA, 0.5);
    beat(DO, 0.75);
    beat(_RAS, 0.25);
    beat(0, 0.5);
    beat(_RA, 0.5);
    beat(_SO, 0.5);
    beat(_DO, 0.25);
    beat(_REF, 0.25);
    beat(_REF, 0.5);
    beat(_RAS, 0.5);
    beat(_RA, 0.5);
    beat(_SO, 0.25);
    beat(_FA, 0.25);
    beat(_FA, 0.5);
    beat(DO, 0.5);
    beat(0, 0.5);
    beat(_RAS, 0.5);
    beat(_RAS, 0.5);
    beat(_RAS, 0.5);
    beat(DO, 0.75);
    beat(RE, 0.25);
    beat(RE, 0.5);
    beat(RES, 0.5);
    beat(RES, 2);
    beat(0, 0.25);
    beat(_REF, 0.25);
    beat(_FA, 0.25);
    beat(_FAS, 0.25);
    beat(_SOS, 0.25);
    beat(_RAS, 0.25);
    beat(DO, 0.25);
    beat(_DOS, 0.25);
    beat(RE, 1.5);
    beat(_FA, 0.5);
    beat(0, 0.5);
    beat(FA, 1);
    beat(RES, 0.5);
    beat(RE, 1.5);
    beat(_FA, 0.5);
    beat(_FA, 1);
    beat(0, 1);
    beat(RE, 1);
    beat(RE, 1);
    beat(RE, 1);
    beat(RE, 1);
    beat(DO, 1.5);
    beat(_RAS, 0.5);
    beat(_RAS, 1);
    beat(_RAS, 1);
    beat(_RAS, 4);
    beat(RAS, 0.25);
    beat(0, 0.5);
    beat(RAS, 0.25);
    beat(0, 0.5);
    beat(RAS, 0.5);
    beat(RAS, 1.5);
    beat(FA, 0.5);
    beat(RAS, 0.5);
}