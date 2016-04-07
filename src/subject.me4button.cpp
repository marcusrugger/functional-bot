#include "subject.me4button.h"


Me4ButtonSubject::Me4ButtonSubject(OBSERVER observer)
:   _notice(observer),
    _buttonState(Me4Button::BUTTON_NONE)
{}
