#include "build.robotfabricator.h"
#include "controller.pin.h"
#include "protocol.segmentdisplay.h"
#include "task.runner.h"
#include "task.timer.h"
#include "task.displayanimator.h"


RobotFabricator::RobotFabricator(void)
{}


void RobotFabricator::buildDisplayAnimator(void)
{
    Serializer serializer(assembleDisplaySerializer(2, 8));
    Runnable animator(assembleDisplayAnimator(serializer));

    _scheduler.schedule(animator);
}


Serializer RobotFabricator::assembleDisplaySerializer(uint8_t Scl, uint8_t Sda)
{
    DigitalPin *pinScl = new ControllerDigitalPin(Scl, true);
    DigitalPin *pinSda = new ControllerDigitalPin(Sda, true);
    return SegmentDisplayProtocol(pinScl, pinSda);
}


Runnable RobotFabricator::assembleDisplayAnimator(Serializer serializer)
{
    DisplayAnimatorTask animator(serializer);
    return TaskTimer(100, animator);
}


Idleloop RobotFabricator::getIdleloop(void)
{
    return _scheduler;
}
