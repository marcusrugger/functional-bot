#include "subject.me4button.h"


Me4ButtonSubject::Me4ButtonSubject(void)
:   BaseSubject()
{}


void Me4ButtonSubject::operator()(void)
{}


Me4ButtonSubject::BUTTONS Me4ButtonSubject::getState(void)
{
    return BUTTON_NONE;
}
