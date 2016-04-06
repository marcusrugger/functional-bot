#include "subject.me4button.h"


Me4ButtonSubject::Me4ButtonSubject(Observer observer, AnalogPinReader *pin)
:   _notice(observer),
    _pin(pin),
    _buttonState(BUTTON_NONE)
{}


Me4ButtonSubject::Me4ButtonSubject(const Me4ButtonSubject &that)
:   _notice(that._notice),
    _pin(that._pin->clone()),
    _buttonState(that._buttonState)
{}


Me4ButtonSubject::Me4ButtonSubject(Me4ButtonSubject &&that)
:   _notice(that._notice),
    _pin(that._pin.release()),
    _buttonState(that._buttonState)
{}


void Me4ButtonSubject::operator()(void)
{
    BUTTON newState = translatePin(_pin->readPin());

    if (newState != _buttonState)
    {
        _buttonState = newState;
        _notice();
    }
}


Me4ButtonSubject::BUTTON Me4ButtonSubject::getState(void)
{
    return _buttonState;
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
