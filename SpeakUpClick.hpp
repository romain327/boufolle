#ifndef SPEAKUPCLICK_HPP
#define SPEAKUPCLICK_HPP

#include "mbed.h"

class SpeakUpClick {
    private:
        InterruptIn *NORD;
        InterruptIn *SUD;
        InterruptIn *EST;
        InterruptIn *OUEST;

    public:
        SpeakUpClick(PinName nord, PinName sud, PinName est, PinName ouest)
            : NORD(new InterruptIn(nord)), SUD(new InterruptIn(sud)), EST(new InterruptIn(est)), OUEST(new InterruptIn(ouest)) {
            if (!NORD || !SUD || !EST || !OUEST) {
                printf("Erreur lors de l'initialisation des pins d'interruptions\n");
                resetCard();
            }
        }

        ~SpeakUpClick() {
            delete NORD;
            delete SUD;
            delete EST;
            delete OUEST;
        }

        InterruptIn *getNord() { return NORD; }
        InterruptIn *getSud() { return SUD; }
        InterruptIn *getEst() { return EST; }
        InterruptIn *getOuest() { return OUEST; }

        void resetCard() {
            printf("Reset\n");
            NVIC_SystemReset();
        }
};

#endif //SPEAKUPCLICK_HPP
