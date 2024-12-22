#include "mbed.h"

InterruptIn nord(D2);
DigitalOut led(D8);

void blink() {
        led = !led;
}

int main()
{
    led = 0;
    nord.fall(&blink);
    while (true) {

    }
}