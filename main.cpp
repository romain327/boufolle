#include "Boufolle.hpp"

DigitalOut led(LED1);

int main()
{
    char spi_mode = 1; // D11, D12, D13
    PinName cs = D10;

    PinName nord = D4; // IO 6
    PinName sud = D5; // IO 12
    PinName est = D6; // IO 5
    PinName ouest = D7; // IO 11

    PinName green = D8;
    PinName red = D9;

    Boufolle boufolle{spi_mode, cs, nord, sud, est, ouest, green, red};

    while (true) {
        boufolle.processInterrupt();
        ThisThread::sleep_for(10ms);
    }
}