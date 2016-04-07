#ifndef SUBJECT_ME4BUTTON_H
#define SUBJECT_ME4BUTTON_H

#include "interfaces.h"
#include "controller.pin.h"
#include "task.notifier.h"
#include <memory>


class Me4ButtonSubject
{
public:

    using OBSERVER = vl::Func<void(Me4ButtonSubject *)>;

    Me4ButtonSubject(OBSERVER observer);

    void operator()(int16_t pinValue);

    enum BUTTON
    {
        BUTTON_NONE = 0x00,
        BUTTON_1    = 0x01,
        BUTTON_2    = 0x02,
        BUTTON_3    = 0x04,
        BUTTON_4    = 0x08
    };

    inline BUTTON getState(void)
    { return _buttonState; }


private:

    OBSERVER _notice;
    BUTTON _buttonState;

    BUTTON translatePin(uint16_t pinValue);
    void setState(BUTTON newState);

};


#endif
