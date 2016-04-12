#include "task.displayanimator.h"
#include <avr/pgmspace.h>

const uint16_t DisplayAnimatorTask::animation_count = 20;
const uint8_t DisplayAnimatorTask::animation[][4] PROGMEM =
{
    { 0b00000000, 0b00000000, 0b00000000, 0b00000010 },
    { 0b00000000, 0b00000000, 0b00000000, 0b00000001 },
    { 0b00000000, 0b00000000, 0b00000001, 0b00000000 },
    { 0b00000000, 0b00000001, 0b00000000, 0b00000000 },
    { 0b00000001, 0b00000000, 0b00000000, 0b00000000 },
    { 0b00100000, 0b00000000, 0b00000000, 0b00000000 },

    { 0b01000000, 0b00000000, 0b00000000, 0b00000000 },
    { 0b00000000, 0b01000000, 0b00000000, 0b00000000 },
    { 0b00000000, 0b00000000, 0b01000000, 0b00000000 },
    { 0b00000000, 0b00000000, 0b00000000, 0b01000000 },

    { 0b00000000, 0b00000000, 0b00000000, 0b00000100 },
    { 0b00000000, 0b00000000, 0b00000000, 0b00001000 },
    { 0b00000000, 0b00000000, 0b00001000, 0b00000000 },
    { 0b00000000, 0b00001000, 0b00000000, 0b00000000 },
    { 0b00001000, 0b00000000, 0b00000000, 0b00000000 },
    { 0b00010000, 0b00000000, 0b00000000, 0b00000000 },

    { 0b01000000, 0b00000000, 0b00000000, 0b00000000 },
    { 0b00000000, 0b01000000, 0b00000000, 0b00000000 },
    { 0b00000000, 0b00000000, 0b01000000, 0b00000000 },
    { 0b00000000, 0b00000000, 0b00000000, 0b01000000 }
};


DisplayAnimatorTask::DisplayAnimatorTask(void)
:   _animation_index(0)
{}


DisplayAnimatorTask::FnBitMap DisplayAnimatorTask::operator()(void)
{
    ProgMemArray it(animation[_animation_index++], 4);
    _animation_index %= animation_count;

    return [it]() -> ProgMemArray { return it; };
}
