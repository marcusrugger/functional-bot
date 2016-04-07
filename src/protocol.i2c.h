#ifndef PROTOCOL_I2C_H
#define PROTOCOL_I2C_H

#include <Arduino.h>
#include "interfaces.h"
#include "controller.pin.h"


/* Basic methods for writing I2C */

class I2CProtocol
{
protected:

    I2CProtocol(DigitalPin pinScl, DigitalPin pinSda);

    void bitDelay(void);
    void start(void);
    void stop(void);
    void writeByte(uint8_t data);
    void writeBit(uint8_t data);
    void lookForAck(void);
    void stretchClock(void);


private:

    DigitalPin _pinScl;
    DigitalPin _pinSda;

};


#endif
