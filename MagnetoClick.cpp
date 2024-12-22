#include "MagnetoClick.hpp"
#include <cstdio> // Inclure pour sprintf

float MagnetoClick::getAngle() {
    float angle{};

    if (!spi) {
        printf("Erreur lors de l'initialisation SPI\n");
        return -1;
    }

    cs = 1;
    ThisThread::sleep_for(10ms);
    cs = 0;
    ThisThread::sleep_for(10ms);

    short rawValue = spi->write(0xFFFF);

    if ((rawValue & 0x3FFF) == 0x3FFF) {
        printf("Valeur lue non valide\n");
        return -1;
    }

    angle = static_cast<float>((rawValue & 0x3FFF) * 36000 / 0x4000) / 100.0f;

    if (angle < 0 || angle > 360) {
        printf("Angle hors plage\n");
        return -1;
    }

    printf("Angle = %.2f\n", angle);

    cs = 1;
    ThisThread::sleep_for(10ms);

    if (angle < 0 || angle > 360) {
        return -1;
    }

    return angle;
}
