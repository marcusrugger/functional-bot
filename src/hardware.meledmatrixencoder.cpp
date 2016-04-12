#include "hardware.meledmatrixencoder.h"
#include <avr/pgmspace.h>


const uint8_t hexMap[][3] PROGMEM
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


std::vector<uint8_t> MeLEDMatrixEncoder::encodeHex(uint8_t n)
{
    return std::vector<uint8_t>
    {
        pgm_read_byte(&(hexMap[n & 0x0f][0])),
        pgm_read_byte(&(hexMap[n & 0x0f][1])),
        pgm_read_byte(&(hexMap[n & 0x0f][2]))
    };
}


std::vector<uint8_t> MeLEDMatrixEncoder::encodeDec(uint8_t n)
{
    return std::vector<uint8_t>
    {
        pgm_read_byte(&(hexMap[n % 10][0])),
        pgm_read_byte(&(hexMap[n % 10][1])),
        pgm_read_byte(&(hexMap[n % 10][2]))
    };
}
