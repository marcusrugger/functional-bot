#ifndef PROTOCOL_SEGMENTDISPLAY_H
#define PROTOCOL_SEGMENTDISPLAY_H

#include "protocol.i2c.h"
#include <vector>


/* Writes LED-digits to display for TM1637 */

class SegmentDisplayProtocol : public I2CProtocol
{
public:

    SegmentDisplayProtocol(DigitalPin pinScl, DigitalPin pinSda);

    template<typename FnBitMap>
    void operator()(FnBitMap fnBitmap)
    {
        start();
        writeByte(ADDR_AUTO);
        stop();

        start();
        writeByte(STARTADDR);
        for (const auto b : fnBitmap()) writeByte(b);
        stop();

        start();
        writeByte(Cmd_DispCtrl);
        stop();
    }


private:

    static const uint8_t ADDR_AUTO  = 0x40;   //Automatic address increment mode
    static const uint8_t STARTADDR  = 0xc0;   //start address of display register
    static const uint8_t SEGDIS_ON  = 0x88;   //diplay on
    static const uint8_t SEGDIS_OFF = 0x80;   //diplay off

    static const uint8_t Cmd_DispCtrl = SEGDIS_ON + 0;

};


#endif
