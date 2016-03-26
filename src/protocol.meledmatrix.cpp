#include "protocol.meledmatrix.h"


MeLEDMatrixProtocol::MeLEDMatrixProtocol(DigitalPin *pinScl, DigitalPin *pinSda)
:   I2CProtocol(pinScl, pinSda)
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
