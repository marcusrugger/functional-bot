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

    Idleloop getIdleloop(void);


protected:

    virtual void subscribe(uint16_t time, Runnable task);

    Runnable    assembleDisplayAnimator(uint8_t Scl, uint8_t Sda);
    SinkUint16  assembleSegmentedDisplayDecimal(uint8_t scl, uint8_t sda);
    SinkUint16  assembleMatrixDisplayDecimal(uint8_t scl, uint8_t sda);
    Runnable    assembleMe4ButtonPanel(SourceUint16 source, Me4Button::PROCESSOR observer);

    MeLEDMatrixProtocol     createMeLEDMatrixProtocol(uint8_t Scl, uint8_t Sda);
    SegmentDisplayProtocol  createSegmentDisplayProtocol(uint8_t Scl, uint8_t Sda);


private:

    TaskRunner _scheduler;

};


#endif
