#include "task.analogpinwriter.h"


AnalogPinWriter::AnalogPinWriter(AnalogPinReader *pin, Writer writer)
:   _writer(writer),
    _pin(pin)
{}


void AnalogPinWriter::operator()(void)
{
    _writer(_pin->readPin());
}
