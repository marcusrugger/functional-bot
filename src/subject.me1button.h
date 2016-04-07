#ifndef SUBJECT_ME1BUTTON_H
#define SUBJECT_ME1BUTTON_H

#include "subject.me4button.h"


class Me1ButtonSubject
{
public:

    using OBSERVER = vl::Func<void(Me1ButtonSubject *)>;

    enum BUTTON_STATE
    {
        BUTTON_RELEASED,
        BUTTON_PRESSED
    };

    Me1ButtonSubject(OBSERVER observer, Me4Button::BUTTON buttonToWatch);

    void operator()(Me4ButtonSubject *subject);

    BUTTON_STATE getState(void);


private:

    OBSERVER _notice;
    Me4Button::BUTTON _watchedButton;
    BUTTON_STATE _buttonState;

    void evaluateNewPanelState(Me4Button::BUTTON panelState);
    void setButtonState(BUTTON_STATE newState);

};


#endif
