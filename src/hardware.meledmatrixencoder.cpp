#include "hardware.meledmatrixencoder.h"


const uint8_t charMap[][5] =
{
    {   // A
        0b00111110,
        0b01010000,
        0b10010000,
        0b01010000,
        0b00111110
    },
    {   // B
        0b01101100,
        0b10010010,
        0b10010010,
        0b10010010,
        0b11111110
    }
};


Array<uint8_t> MeLEDMatrixEncoder::encodeChar(uint8_t n)
{
    return Array<uint8_t>(charMap[n % 2], 5);
}


const uint8_t hexMap[][3]
{
    {   // 0
        0b11111000,
        0b10001000,
        0b11111000
    },
    {   // 1
        0b00000000,
        0b11111000,
        0b00000000
    },
    {   // 2
        0b11101000,
        0b10101000,
        0b10111000
    },
    {   // 3
        0b11111000,
        0b10101000,
        0b10101000
    },
    {   // 4
        0b11111000,
        0b00100000,
        0b11100000
    },
    {   // 5
        0b10111000,
        0b10101000,
        0b11101000
    },
    {   // 6
        0b10111000,
        0b10101000,
        0b11111000
    },
    {   // 7
        0b11111000,
        0b10000000,
        0b10000000
    },
    {   // 8
        0b11111000,
        0b10101000,
        0b11111000
    },
    {   // 9
        0b11111000,
        0b10101000,
        0b11101000
    },
    {   // A
        0b11111000,
        0b10100000,
        0b11111000
    },
    {   // b
        0b00111000,
        0b00101000,
        0b11111000
    },
    {   // C
        0b10001000,
        0b10001000,
        0b11111000
    },
    {   // d
        0b11111000,
        0b00101000,
        0b00111000
    },
    {   // E
        0b10101000,
        0b10101000,
        0b11111000
    },
    {   // F
        0b10100000,
        0b10100000,
        0b11111000
    }
};


Array<uint8_t> MeLEDMatrixEncoder::encodeHex(uint8_t n)
{
    return Array<uint8_t>(hexMap[n & 0x0f], 3);
}


Array<uint8_t> MeLEDMatrixEncoder::encodeDec(uint8_t n)
{
    return Array<uint8_t>(hexMap[n % 10], 3);
}