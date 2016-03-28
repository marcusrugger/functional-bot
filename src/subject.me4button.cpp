#include "subject.me4button.h"


Me4ButtonSubject::Me4ButtonSubject(AnalogPinReader *pin)
:   BaseSubject(),
    _pin(pin),
    _buttonState(BUTTON_NONE)
{}


Me4ButtonSubject::Me4ButtonSubject(const Me4ButtonSubject &that)
:   BaseSubject(),
    _pin(that._pin->clone()),
    _buttonState(that._buttonState)
{}


Me4ButtonSubject::Me4ButtonSubject(Me4ButtonSubject &&that)
:   BaseSubject(),
    _pin(that._pin),
    _buttonState(that._buttonState)
{
    that._pin = NULL;
}


Me4ButtonSubject::~Me4ButtonSubject(void)
{
    if (_pin) delete _pin;
}


void Me4ButtonSubject::operator()(void)
{
    BUTTONS newState = translatePin(_pin->readPin());

    if (newState != _buttonState)
    {
        _buttonState = newState;
        notify();
    }
}


Me4ButtonSubject::BUTTONS Me4ButtonSubject::getState(void)
{
    return _buttonState;
}


Me4ButtonSubject::BUTTONS Me4ButtonSubject::translatePin(uint16_t pinValue)
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
