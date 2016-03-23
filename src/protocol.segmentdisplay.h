#ifndef PROTOCOL_SEGMENTDISPLAY_H
#define PROTOCOL_SEGMENTDISPLAY_H

#include <Arduino.h>
#include "interfaces.h"
#include "controller.pin.h"


/* Writes LED-digits to display for TM1637 */

class SegmentDisplayProtocol
{
public:

    static SegmentDisplayProtocol *create(DigitalPin *pinScl, DigitalPin *pinSda);
    SegmentDisplayProtocol(DigitalPin *pinScl, DigitalPin *pinSda);

    void setDisplayOn(bool flag);

    void operator()(Iterable<uint8_t> data);

private:

    DigitalPin *_pinScl;
    DigitalPin *_pinSda;

    static const uint8_t ADDR_AUTO  = 0x40;   //Automatic address increment mode
    static const uint8_t STARTADDR  = 0xc0;   //start address of display register
    static const uint8_t SEGDIS_ON  = 0x88;   //diplay on
    static const uint8_t SEGDIS_OFF = 0x80;   //diplay off

    static const uint8_t Cmd_DispCtrl = SEGDIS_ON + 2;

    void bitDelay(void);
    void start(void);
    void stop(void);
    void writeByte(uint8_t data);
    void waitForAck(void);
    void stretchClock(void);

};


#endif
