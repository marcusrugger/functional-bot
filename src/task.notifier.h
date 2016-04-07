#ifndef TASK_NOTIFIER_H
#define TASK_NOTIFIER_H

#include "interfaces.h"
#include <vector>


template<typename SUBJECT>
class Notifier
{
public:

    using OBSERVER = vl::Func<void(SUBJECT)>;

    Notifier(void);

    void subscribe(OBSERVER observer)
    {
        if (std::find(_observers.begin(), _observers.end(), observer) == _observers.end())
            _observers.push_back(observer);
    }

    void unsubscribe(OBSERVER observer)
    {
        _observers.erase(std::remove(_observers.begin(), _observers.end(), observer), _observers.end());
    }


    void operator()(SUBJECT subject)
    { for (auto notice : _observers) notice(subject); }


private:

    using Observers = std::vector<OBSERVER>;
    Observers _observers;

};


#endif
