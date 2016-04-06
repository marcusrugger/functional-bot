#include "task.notifier.h"


Notifier::Notifier(void)
{}


void Notifier::subscribe(Observer observer)
{
    if (std::find(_observers.begin(), _observers.end(), observer) == _observers.end())
        _observers.push_back(observer);
}


void Notifier::unsubscribe(Observer observer)
{
    _observers.erase(std::remove(_observers.begin(), _observers.end(), observer), _observers.end());
}


void Notifier::operator()(void)
{
    for (auto notify : _observers) notify();
}
