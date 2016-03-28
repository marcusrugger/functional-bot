#include "subject.me1button.h"


Me1ButtonSubject::Me1ButtonSubject(Me4ButtonSubject &subject, Me4ButtonSubject::BUTTONS button)
:   BaseSubject(),
    _subject(subject),
    _button(button),
    _buttonState(false)
{}


void Me1ButtonSubject::operator()(void)
{
    Me4ButtonSubject::BUTTONS newState = _subject.getState();

    if (isWatchingButton(newState))
    {
        _buttonState = true;
        notify();
    }
    else
    {
        if (_buttonState)
        {
            _buttonState = false;
            notify();
        }
    }
}


bool Me1ButtonSubject::getState(void)
{
    return _buttonState;
}
