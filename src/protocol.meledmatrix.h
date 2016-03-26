#ifndef PROTOCOL_MELEDMATRIX_H
#define PROTOCOL_MELEDMATRIX_H

#include "protocol.i2c.h"
#include <vector>



class MeLEDMatrixProtocol : public I2CProtocol
{
public:

    MeLEDMatrixProtocol(DigitalPin *pinScl, DigitalPin *pinSda);

    template<typename ITERABLE>
    void operator()(ITERABLE data)
    {
        start();
        // writeByte2(STARTADDR);
        for (const auto b : data) writeByte2(b);
        stop();
    }

    void writeByte2(uint8_t data)
    {
        for (int bit = 0; bit < 8; bit++)
        {
            _pinScl->setLow();
            _pinSda->set(data & 0x01);
            _pinScl->setHigh();
            data >>= 1;
        }
    }


private:

    static const uint8_t ADDR_AUTO  = 0x40;   //Automatic address increment mode
    static const uint8_t STARTADDR  = 0xc0;   //start address of LED registers
    static const uint8_t SEGDIS_ON  = 0x88;   //diplay on
    static const uint8_t SEGDIS_OFF = 0x80;   //diplay off

    static const uint8_t Cmd_DispCtrl = SEGDIS_ON + 0;

};


#endif
