#include "util.encoders.h"
#include "hardware.me7segmentencoder.h"


HexEncoder::HexEncoder(Encoder encoder)
:   _encoder(encoder)
{}


std::vector<uint8_t> HexEncoder::operator()(uint16_t number)
{
    std::vector<uint8_t> digits(4);

    digits[3] = _encoder( number       );
    digits[2] = _encoder( number >>= 4 );
    digits[1] = _encoder( number >>= 4 );
    digits[0] = _encoder( number >>= 4 );

    return digits;
}


DecEncoder::DecEncoder(Encoder encoder)
:   _encoder(encoder)
{}


std::vector<uint8_t> DecEncoder::operator()(uint16_t number)
{
    std::vector<uint8_t> digits(4);

    digits[3] = _encoder( number       );
    digits[2] = _encoder( number /= 10 );
    digits[1] = _encoder( number /= 10 );
    digits[0] = _encoder( number /= 10 );

    return digits;
}
