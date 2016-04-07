#ifndef SUBJECT_ME1BUTTON_H
#define SUBJECT_ME1BUTTON_H

#include "subject.me4button.h"


class Me1ButtonSubject
{
public:

    using OBSERVER = vl::Func<void(BUTTON_STATE)>;

    Me1ButtonSubject(OBSERVER observer, Me4Button::BUTTON buttonToWatch);

    void operator()(Me4Button::BUTTON);


private:

    OBSERVER _notice;
    Me4Button::BUTTON _watchedButton;
    BUTTON_STATE _buttonState;

    void setButtonState(BUTTON_STATE newState);

};


#endif
