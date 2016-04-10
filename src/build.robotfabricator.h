#ifndef BUILD_ROBOTFABRICATOR_H
#define BUILD_ROBOTFABRICATOR_H

#include "interfaces.h"
#include "subject.me4button.h"
#include "subject.me1button.h"
#include "task.runner.h"
#include <memory>

class TaskRunner;
class MeLEDMatrixProtocol;
class SegmentDisplayProtocol;


class RobotFabricator : public BuildFabricator
{
public:

    RobotFabricator(void);

    void buildDisplayAnimator(void);


protected:

    virtual void subscribe(uint16_t time, Runnable task) = 0;

    Runnable    assembleDisplayAnimator(uint8_t Scl, uint8_t Sda);
    SinkUint16  assembleSegmentedDisplayDecimal(uint8_t scl, uint8_t sda);
    SinkUint16  assembleSegmentedDisplayHex(uint8_t scl, uint8_t sda);
    SinkUint16  assembleMatrixDisplayDecimal(uint8_t scl, uint8_t sda);
    SinkUint16  assembleMatrixDisplayHex(uint8_t scl, uint8_t sda);
    Runnable    assembleMe4ButtonPanel(SourceUint16 source, Me4Button::OBSERVER observer);

    MeLEDMatrixProtocol     createMeLEDMatrixProtocol(uint8_t Scl, uint8_t Sda);
    SegmentDisplayProtocol  createSegmentDisplayProtocol(uint8_t Scl, uint8_t Sda);

};


#endif
