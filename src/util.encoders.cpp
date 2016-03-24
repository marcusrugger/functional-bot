#include "util.encoders.h"
#include "hardware.me7segmentencoder.h"


HexEncoder::HexEncoder(Encoder encoder, Serializer writer)
:   _encoder(encoder),
    _writer(writer)
{}


void HexEncoder::operator()(uint16_t number)
{
    uint8_t digits[4];

    digits[3] = _encoder( number       );
    digits[2] = _encoder( number >>= 4 );
    digits[1] = _encoder( number >>= 4 );
    digits[0] = _encoder( number >>= 4 );

    Iterable<uint8_t> it(digits, 4);
    _writer(it);
}


DecEncoder::DecEncoder(Encoder encoder, Serializer writer)
:   _encoder(encoder),
    _writer(writer)
{}


void DecEncoder::operator()(uint16_t number)
{
    uint8_t digits[4];

    digits[3] = _encoder( number       );
    digits[2] = _encoder( number /= 10 );
    digits[1] = _encoder( number /= 10 );
    digits[0] = _encoder( number /= 10 );

    Iterable<uint8_t> it(digits, 4);
    _writer(it);
}
