#ifndef TASK_TIMER_H
#define TASK_TIMER_H

#include "interfaces.h"


class TaskTimer
{
public:

    TaskTimer(uint16_t duration, Runnable task);

    void operator()(void);


private:

    Runnable _task;
    uint16_t _wait_duration;
    uint16_t _wait_start;


    inline bool isTimeExpired(void)
    { return millis() - _wait_start > _wait_duration; }

};


#endif
