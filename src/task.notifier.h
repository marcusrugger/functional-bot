#ifndef TASK_NOTIFIER_H
#define TASK_NOTIFIER_H

#include "interfaces.h"
#include <vector>


class Notifier : public Subject
{
public:

    Notifier(void);

    void subscribe(Observer observer);
    void unsubscribe(Observer observer);

    void operator()(void);


private:

    using Observers = std::vector<Observer>;
    Observers _observers;

};


#endif
