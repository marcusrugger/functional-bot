#ifndef HARDWARE_ME7SEGMENTDIGIT_H
#define HARDWARE_ME7SEGMENTDIGIT_H

#include "interfaces.h"


class Me7SegmentEncoder
{
public:

    static uint8_t encodeHex(uint8_t number);
    static uint8_t encodeDec(uint8_t number);

private:

    static const uint8_t _hexToSegmentBitmap[];

};


#endif
