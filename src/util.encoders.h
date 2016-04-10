#ifndef UTIL_ENCODERS_H
#define UTIL_ENCODERS_H

#include "interfaces.h"
#include <vector>


class HexEncoder
{
public:

    using Encoder = vl::Func<uint8_t(uint8_t)>;

    HexEncoder(Encoder encoder);

    std::vector<uint8_t> operator()(uint16_t number);
    std::vector<uint8_t> operator()(uint8_t x, uint8_t y);


private:

    Encoder _encoder;

};


class DecEncoder
{
public:

    using Encoder = vl::Func<uint8_t(uint8_t)>;

    DecEncoder(Encoder encoder);

    std::vector<uint8_t> operator()(uint16_t number);
    std::vector<uint8_t> operator()(uint8_t x, uint8_t y);


private:

    Encoder _encoder;

};


class MatrixHexEncoder
{
public:

    using Encoder = vl::Func<Array<uint8_t>(uint8_t)>;

    MatrixHexEncoder(Encoder encoder);

    std::vector<uint8_t> operator()(uint16_t number);
    std::vector<uint8_t> operator()(uint8_t x, uint8_t y);


private:

    Encoder _encoder;

};


class MatrixDecEncoder
{
public:

    using Encoder = vl::Func<Array<uint8_t>(uint8_t)>;

    MatrixDecEncoder(Encoder encoder);

    std::vector<uint8_t> operator()(uint16_t number);
    std::vector<uint8_t> operator()(uint8_t x, uint8_t y);


private:

    Encoder _encoder;

};


#endif
