#ifndef TASK_TIMER_H
#define TASK_TIMER_H

#include "interfaces.h"


class TaskTimer
{
public:

    TaskTimer(unsigned long duration, Runnable task);

    void operator()(void);


private:

    Runnable _task;
    unsigned long _wait_duration;
    unsigned long _wait_start;


    inline bool isTimeExpired(void)
    { return millis() - _wait_start > _wait_duration; }

};


#endif
