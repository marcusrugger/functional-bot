#include "protocol.segmentdisplay.h"


SegmentDisplayProtocol::SegmentDisplayProtocol(DigitalPin *pinScl, DigitalPin *pinSda)
:   I2CProtocol(pinScl, pinSda)
{}


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
