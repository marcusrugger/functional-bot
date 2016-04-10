#include "util.encoders.h"
#include "hardware.me7segmentencoder.h"


HexEncoder::HexEncoder(Encoder encoder)
:   _encoder(encoder)
{}


HexEncoder::FnBitMap HexEncoder::operator()(uint16_t number)
{
    return [number, this]() -> std::vector<uint8_t>
    {
        std::vector<uint8_t> digits(4);

        digits[3] = _encoder( number       );
        digits[2] = _encoder( number >> 4  );
        digits[1] = _encoder( number >> 8  );
        digits[0] = _encoder( number >> 12 );

        return digits;
    };
}


HexEncoder::FnBitMap HexEncoder::operator()(uint8_t x, uint8_t y)
{
    return [x, y, this]() -> std::vector<uint8_t>
    {
        std::vector<uint8_t> digits(4);

        digits[3] = _encoder( x      );
        digits[2] = _encoder( x >> 4 );
        digits[1] = _encoder( y      );
        digits[0] = _encoder( y >> 4 );

        return digits;
    };
}


DecEncoder::DecEncoder(Encoder encoder)
:   _encoder(encoder)
{}


DecEncoder::FnBitMap DecEncoder::operator()(uint16_t number)
{
    return [number, this]() -> std::vector<uint8_t>
    {
        std::vector<uint8_t> digits(4);

        digits[3] = _encoder( number        );
        digits[2] = _encoder( number / 10   );
        digits[1] = _encoder( number / 100  );
        digits[0] = _encoder( number / 1000 );

        return digits;
    };
}


DecEncoder::FnBitMap DecEncoder::operator()(uint8_t x, uint8_t y)
{
    return [x, y, this]() -> std::vector<uint8_t>
    {
        std::vector<uint8_t> digits(4);

        digits[3] = _encoder( x      );
        digits[2] = _encoder( x / 10 );
        digits[1] = _encoder( y      );
        digits[0] = _encoder( y / 10 );

        return digits;
    };
}


MatrixHexEncoder::MatrixHexEncoder(Encoder encoder)
:   _encoder(encoder)
{}


MatrixHexEncoder::FnBitMap MatrixHexEncoder::operator()(uint16_t number)
{
    return [number, this]() -> std::vector<uint8_t>
    {
        std::vector<uint8_t> digits;

        auto fnEncodeDigit = [&digits, this](uint8_t n)
        {
            Array<uint8_t> array(_encoder(n));
            digits.push_back(0);
            digits.insert(digits.end(), array.begin(), array.end());
        };

        fnEncodeDigit(number);
        fnEncodeDigit(number >> 4);
        fnEncodeDigit(number >> 8);
        fnEncodeDigit(number >> 12);

        return digits;
    };
}


MatrixHexEncoder::FnBitMap MatrixHexEncoder::operator()(uint8_t x, uint8_t y)
{
    return [x, y, this]() -> std::vector<uint8_t>
    {
        std::vector<uint8_t> digits;
        Array<uint8_t> array;

        array = _encoder(x);
        digits.insert(digits.end(), array.begin(), array.end());
        digits.push_back(0);

        array = _encoder(x >> 4);
        digits.insert(digits.end(), array.begin(), array.end());
        digits.push_back(0);

        array = _encoder(y);
        digits.push_back(0);
        digits.insert(digits.end(), array.begin(), array.end());

        array = _encoder(y >> 4);
        digits.push_back(0);
        digits.insert(digits.end(), array.begin(), array.end());

        return digits;
    };
}


MatrixDecEncoder::MatrixDecEncoder(Encoder encoder)
:   _encoder(encoder)
{}


MatrixDecEncoder::FnBitMap MatrixDecEncoder::operator()(uint16_t number)
{
    return [number, this]() -> std::vector<uint8_t>
    {
        std::vector<uint8_t> digits;

        auto fnEncodeDigit = [&digits, this](uint8_t n)
        {
            Array<uint8_t> array(_encoder(n));
            digits.push_back(0);
            digits.insert(digits.end(), array.begin(), array.end());
        };

        fnEncodeDigit(number);
        fnEncodeDigit(number / 10);
        fnEncodeDigit(number / 100);
        fnEncodeDigit(number / 1000);

        return digits;
    };
}


MatrixDecEncoder::FnBitMap MatrixDecEncoder::operator()(uint8_t x, uint8_t y)
{
    return [x, y, this]() -> std::vector<uint8_t>
    {
        std::vector<uint8_t> digits;
        Array<uint8_t> array;

        array = _encoder(x);
        digits.insert(digits.end(), array.begin(), array.end());
        digits.push_back(0);

        array = _encoder(x / 10);
        digits.insert(digits.end(), array.begin(), array.end());
        digits.push_back(0);

        array = _encoder(y);
        digits.push_back(0);
        digits.insert(digits.end(), array.begin(), array.end());

        array = _encoder(y / 10);
        digits.push_back(0);
        digits.insert(digits.end(), array.begin(), array.end());

        return digits;
    };
}
