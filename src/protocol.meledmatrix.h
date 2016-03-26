#ifndef PROTOCOL_MELEDMATRIX_H
#define PROTOCOL_MELEDMATRIX_H

#include "protocol.i2c.h"
#include <vector>



class MeLEDMatrixProtocol : public I2CProtocol
{
public:

    MeLEDMatrixProtocol(DigitalPin *pinScl, DigitalPin *pinSda)
    :   I2CProtocol(pinScl, pinSda)
    {
        _pinScl->setHigh();
        _pinSda->setHigh();

        writeByte(0x40);
        writeByte(0x89);
    }

    template<typename ITERABLE>
    void operator()(ITERABLE data)
    {
        // start();
        _pinScl->setHigh();
        _pinSda->setLow();

        writeByte2(STARTADDR);

        for (int a = 0; a < 4; a++)
        for (const auto b : data) writeByte2(b);

        _pinScl->setLow();
        _pinSda->setLow();
        _pinScl->setHigh();
        _pinSda->setHigh();

        // stop();
    }

    void writeByte(uint8_t data)
    {
        _pinScl->setHigh();
        _pinSda->setLow();

        for (int bit = 0; bit < 8; bit++)
        {
            _pinScl->setLow();
            _pinSda->set(data & 0x01);
            _pinScl->setHigh();
            data >>= 1;
        }

        _pinScl->setLow();
        _pinSda->setLow();
        _pinScl->setHigh();
        _pinSda->setHigh();
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
    static const uint8_t STARTADDR  = 0xC0;   //start address of LED registers
    static const uint8_t SEGDIS_ON  = 0x88;   //diplay on
    static const uint8_t SEGDIS_OFF = 0x80;   //diplay off

    static const uint8_t Cmd_DispCtrl = SEGDIS_ON + 0;

};


#endif
