#include "task.runner.h"
#include <algorithm>


TaskRunner::TaskRunner(void)
{}


void TaskRunner::operator()(void)
{
    for (auto task : _tasks) task();
}


void TaskRunner::subscribe(Runnable task)
{
    Tasks::iterator it = std::find(_tasks.begin(), _tasks.end(), task);
    if (it == _tasks.end()) _tasks.push_back(task);
}


void TaskRunner::unsubscribe(Runnable task)
{
    _tasks.erase(std::remove(_tasks.begin(), _tasks.end(), task), _tasks.end());
}
