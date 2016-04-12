#ifndef PROTOCOL_MELEDMATRIX_H
#define PROTOCOL_MELEDMATRIX_H

#include "interfaces.h"
#include "controller.pin.h"
#include <vector>



class MeLEDMatrixProtocol
{
public:

    MeLEDMatrixProtocol(SinkBool pinScl, SinkBool pinSda);
    MeLEDMatrixProtocol(const MeLEDMatrixProtocol &other);

    template<typename FnBitMap>
    void operator()(FnBitMap fnBitmap)
    {
        start();
        writeByte(STARTADDR);
        for (const auto b : fnBitmap()) writeByte(b);
        stop();
    }


private:

    SinkBool _pinScl;
    SinkBool _pinSda;

    static const uint8_t MATRIX_LENGTH  = 16;     // The matrix is 16 columns wide
    static const uint8_t ADDR_AUTO      = 0x40;   // Automatic address increment mode
    static const uint8_t STARTADDR      = 0xc0;   // start address of LED registers
    static const uint8_t SEGDIS_ON      = 0x88;   // diplay on
    static const uint8_t SEGDIS_OFF     = 0x80;   // diplay off

    static const uint8_t Cmd_DispCtrl = SEGDIS_ON + 0;

    void clearMatrix(void);

    inline void start()
    {
        _pinScl(HIGH);
        _pinSda(LOW);
    }

    inline void stop()
    {
        _pinScl(LOW);
        _pinSda(LOW);
        _pinScl(HIGH);
        _pinSda(HIGH);
    }

    inline void writeByte(uint8_t data)
    {
        writeBit(data & 0x01);
        writeBit(data & 0x02);
        writeBit(data & 0x04);
        writeBit(data & 0x08);

        writeBit(data & 0x10);
        writeBit(data & 0x20);
        writeBit(data & 0x40);
        writeBit(data & 0x80);
    }

    inline void writeBit(bool bit)
    {
        _pinScl(LOW);
        _pinSda(bit);
        _pinScl(HIGH);
    }

};


#endif
