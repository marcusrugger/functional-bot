#ifndef SUBJECT_ME4BUTTON_H
#define SUBJECT_ME4BUTTON_H

#include "interfaces.h"
#include "subject.base.h"


class Me4ButtonSubject : public BaseSubject
{
public:

    Me4ButtonSubject(void);

    void operator()(void);

    enum BUTTONS
    {
        BUTTON_NONE = 0x00,
        BUTTON_1    = 0x01,
        BUTTON_2    = 0x02,
        BUTTON_3    = 0x04,
        BUTTON_4    = 0x08
    };

    BUTTONS getState(void);


private:

    BUTTONS _button_state;

};


#endif
