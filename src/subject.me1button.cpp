#include "subject.me1button.h"


Me1ButtonSubject::Me1ButtonSubject(Me4ButtonSubject &subject, Me4ButtonSubject::BUTTONS button)
:   BaseSubject(),
    _subject(subject),
    _button(button),
    _buttonState(false)
{}


void Me1ButtonSubject::operator()(void)
{
    Me4ButtonSubject::BUTTONS newButtonState = _subject.getState();

    if (isWatchingButton(newButtonState))
        changeState(true);
    else if (_buttonState)
        changeState(false);
}


bool Me1ButtonSubject::isWatchingButton(Me4ButtonSubject::BUTTONS button)
{
    return button == _button;
}


void Me1ButtonSubject::changeState(bool newState)
{
    _buttonState = newState;
    notify();
}


bool Me1ButtonSubject::getState(void)
{
    return _buttonState;
}
