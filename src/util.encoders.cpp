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


MatrixHexEncoder::MatrixHexEncoder(Encoder encoder)
:   _encoder(encoder)
{}


std::vector<uint8_t> MatrixHexEncoder::operator()(uint16_t number)
{
    std::vector<uint8_t> digits;
    Array<uint8_t> array;

    array = _encoder(number);
    digits.insert(digits.end(), array.begin(), array.end());
    digits.push_back(0);

    array = _encoder(number >>= 4);
    digits.insert(digits.end(), array.begin(), array.end());
    digits.push_back(0);

    array = _encoder(number >>= 4);
    digits.push_back(0);
    digits.insert(digits.end(), array.begin(), array.end());

    array = _encoder(number >>= 4);
    digits.push_back(0);
    digits.insert(digits.end(), array.begin(), array.end());

    return digits;
}


MatrixDecEncoder::MatrixDecEncoder(Encoder encoder)
:   _encoder(encoder)
{}


std::vector<uint8_t> MatrixDecEncoder::operator()(uint16_t number)
{
    std::vector<uint8_t> digits;
    Array<uint8_t> array;

    array = _encoder(number);
    digits.insert(digits.end(), array.begin(), array.end());
    digits.push_back(0);

    array = _encoder(number /= 10);
    digits.insert(digits.end(), array.begin(), array.end());
    digits.push_back(0);

    array = _encoder(number /= 10);
    digits.push_back(0);
    digits.insert(digits.end(), array.begin(), array.end());

    array = _encoder(number /= 10);
    digits.push_back(0);
    digits.insert(digits.end(), array.begin(), array.end());

    return digits;
}
