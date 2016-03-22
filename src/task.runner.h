#ifndef TASK_RUNNER_H
#define TASK_RUNNER_H

#include "interfaces.h"


class TaskRunner
{
public:

    TaskRunner(void);

    void operator()(void);

    void schedule(Runnable task);
    void unschedule(Runnable task);

private:

    static const unsigned int MAX_TASKS = 8;
    Runnable _tasks[MAX_TASKS];
    unsigned int _count = 0;

};

#endif
