#include "task.runner.h"


TaskRunner::TaskRunner(void)
:   _count(0)
{}


void TaskRunner::operator()(void)
{
    for (unsigned int i = 0; i < _count; ++i)
        _tasks[i]();
}


void TaskRunner::schedule(Runnable task)
{
    if (_count < MAX_TASKS)
        _tasks[_count++] = task;
}


void TaskRunner::unschedule(Runnable task)
{
    unsigned int is, id;
    for (is = id = 0; is < _count; )
    {
        if (_tasks[is] == task)
        {
            if (++is < _count)
                _tasks[id++] = _tasks[is++];
            --_count;
        }
        else if (id < is)
            _tasks[id++] = _tasks[is++];
        else
            id = ++is;
    }
}
