/*
 * WS2812B.h
 *
 *  Created on: Feb 3, 2021
 *      Author: mh
 */

#include <GraphicUtil.h>
#include <rgbled.h>
#include <string.h>


#ifndef WS2812B_H_
#define WS2812B_H_

#define GRB_BIT_TO_SPI_BITS(val, bitPos) ((1 << bitPos & val) ? 0x06 : 0x04)

using namespace Graphic;

class WS2812B : public RGBLED {
public:
    WS2812B(uint_least8_t spiIndex, uint16_t ledCount);
    virtual ~WS2812B();

protected:
    void convertOutputBuffer();

private:
    uint8_t *outputBuffer;
};

#endif
