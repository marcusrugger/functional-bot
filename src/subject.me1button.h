#ifndef SUBJECT_ME1BUTTON_H
#define SUBJECT_ME1BUTTON_H

#include "subject.me4button.h"


class Me1ButtonSubject : public BaseSubject
{
public:

    Me1ButtonSubject(Me4ButtonSubject &subject, Me4ButtonSubject::BUTTONS button);

    void operator()(void);

    bool getState(void);


private:

    Me4ButtonSubject &_subject;
    Me4ButtonSubject::BUTTONS _button;
    bool _buttonState;


    bool isWatchingButton(Me4ButtonSubject::BUTTONS button);
    void changeState(bool newState);

};


#endif
