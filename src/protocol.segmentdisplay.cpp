#include "protocol.segmentdisplay.h"


SegmentDisplayProtocol *SegmentDisplayProtocol::create(DigitalPin *pinScl, DigitalPin *pinSda)
{
    return new SegmentDisplayProtocol(pinScl, pinSda);
}


SegmentDisplayProtocol::SegmentDisplayProtocol(DigitalPin *pinScl, DigitalPin *pinSda)
:   _pinScl(pinScl),
    _pinSda(pinSda)
{
    _pinScl->setLow();
    _pinSda->setLow();
}


void SegmentDisplayProtocol::operator()(Iterable<uint8_t> data)
{
    start();
    writeByte(ADDR_AUTO);
    stop();

    start();
    writeByte(STARTADDR);
    for (const uint8_t b : data) writeByte(b);
    stop();

    start();
    writeByte(Cmd_DispCtrl);
    stop();
}


void SegmentDisplayProtocol::bitDelay(void)
{
    delayMicroseconds(5);
}


void SegmentDisplayProtocol::start(void)
{
    _pinSda->setHigh();
    _pinScl->setHigh();     bitDelay();
    _pinSda->setLow();      bitDelay();
    _pinScl->setLow();
}


void SegmentDisplayProtocol::stop(void)
{
    _pinSda->setLow();      bitDelay();
    _pinScl->setHigh();     bitDelay();
    _pinSda->setHigh();
}


void SegmentDisplayProtocol::writeByte(uint8_t data)
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


void SegmentDisplayProtocol::waitForAck(void)
{
    _pinScl->setLow();
    _pinSda->setHigh();     bitDelay();
    _pinScl->setHigh();

    stretchClock();

    _pinScl->setLow();
    _pinSda->setLow();
}


void SegmentDisplayProtocol::stretchClock(void)
{
    for (int cnt = 0; !_pinScl->get() && cnt < 20; cnt++)
        bitDelay();
}
