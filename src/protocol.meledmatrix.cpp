#include "protocol.meledmatrix.h"


MeLEDMatrixProtocol::MeLEDMatrixProtocol(DigitalPin *pinScl, DigitalPin *pinSda)
:   _pinScl(pinScl),
    _pinSda(pinSda)
{
    _pinScl->setHigh();
    _pinSda->setHigh();

    start();
    writeByte(ADDR_AUTO);
    stop();

    start();
    writeByte(Cmd_DispCtrl);
    stop();
}


void MeLEDMatrixProtocol::start()
{
    _pinScl->setHigh();
    _pinSda->setLow();
}


void MeLEDMatrixProtocol::stop()
{
    _pinScl->setLow();
    _pinSda->setLow();
    _pinScl->setHigh();
    _pinSda->setHigh();
}


void MeLEDMatrixProtocol::writeByte(uint8_t data)
{
    for (int bit = 0; bit < 8; bit++)
    {
        writeBit(data & 0x01);
        data >>= 1;
    }
}


void MeLEDMatrixProtocol::writeBit(bool bit)
{
    _pinScl->setLow();
    _pinSda->set(bit);
    _pinScl->setHigh();
}
