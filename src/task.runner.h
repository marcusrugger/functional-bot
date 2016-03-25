#ifndef TASK_RUNNER_H
#define TASK_RUNNER_H

#include "interfaces.h"
#include <vector>


class TaskRunner
{
public:

    TaskRunner(void);

    void operator()(void);

    void schedule(Runnable task);
    void unschedule(Runnable task);

private:

    using Tasks = std::vector<Runnable>;
    Tasks _tasks;

};

#endif
