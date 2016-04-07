#ifndef SUBJECT_ME4BUTTON_H
#define SUBJECT_ME4BUTTON_H

#include "interfaces.h"
#include "controller.pin.h"


class Me4Button
{
public:

    enum BUTTON
    {
        BUTTON_NONE = 0x00,
        BUTTON_1    = 0x01,
        BUTTON_2    = 0x02,
        BUTTON_3    = 0x04,
        BUTTON_4    = 0x08
    };

    static BUTTON translatePin(uint16_t pinValue)
    {
        uint16_t value = pinValue / 100;

        switch (value)
        {
            case 0:  return BUTTON_1;
            case 4:  return BUTTON_2;
            case 6:  return BUTTON_3;
            case 7:  return BUTTON_4;
            default: return BUTTON_NONE;
        }
    }

};


class Me4ButtonSubject
{
public:

    using OBSERVER = vl::Func<void(Me4ButtonSubject *)>;

    Me4ButtonSubject(OBSERVER observer);

    void operator()(Me4Button::BUTTON newState)
    {
        if (newState != _buttonState)
        {
            _buttonState = newState;
            _notice(this);
        }
    }

    inline Me4Button::BUTTON getState(void)
    { return _buttonState; }


private:

    OBSERVER _notice;
    Me4Button::BUTTON _buttonState;

};


#endif
