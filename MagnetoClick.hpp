#ifndef MAGNETOCLICK_HPP
#define MAGNETOCLICK_HPP

#include "mbed.h"

class MagnetoClick {
    private:
        SPI *spi;
        DigitalOut cs;
        
    public:
        MagnetoClick(PinName cs) : spi(nullptr), cs(cs) {}

        virtual ~MagnetoClick() {
            delete spi;
        }

        void init(SPI *spi) {
            this->spi = spi;
            this->spi->format(16, 1);
            this->spi->frequency(1000000);
        }

        float getAngle();
};

#endif //MAGNETOCLICK_HPP