#include "subject.me1button.h"


Me1ButtonSubject::Me1ButtonSubject(OBSERVER observer, Me4Button::BUTTON buttonToWatch)
:   _notice(observer),
    _watchedButton(buttonToWatch),
    _buttonState(BUTTON_RELEASED)
{}


void Me1ButtonSubject::operator()(Me4ButtonSubject *subject)
{
    evaluateNewPanelState(subject->getState());
}


void Me1ButtonSubject::evaluateNewPanelState(Me4Button::BUTTON panelState)
{
    if (panelState == _watchedButton)
        setButtonState(BUTTON_PRESSED);
    else
        setButtonState(BUTTON_RELEASED);
}


void Me1ButtonSubject::setButtonState(BUTTON_STATE newState)
{
    if (newState != _buttonState)
    {
        _buttonState = newState;
        _notice(this);
    }
}


Me1ButtonSubject::BUTTON_STATE Me1ButtonSubject::getState(void)
{
    return _buttonState;
}
