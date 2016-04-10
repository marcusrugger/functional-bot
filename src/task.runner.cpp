#include "task.runner.h"
#include <algorithm>


TaskRunner::TaskRunner(void)
{}


TaskRunner::TaskRunner(const TaskRunner &other)
:   _tasks(other._tasks)
{}


void TaskRunner::operator()(void) const
{
    for (auto task : _tasks) task();
}


void TaskRunner::subscribe(Runnable task)
{
    _tasks.push_back(task);
}


void TaskRunner::unsubscribe(Runnable task)
{
    _tasks.erase(std::remove(_tasks.begin(), _tasks.end(), task), _tasks.end());
}
