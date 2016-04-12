#ifndef UTIL_ENCODERS_H
#define UTIL_ENCODERS_H

#include "interfaces.h"
#include <vector>


class HexEncoder
{
public:

    using Encoder = vl::Func<uint8_t(uint8_t)>;

    HexEncoder(Encoder encoder);

    using FnBitMap = vl::Func<std::vector<uint8_t>(void)>;

    FnBitMap operator()(uint16_t number);
    FnBitMap operator()(uint8_t x, uint8_t y);


private:

    Encoder _encoder;

};


class DecEncoder
{
public:

    using Encoder = vl::Func<uint8_t(uint8_t)>;

    DecEncoder(Encoder encoder);

    using FnBitMap = vl::Func<std::vector<uint8_t>(void)>;

    FnBitMap operator()(uint16_t number);
    FnBitMap operator()(uint8_t x, uint8_t y);


private:

    Encoder _encoder;

};


class MatrixHexEncoder
{
public:

    using EncoderType = std::vector<uint8_t>;
    using Encoder = vl::Func<EncoderType(uint8_t)>;

    MatrixHexEncoder(Encoder encoder);

    using FnBitMap = vl::Func<std::vector<uint8_t>(void)>;

    FnBitMap operator()(uint16_t number);
    FnBitMap operator()(uint8_t x, uint8_t y);


private:

    Encoder _encoder;

};


class MatrixDecEncoder
{
public:

    using EncoderType = std::vector<uint8_t>;
    using Encoder = vl::Func<EncoderType(uint8_t)>;

    MatrixDecEncoder(Encoder encoder);

    using FnBitMap = vl::Func<std::vector<uint8_t>(void)>;

    FnBitMap operator()(uint16_t number);
    FnBitMap operator()(uint8_t x, uint8_t y);


private:

    Encoder _encoder;

};


#endif
