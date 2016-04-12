#include "protocol.meledmatrix.h"


MeLEDMatrixProtocol::MeLEDMatrixProtocol(SinkBool pinScl, SinkBool pinSda)
:   _pinScl(pinScl),
    _pinSda(pinSda)
{
    _pinScl(HIGH);
    _pinSda(HIGH);

    start();
    writeByte(ADDR_AUTO);
    stop();

    start();
    writeByte(Cmd_DispCtrl);
    stop();

    clearMatrix();
}


MeLEDMatrixProtocol::MeLEDMatrixProtocol(const MeLEDMatrixProtocol &other)
:   _pinScl(other._pinScl),
    _pinSda(other._pinSda)
{}


void MeLEDMatrixProtocol::clearMatrix(void)
{
    start();
    writeByte(STARTADDR);
    for (int a = 0; a < MATRIX_LENGTH; ++a) writeByte(0);
    stop();
}
