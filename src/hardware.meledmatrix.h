#ifndef HARDWARE_MELEDMATRIX_H
#define HARDWARE_MELEDMATRIX_H

#include "interfaces.h"


class MeLEDMatrixEncoder
{
public:

    static Iterable<uint8_t> encodeChar(uint8_t ch);
    static Iterable<uint8_t> encodeHex(uint8_t number);
    static Iterable<uint8_t> encodeDec(uint8_t number);

};


#endif
