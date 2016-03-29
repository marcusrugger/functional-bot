#include "subject.base.h"


BaseSubject::BaseSubject(void)
{}


void BaseSubject::subscribe(Observer observer)
{
    Observers::iterator it = std::find(_observers.begin(), _observers.end(), observer);
    if (it == _observers.end()) _observers.push_back(observer);
}


void BaseSubject::unsubscribe(Observer observer)
{
    _observers.erase(std::remove(_observers.begin(), _observers.end(), observer), _observers.end());
}


void BaseSubject::notify(void)
{
    for (auto observer : _observers) observer();
}
