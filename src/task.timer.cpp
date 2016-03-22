#include "task.timer.h"


TaskTimer::TaskTimer(uint16_t duration, Runnable task)
:   _task(task),
    _wait_duration(duration),
    _wait_start(millis())
{}


void TaskTimer::operator()(void)
{
    if (isTimeExpired())
    {
        _wait_start = millis();
        _task();
    }
}
