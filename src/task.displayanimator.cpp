#include "task.displayanimator.h"


const uint16_t animation_count = 20;
const uint8_t animation[][4] =
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


Array<uint8_t> DisplayAnimatorTask::operator()(void)
{
    Array<uint8_t> it(animation[_animation_index++], 4);
    _animation_index %= animation_count;
    return it;
}
