#ifndef TASK_DISPLAYANIMATOR_H
#define TASK_DISPLAYANIMATOR_H

#include "interfaces.h"


class DisplayAnimatorTask
{
public:

    DisplayAnimatorTask(Serializer writer);

    void operator()(void);


private:

    Serializer _writer;
    uint16_t _animation_index;

};


#endif
