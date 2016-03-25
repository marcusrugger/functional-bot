#ifndef TASK_DISPLAYANIMATOR_H
#define TASK_DISPLAYANIMATOR_H

#include "interfaces.h"


class DisplayAnimatorTask
{
public:

    DisplayAnimatorTask(void);

    Iterable<uint8_t> operator()(void);


private:

    uint16_t _animation_index;

};


#endif
