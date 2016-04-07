#include "protocol.segmentdisplay.h"


SegmentDisplayProtocol::SegmentDisplayProtocol(DigitalPin pinScl, DigitalPin pinSda)
:   I2CProtocol(pinScl, pinSda)
{}
