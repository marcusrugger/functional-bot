#include "build.robotfabricator.h"
#include "controller.pin.h"
#include "hardware.me7segmentencoder.h"
#include "protocol.segmentdisplay.h"
#include "protocol.meledmatrix.h"
#include "task.displayanimator.h"
#include "task.runner.h"
#include "task.timer.h"
#include "util.encoders.h"


static MeLEDMatrixProtocol createMeLEDMatrixProtocol(uint8_t Scl, uint8_t Sda)
{
    DigitalPin *pinScl = new ControllerDigitalPin(Scl, true);
    DigitalPin *pinSda = new ControllerDigitalPin(Sda, true);
    return MeLEDMatrixProtocol(pinScl, pinSda);
}


static SegmentDisplayProtocol createSegmentDisplayProtocol(uint8_t Scl, uint8_t Sda)
{
    DigitalPin *pinScl = new ControllerDigitalPin(Scl, true);
    DigitalPin *pinSda = new ControllerDigitalPin(Sda, true);
    return SegmentDisplayProtocol(pinScl, pinSda);
}


RobotFabricator::RobotFabricator(void)
{}


void RobotFabricator::buildDisplayAnimator(void)
{
    Runnable animator(assembleDisplayAnimator(2, 8));
    schedule(100, animator);
}


void RobotFabricator::buildMatrixAnimator(void)
{
    Runnable animator(assembleMatrixAnimator(12, 13));
    schedule(100, animator);
}


void RobotFabricator::buildDisplayPin(void)
{
    Runnable pinwriter(assembleDisplayAnalogPin(A0, 2, 8));
    schedule(100, pinwriter);
}


Runnable RobotFabricator::assembleDisplayAnimator(uint8_t Scl, uint8_t Sda)
{
    SegmentDisplayProtocol serializer(createSegmentDisplayProtocol(Scl, Sda));
    DisplayAnimatorTask animator;

    return [=]() mutable { serializer(animator()); };
}


Runnable RobotFabricator::assembleMatrixAnimator(uint8_t Scl, uint8_t Sda)
{
    MeLEDMatrixProtocol serializer(createMeLEDMatrixProtocol(Scl, Sda));
    DisplayAnimatorTask animator;

    return [=]() mutable { serializer(animator()); };
}


Runnable RobotFabricator::assembleDisplayAnalogPin(uint8_t pinNumber, uint8_t Scl, uint8_t Sda)
{
    SegmentDisplayProtocol serializer(createSegmentDisplayProtocol(Scl, Sda));
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
