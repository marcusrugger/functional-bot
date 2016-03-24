#include "build.robotfabricator.h"
#include "controller.pin.h"
#include "hardware.me7segmentencoder.h"
#include "protocol.segmentdisplay.h"
#include "task.displayanimator.h"
#include "task.runner.h"
#include "task.timer.h"
#include "util.encoders.h"


RobotFabricator::RobotFabricator(void)
{}


void RobotFabricator::buildDisplayAnimator(void)
{
    Serializer serializer(assembleDisplaySerializer(2, 8));
    Runnable animator(assembleDisplayAnimator(serializer));

    _scheduler.schedule(animator);
}


void RobotFabricator::buildDisplayPin(void)
{
    Serializer serializer(assembleDisplaySerializer(2, 8));
    Runnable animator(assembleDisplayAnalogPin(A0, serializer));

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


Runnable RobotFabricator::assembleDisplayAnalogPin(uint8_t pinNumber, Serializer serializer)
{
    DecEncoder encoder(Me7SegmentEncoder::encodeDec, serializer);
    ControllerPin pin(pinNumber, INPUT);
    auto writer = [=]() mutable { encoder(pin.readPin()); };
    return TaskTimer(100, writer);
}


Idleloop RobotFabricator::getIdleloop(void)
{
    return _scheduler;
}
