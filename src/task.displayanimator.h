#ifndef TASK_DISPLAYANIMATOR_H
#define TASK_DISPLAYANIMATOR_H

#include "interfaces.h"
#include <avr/pgmspace.h>


class DisplayAnimatorTask
{
public:

    DisplayAnimatorTask(void);

    using FnBitMap = vl::Func<ProgMemArray(void)>;

    FnBitMap operator()(void);


private:

    uint16_t _animation_index;

    static const uint16_t animation_count;
    static const uint8_t animation[][4];

};


#endif
