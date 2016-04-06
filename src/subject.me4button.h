#ifndef SUBJECT_ME4BUTTON_H
#define SUBJECT_ME4BUTTON_H

#include "interfaces.h"
#include "controller.pin.h"
#include <memory>


class Me4ButtonSubject
{
public:

    Me4ButtonSubject(Observer observer, AnalogPinReader *pin);
    Me4ButtonSubject(const Me4ButtonSubject &that);
    Me4ButtonSubject(Me4ButtonSubject &&that);

    void operator()(void);

    enum BUTTON
    {
        BUTTON_NONE = 0x00,
        BUTTON_1    = 0x01,
        BUTTON_2    = 0x02,
        BUTTON_3    = 0x04,
        BUTTON_4    = 0x08
    };

    BUTTON getState(void);


private:

    Observer _notice;
    std::auto_ptr<AnalogPinReader> _pin;
    BUTTON _buttonState;

    BUTTON translatePin(uint16_t pinValue);

};


#endif
