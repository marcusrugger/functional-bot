#ifndef SUBJECT_ME1BUTTON_H
#define SUBJECT_ME1BUTTON_H

#include "subject.me4button.h"


class Me1ButtonSubject
{
public:

    Me1ButtonSubject(void) {};
    Me1ButtonSubject(SinkButton observer, Me4Button::BUTTON buttonToWatch)
    :   _notice(observer),
        _watchedButton(buttonToWatch),
        _buttonState(BUTTON_RELEASED)
    {}

    void operator()(Me4Button::BUTTON panelState)
    {
        if (panelState == _watchedButton)
            setButtonState(BUTTON_PRESSED);
        else
            setButtonState(BUTTON_RELEASED);
    }


private:

    SinkButton _notice;
    Me4Button::BUTTON _watchedButton;
    BUTTON_STATE _buttonState;

    void setButtonState(BUTTON_STATE newState)
    {
        if (newState != _buttonState)
        {
            _buttonState = newState;
            _notice(_buttonState);
        }
    }

};


#endif
