#include "subject.me4button.h"


Me4ButtonSubject::Me4ButtonSubject(void)
:   BaseSubject(),
    _button_state(BUTTON_NONE)
{}


void Me4ButtonSubject::operator()(void)
{}


Me4ButtonSubject::BUTTONS Me4ButtonSubject::getState(void)
{
    return _button_state;
}
