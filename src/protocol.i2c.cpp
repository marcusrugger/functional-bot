#include "protocol.i2c.h"


I2CProtocol::I2CProtocol(DigitalPin *pinScl, DigitalPin *pinSda)
:   _pinScl(pinScl),
    _pinSda(pinSda)
{
    _pinScl->setLow();
    _pinSda->setLow();
}


I2CProtocol::I2CProtocol(const I2CProtocol &src)
:   _pinScl(src._pinScl->clone()),
    _pinSda(src._pinSda->clone())
{}


I2CProtocol::~I2CProtocol(void)
{
    delete _pinScl;
    delete _pinSda;
}


void I2CProtocol::bitDelay(void)
{
    delayMicroseconds(5);
}


void I2CProtocol::start(void)
{
    _pinSda->setHigh();
    _pinScl->setHigh();     bitDelay();
    _pinSda->setLow();      bitDelay();
    _pinScl->setLow();
}


void I2CProtocol::stop(void)
{
    _pinSda->setLow();      bitDelay();
    _pinScl->setHigh();     bitDelay();
    _pinSda->setHigh();
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
    _pinScl->setLow();
    _pinSda->set(data);
    _pinScl->setHigh();

    bitDelay();
    stretchClock();
}


void I2CProtocol::lookForAck(void)
{
    _pinScl->setLow();
    _pinSda->setHigh();     bitDelay();
    _pinScl->setHigh();

    stretchClock();

    _pinScl->setLow();
    _pinSda->setLow();
}


void I2CProtocol::stretchClock(void)
{
    for (int cnt = 0; !_pinScl->get() && cnt < 20; cnt++)
        bitDelay();
}
