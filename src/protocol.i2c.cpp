#include "protocol.i2c.h"


I2CProtocol::I2CProtocol(DigitalPin pinScl, DigitalPin pinSda)
:   _pinScl(pinScl),
    _pinSda(pinSda)
{
    _pinScl(LOW);
    _pinSda(LOW);
}


void I2CProtocol::bitDelay(void)
{
    delayMicroseconds(5);
}


void I2CProtocol::start(void)
{
    _pinSda(HIGH);
    _pinScl(HIGH);     bitDelay();
    _pinSda(LOW);      bitDelay();
    _pinScl(LOW);
}


void I2CProtocol::stop(void)
{
    _pinSda(LOW);      bitDelay();
    _pinScl(HIGH);     bitDelay();
    _pinSda(HIGH);
}


void I2CProtocol::writeByte(uint8_t data)
{
    for (int bit = 0; bit < 8; bit++)
    {
        writeBit(data & 0x01);
        data >>= 1;
    }

    lookForAck();
}


void I2CProtocol::writeBit(uint8_t data)
{
    _pinScl(LOW);
    _pinSda(data);
    _pinScl(HIGH);

    bitDelay();
    stretchClock();
}


void I2CProtocol::lookForAck(void)
{
    _pinScl(LOW);
    _pinSda(HIGH);     bitDelay();
    _pinScl(HIGH);

    stretchClock();

    _pinScl(LOW);
    _pinSda(LOW);
}


void I2CProtocol::stretchClock(void)
{
    for (int cnt = 0; !_pinScl() && cnt < 20; cnt++)
        bitDelay();
}
