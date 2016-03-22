#include "task.runner.h"
#include <algorithm>


TaskRunner::TaskRunner(void)
{}


void TaskRunner::operator()(void)
{
    for (auto task : _tasks)
        task();
}


void TaskRunner::schedule(Runnable task)
{
    _tasks.push_back(task);
}


void TaskRunner::unschedule(Runnable task)
{
    Tasks::iterator it = std::find(_tasks.begin(), _tasks.end(), task);
    if (it != _tasks.end())
        _tasks.erase(it);
}
