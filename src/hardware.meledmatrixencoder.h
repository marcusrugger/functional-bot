#ifndef HARDWARE_MELEDMATRIX_H
#define HARDWARE_MELEDMATRIX_H

#include "interfaces.h"
#include <vector>


class MeLEDMatrixEncoder
{
public:

    static std::vector<uint8_t> encodeHex(uint8_t number);
    static std::vector<uint8_t> encodeDec(uint8_t number);

};


#endif
