#ifndef SUBJECT_ME1BUTTON_H
#define SUBJECT_ME1BUTTON_H

#include "subject.me4button.h"


class Me1ButtonSubject
{
public:

    enum BUTTON_STATE
    {
        BUTTON_RELEASED,
        BUTTON_PRESSED
    };

    Me1ButtonSubject(Observer observer, Me4ButtonSubject &subject, Me4ButtonSubject::BUTTON buttonToWatch);

    void operator()(void);

    BUTTON_STATE getState(void);


private:

    Observer _notice;
    Me4ButtonSubject &_subject;
    Me4ButtonSubject::BUTTON _watchedButton;
    BUTTON_STATE _buttonState;

    void evaluateNewPanelState(Me4ButtonSubject::BUTTON panelState);
    void setButtonState(BUTTON_STATE newState);

};


#endif
