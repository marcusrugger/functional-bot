#ifndef TASK_ANALOGPINWRITER_H
#define TASK_ANALOGPINWRITER_H

#include "interfaces.h"
#include "controller.pin.h"


class AnalogPinWriter
{
public:

    using Writer = vl::Func<void(uint16_t)>;

    AnalogPinWriter(AnalogPinReader *pin, Writer writer);

    void operator()(void);


private:

    Writer _writer;
    AnalogPinReader *_pin;

};


#endif
