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
    DigitalPin pinScl(Scl);
    DigitalPin pinSda(Sda);
    return MeLEDMatrixProtocol(pinScl, pinSda);
}


SegmentDisplayProtocol RobotFabricator::createSegmentDisplayProtocol(uint8_t Scl, uint8_t Sda)
{
    DigitalPin pinScl(Scl);
    DigitalPin pinSda(Sda);
    return SegmentDisplayProtocol(pinScl, pinSda);
}


RobotFabricator::RobotFabricator(void)
{}


void RobotFabricator::buildDisplayAnimator(void)
{
    Runnable animator(assembleDisplayAnimator(2, 8));
    subscribe(100, animator);
}


Runnable RobotFabricator::assembleDisplayAnimator(uint8_t Scl, uint8_t Sda)
{
    SegmentDisplayProtocol serializer(createSegmentDisplayProtocol(Scl, Sda));
    DisplayAnimatorTask animator;

    return [=]() mutable { serializer(animator()); };
}


SinkUint16 RobotFabricator::assembleSegmentedDisplayDecimal(uint8_t scl, uint8_t sda)
{
    SegmentDisplayProtocol serialize(createSegmentDisplayProtocol(scl, sda));
    DecEncoder encode(Me7SegmentEncoder::encodeDec);

    return [=](uint16_t value) mutable { serialize(encode(value)); };
}


SinkUint16 RobotFabricator::assembleMatrixDisplayDecimal(uint8_t scl, uint8_t sda)
{
    MeLEDMatrixProtocol serialize(createMeLEDMatrixProtocol(scl, sda));
    MatrixDecEncoder encode(MeLEDMatrixEncoder::encodeDec);

    return [=](uint16_t value) mutable { serialize(encode(value)); };
}


Runnable RobotFabricator::assembleMe4ButtonPanel(SourceUint16 source, Me4Button::PROCESSOR observer)
{
    Me4ButtonSubject setButtonState(observer);

    return [=](void) mutable { setButtonState(Me4Button::translatePin(source())); };
}


void RobotFabricator::subscribe(uint16_t time, Runnable task)
{
    _scheduler.subscribe( TaskTimer(time, task) );
}


Idleloop RobotFabricator::getIdleloop(void)
{
    return _scheduler;
}
