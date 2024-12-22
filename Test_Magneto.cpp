#include "mbed.h"
 
SPI spi(D11, D12, D13); // mosi, miso, sclk
DigitalOut cs(D10);
 
int main() {

    float angle = 0;

    spi.format(16, 1);
    spi.frequency(1000000);

    while(1)
    {
        cs = 1;
        ThisThread::sleep_for(1ms);
    
        cs = 0;
        ThisThread::sleep_for(1ms);
    
        angle = ((spi.write(0xFFFF) & 0x3FFF) * 36000 / 0x4000)/100;
    
        printf("angle = %F\n", angle);
        

        // Deselect the device
        cs = 1;
        ThisThread::sleep_for(1ms);

        ThisThread::sleep_for(1s);
    }
}