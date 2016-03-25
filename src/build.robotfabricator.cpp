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
    _scheduler.schedule(animator);
}


void RobotFabricator::buildDisplayPin(void)
{
    Runnable pinwriter(assembleDisplayAnalogPin(A0, 2, 8));
    _scheduler.schedule(pinwriter);
}


Runnable RobotFabricator::assembleDisplayAnimator(uint8_t Scl, uint8_t Sda)
{
    DigitalPin *pinScl = new ControllerDigitalPin(Scl, true);
    DigitalPin *pinSda = new ControllerDigitalPin(Sda, true);
    SegmentDisplayProtocol serializer(pinScl, pinSda);

    DisplayAnimatorTask animator;
    auto runner = [=]() mutable { serializer(animator()); };
    return TaskTimer(100, runner);
}


Runnable RobotFabricator::assembleDisplayAnalogPin(uint8_t pinNumber, uint8_t Scl, uint8_t Sda)
{
    DigitalPin *pinScl = new ControllerDigitalPin(Scl, true);
    DigitalPin *pinSda = new ControllerDigitalPin(Sda, true);
    vl::Func<void(std::vector<uint8_t>)> serializer = SegmentDisplayProtocol(pinScl, pinSda);

    DecEncoder encoder(Me7SegmentEncoder::encodeDec);
    ControllerPin pin(pinNumber, INPUT);

    auto writer = [=]() mutable { serializer(encoder(pin.readPin())); };
    return TaskTimer(100, writer);
}


Idleloop RobotFabricator::getIdleloop(void)
{
    return _scheduler;
}
