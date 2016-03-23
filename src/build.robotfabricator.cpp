#include "build.robotfabricator.h"
#include "controller.pin.h"
#include "protocol.segmentdisplay.h"
#include "task.runner.h"
#include "task.timer.h"
#include "task.displayanimator.h"


RobotFabricator::RobotFabricator(void)
:   _scheduler(new TaskRunner())
{}


void RobotFabricator::buildDisplayCounter(void)
{
    Serializer serializer = buildDisplaySerializer(2, 8);
    Runnable   animator   = buildDisplayAnimator(serializer);

    _scheduler->schedule(animator);
}


Serializer RobotFabricator::buildDisplaySerializer(uint8_t Scl, uint8_t Sda)
{
    DigitalPin *pinScl = new ControllerDigitalPin(Scl, true);
    DigitalPin *pinSda = new ControllerDigitalPin(Sda, true);
    SegmentDisplayProtocol *serializer = new SegmentDisplayProtocol(pinScl, pinSda);
    return *serializer;
}


Runnable RobotFabricator::buildDisplayAnimator(Serializer serializer)
{
    DisplayAnimatorTask *animator = new DisplayAnimatorTask(serializer);
    TaskTimer *timer = new TaskTimer(100, *animator);
    return *timer;
}


Idleloop RobotFabricator::getIdleloop(void)
{
    return *_scheduler;
}
