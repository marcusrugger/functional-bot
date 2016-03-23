#include "protocol.i2c.h"


I2CProtocol::I2CProtocol(DigitalPin *pinScl, DigitalPin *pinSda)
:   _pinScl(pinScl),
    _pinSda(pinSda)
{
    _pinScl->setLow();
    _pinSda->setLow();
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
        _pinScl->setLow();
        _pinSda->set(data & 0x01);
        _pinScl->setHigh();
        bitDelay();

        stretchClock();

        data >>= 1;
    }

    waitForAck();
}


void I2CProtocol::waitForAck(void)
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