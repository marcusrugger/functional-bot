#ifndef UTIL_ENCODERS_H
#define UTIL_ENCODERS_H

#include "interfaces.h"


class HexEncoder
{
public:

    using Encoder = vl::Func<uint8_t(uint8_t)>;

    HexEncoder(Encoder encoder, Serializer writer);

    void operator()(uint16_t number);


private:

    Encoder _encoder;
    Serializer _writer;

};


class DecEncoder
{
public:

    using Encoder = vl::Func<uint8_t(uint8_t)>;

    DecEncoder(Encoder encoder, Serializer writer);

    void operator()(uint16_t number);


private:

    Encoder _encoder;
    Serializer _writer;

};


#endif
