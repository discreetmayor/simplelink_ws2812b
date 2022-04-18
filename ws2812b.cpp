#include <ws2812b.h>

WS2812B::WS2812B(uint_least8_t spiIndex, uint16_t ledCount) : RGBLED(spiIndex, ledCount, SPI_POL0_PHA1) {
    outputBuffer = new uint8_t[ledCount*9 + 480]();
    transaction.txBuf = (void *) outputBuffer;
    transaction.count = ledCount*9 + 480;
}

WS2812B::~WS2812B() {
    delete[] outputBuffer;
}

void WS2812B::convertOutputBuffer() {
    memset(outputBuffer, 0, ledCount*9 + 480);
    for(uint16_t ledIndex = 0; ledIndex < ledCount; ledIndex++) {
        EightBitLed led = getEightBitLed(ledIndex, true);
        uint16_t ledOffset = ledIndex*9 + 240;
        uint8_t  shiftIndex = 3;
        uint32_t color = led.color.green<<16 | led.color.red<<8 | led.color.blue;

        uint16_t accumulator = 0;

        for(int8_t bit = 23; bit >= 0; bit--) {
            accumulator |= GRB_BIT_TO_SPI_BITS(color, bit) << (16 + 8*((shiftIndex - 3)/8) - shiftIndex);

            if((shiftIndex)/8 > (shiftIndex-3)/8) {
                outputBuffer[ledOffset + shiftIndex/8 - 1] = accumulator >> 8;
                accumulator = accumulator << 8;
            }
            shiftIndex += 3;
        }
    }
}
