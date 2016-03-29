#include "build.robotfabricator.h"
#include "controller.pin.h"
#include "hardware.me7segmentencoder.h"
#include "hardware.meledmatrixencoder.h"
#include "protocol.segmentdisplay.h"
#include "protocol.meledmatrix.h"
#include "task.displayanimator.h"
#include "task.runner.h"
#include "task.timer.h"
#include "util.encoders.h"


MeLEDMatrixProtocol RobotFabricator::createMeLEDMatrixProtocol(uint8_t Scl, uint8_t Sda)
{
    DigitalPin *pinScl = new ControllerDigitalPin(Scl);
    DigitalPin *pinSda = new ControllerDigitalPin(Sda);
    return MeLEDMatrixProtocol(pinScl, pinSda);
}


SegmentDisplayProtocol RobotFabricator::createSegmentDisplayProtocol(uint8_t Scl, uint8_t Sda)
{
    DigitalPin *pinScl = new ControllerDigitalPin(Scl);
    DigitalPin *pinSda = new ControllerDigitalPin(Sda);
    return SegmentDisplayProtocol(pinScl, pinSda);
}


RobotFabricator::RobotFabricator(void)
{}


void RobotFabricator::buildDisplayAnimator(void)
{
    Runnable animator(assembleDisplayAnimator(2, 8));
    subscribe(100, animator);
}


void RobotFabricator::buildMatrixAnimator(void)
{
    Runnable animator(assembleMatrixAnimator(12, 13));
    subscribe(100, animator);
}


void RobotFabricator::buildDisplayPin(void)
{
    Runnable pinwriter(assembleDisplayAnalogPin(A0, 2, 8));
    subscribe(100, pinwriter);
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
    ControllerPin pin(pinNumber);

    return [=]() mutable { serializer(encoder(pin.readPin())); };
}


Runnable RobotFabricator::assembleMatrixDisplayAnalogPin(uint8_t pinNumber, uint8_t Scl, uint8_t Sda)
{
    SegmentDisplayProtocol serializer1(createSegmentDisplayProtocol(2, 8));
    DecEncoder encoder1(Me7SegmentEncoder::encodeDec);

    MeLEDMatrixProtocol serializer2(createMeLEDMatrixProtocol(Scl, Sda));
    MatrixDecEncoder encoder2(MeLEDMatrixEncoder::encodeDec);

    ControllerPin pin(pinNumber);

    return [=]() mutable
    {
        uint16_t pinValue = pin.readPin();
        serializer1(encoder1(pinValue));
        serializer2(encoder2(pinValue));
    };
}


void RobotFabricator::subscribe(uint16_t time, Runnable task)
{
    TaskTimer timer(time, task);
    _scheduler.subscribe(timer);
}


Idleloop RobotFabricator::getIdleloop(void)
{
    return _scheduler;
}
