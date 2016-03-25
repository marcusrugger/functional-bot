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
    Runnable animator(assembleDisplayAnimator(2, 8));
    schedule(100, animator);
}


void RobotFabricator::buildDisplayPin(void)
{
    Runnable pinwriter(assembleDisplayAnalogPin(A0, 2, 8));
    schedule(100, pinwriter);
}


Runnable RobotFabricator::assembleDisplayAnimator(uint8_t Scl, uint8_t Sda)
{
    DigitalPin *pinScl = new ControllerDigitalPin(Scl, true);
    DigitalPin *pinSda = new ControllerDigitalPin(Sda, true);
    SegmentDisplayProtocol serializer(pinScl, pinSda);

    DisplayAnimatorTask animator;
    return [=]() mutable { serializer(animator()); };
}


Runnable RobotFabricator::assembleDisplayAnalogPin(uint8_t pinNumber, uint8_t Scl, uint8_t Sda)
{
    DigitalPin *pinScl = new ControllerDigitalPin(Scl, true);
    DigitalPin *pinSda = new ControllerDigitalPin(Sda, true);
    SegmentDisplayProtocol serializer(pinScl, pinSda);

    DecEncoder encoder(Me7SegmentEncoder::encodeDec);
    ControllerPin pin(pinNumber, INPUT);

    return [=]() mutable { serializer(encoder(pin.readPin())); };
}


void RobotFabricator::schedule(uint16_t time, Runnable task)
{
    TaskTimer timer(time, task);
    _scheduler.schedule(timer);
}


Idleloop RobotFabricator::getIdleloop(void)
{
    return _scheduler;
}
