#ifndef SUBJECT_BASE_H
#define SUBJECT_BASE_H

#include "interfaces.h"
#include <vector>


class BaseSubject : public Subject
{
public:

    void attach(Observer observer);
    void detach(Observer observer);


protected:

    BaseSubject(void);

    void notify(void);


private:

    using Observers = std::vector<Observer>;
    Observers _observers;

};

#endif
