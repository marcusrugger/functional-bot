#include "subject.me4button.h"


Me4ButtonSubject::Me4ButtonSubject(OBSERVER observer)
:   _notice(observer),
    _buttonState(BUTTON_NONE)
{}


void Me4ButtonSubject::operator()(int16_t pinValue)
{
    setState(translatePin(pinValue));
}


Me4ButtonSubject::BUTTON Me4ButtonSubject::translatePin(uint16_t pinValue)
{
    uint16_t value = pinValue / 100;

    switch (value)
    {
        case 0:  return BUTTON_1;
        case 4:  return BUTTON_2;
        case 6:  return BUTTON_3;
        case 7:  return BUTTON_4;
        default: return BUTTON_NONE;
    }
}


void Me4ButtonSubject::setState(BUTTON newState)
{
    if (newState != _buttonState)
    {
        _buttonState = newState;
        _notice(this);
    }
}
