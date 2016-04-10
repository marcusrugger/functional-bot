#ifndef TASK_RUNNER_H
#define TASK_RUNNER_H

#include "interfaces.h"
#include <vector>


class TaskRunner
{
public:

    TaskRunner(void);
    TaskRunner(const TaskRunner &other);

    void operator()(void) const;

    void subscribe(Runnable task);
    void unsubscribe(Runnable task);

private:

    using Tasks = std::vector<Runnable>;
    Tasks _tasks;

};

#endif
