#ifndef BOUFOLLE_HPP
#define BOUFOLLE_HPP

#include "SpeakUpClick.hpp"
#include "MagnetoClick.hpp"

class Boufolle {
    private:
        SPI *spi;
        MagnetoClick magnetoClick;
        SpeakUpClick speakupClick;
        DigitalOut GREEN;
        DigitalOut RED;

        static Boufolle* instance;
        volatile char interruptFlag{0};

    public:
        Boufolle(char spi_mode, PinName cs, PinName nord, PinName sud, PinName est, PinName ouest, PinName green, PinName red)
            : spi(nullptr), magnetoClick(cs), speakupClick(nord, sud, est, ouest), GREEN(green), RED(red) {
            switch (spi_mode) {
                case 1:
                    spi = new SPI(PA_7, PA_6, PA_5);
                    break;
                case 2:
                    spi = new SPI(PB_15, PB_14, PB_13);
                    break;
                case 3::
                    spi = new SPI(PB_5, PB_4, PB_3);
                    break;
                default 1:
                    spi = new SPI(PA_7, PA_6, PA_5);
                    break;
            }
            magnetoClick.init(spi);

            instance = this;

            printf("init\n");

            speakupClick.getNord()->fall(&Boufolle::nordAction);
            speakupClick.getSud()->fall(&Boufolle::sudAction);
            speakupClick.getEst()->fall(&Boufolle::estAction);
            speakupClick.getOuest()->fall(&Boufolle::ouestAction);
        }

        ~Boufolle() {
            delete spi;
        }

        MagnetoClick& getMagnetolick() { return magnetoClick; }

        SpeakUpClick& getSpeakUpClick() { return speakupClick; }

    private:
        [[nodiscard]] bool compareAngle(const char askedDirection) {
            float angle = magnetoClick.getAngle();
            if ((angle < 0 || angle > 360)) {
                printf("Angle hors plage\n");
                resetCard();
                return false;
            }

            if (angle == -1) {
                printf("Erreur lors de l'acquisition de l'angle\n");
                resetCard();
            }

            switch (askedDirection) {
                case 1:
                    return angle > 316 || angle < 45;
                case 2:
                    return angle > 46 && angle < 135;
                case 3:
                    return angle > 136 && angle < 225;
                case 4:
                    return angle > 226 && angle < 315;
                default:
                    return false;
            }
        }

        void angleCorrect() {
            GREEN = 1;
            ThisThread::sleep_for(2s);
            GREEN = 0;
        }

        void angleWrong() {
            RED = 1;
            ThisThread::sleep_for(2s);
            RED = 0;
        }

        static void nordAction(void) {
            if (instance)
                instance->interruptFlag = 1;
            else
                resetCard();
        }

        static void sudAction(void) {
            if (instance) {
                instance->interruptFlag = 3;
            }
            else
                resetCard();
        }

        static void estAction(void) {
            if (instance)
                instance->interruptFlag = 2;
            else
                resetCard();
        }

        static void ouestAction(void) {
            if (instance)
                instance->interruptFlag = 4;
            else
                resetCard();
        }

    public:
        void processInterrupt() {
            switch(interruptFlag) {
                case 1:
                    printf("nord\n");
                    if (instance->compareAngle(1))
                        instance->angleCorrect();
                    else
                        instance->angleWrong();
                    break;
                case 2:
                    printf("est\n");
                    if (instance->compareAngle(2))
                        instance->angleCorrect();
                    else
                        instance->angleWrong();
                    break;
                case 3:
                    printf("sud\n");
                    if (instance->compareAngle(3))
                        instance->angleCorrect();
                    else
                        instance->angleWrong();
                    break;
                case 4:
                    printf("ouest\n");
                    if (instance->compareAngle(4))
                        instance->angleCorrect();
                    else
                        instance->angleWrong();
                    break;
                default:
                    break;
            }
            interruptFlag = 0;
        }

        static void resetCard() {
            printf("Reset\n");
            NVIC_SystemReset();
        }
};

#endif // BOUFOLLE_HPP
