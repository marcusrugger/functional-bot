#ifndef PROTOCOL_MELEDMATRIX_H
#define PROTOCOL_MELEDMATRIX_H

#include "interfaces.h"
#include "controller.pin.h"
#include <vector>



class MeLEDMatrixProtocol
{
public:

    MeLEDMatrixProtocol(DigitalPin *pinScl, DigitalPin *pinSda);

    template<typename ITERABLE>
    void operator()(ITERABLE data)
    {
        start();
        writeByte(STARTADDR);
        for (const auto b : data) writeByte(b);
        stop();
    }


private:

    DigitalPin *_pinScl;
    DigitalPin *_pinSda;

    static const uint8_t MATRIX_LENGTH  = 16;     // The matrix is 16 columns wide
    static const uint8_t ADDR_AUTO      = 0x40;   // Automatic address increment mode
    static const uint8_t STARTADDR      = 0xc0;   // start address of LED registers
    static const uint8_t SEGDIS_ON      = 0x88;   // diplay on
    static const uint8_t SEGDIS_OFF     = 0x80;   // diplay off

    static const uint8_t Cmd_DispCtrl = SEGDIS_ON + 0;

    void clearMatrix(void);
    void start();
    void stop();
    void writeByte(uint8_t data);
    void writeBit(bool bit);

};


#endif
