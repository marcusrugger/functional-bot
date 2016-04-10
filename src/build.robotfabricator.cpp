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
    return MeLEDMatrixProtocol(DigitalPin(Scl), DigitalPin(Sda));
}


SegmentDisplayProtocol RobotFabricator::createSegmentDisplayProtocol(uint8_t Scl, uint8_t Sda)
{
    return SegmentDisplayProtocol(DigitalPin(Scl), DigitalPin(Sda));
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


SinkUint16 RobotFabricator::assembleSegmentedDisplayHex(uint8_t scl, uint8_t sda)
{
    SegmentDisplayProtocol serialize(createSegmentDisplayProtocol(scl, sda));
    HexEncoder encode(Me7SegmentEncoder::encodeHex);

    return [=](uint16_t value) mutable { serialize(encode(value)); };
}


SinkUint16 RobotFabricator::assembleMatrixDisplayDecimal(uint8_t scl, uint8_t sda)
{
    MeLEDMatrixProtocol serialize(createMeLEDMatrixProtocol(scl, sda));
    MatrixDecEncoder encode(MeLEDMatrixEncoder::encodeDec);

    return [=](uint16_t value) mutable { serialize(encode(value)); };
}


SinkUint16 RobotFabricator::assembleMatrixDisplayHex(uint8_t scl, uint8_t sda)
{
    MeLEDMatrixProtocol serialize(createMeLEDMatrixProtocol(scl, sda));
    MatrixHexEncoder encode(MeLEDMatrixEncoder::encodeHex);

    return [=](uint16_t value) mutable { serialize(encode(value));  };
}


Runnable RobotFabricator::assembleMe4ButtonPanel(SourceUint16 source, Me4Button::OBSERVER observer)
{
    Me4ButtonSubject setButtonState(observer);

    return [=](void) mutable { setButtonState(Me4Button::translatePin(source())); };
}
