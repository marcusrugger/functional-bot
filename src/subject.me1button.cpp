#include "subject.me1button.h"


Me1ButtonSubject::Me1ButtonSubject(Me4ButtonSubject &subject, Me4ButtonSubject::BUTTON buttonToWatch)
:   BaseSubject(),
    _subject(subject),
    _watchedButton(buttonToWatch),
    _buttonState(BUTTON_RELEASED)
{}


void Me1ButtonSubject::operator()(void)
{
    evaluateNewPanelState(_subject.getState());
}


void Me1ButtonSubject::evaluateNewPanelState(Me4ButtonSubject::BUTTON panelState)
{
    if (panelState == _watchedButton)
        setButtonState(BUTTON_PRESSED);
    else
        setButtonState(BUTTON_RELEASED);
}


void Me1ButtonSubject::setButtonState(BUTTON_STATE newState)
{
    if (_buttonState != newState)
    {
        _buttonState = newState;
        notify();
    }
}


Me1ButtonSubject::BUTTON_STATE Me1ButtonSubject::getState(void)
{
    return _buttonState;
}
