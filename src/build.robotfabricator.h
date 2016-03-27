#ifndef BUILD_ROBOTFABRICATOR_H
#define BUILD_ROBOTFABRICATOR_H

#include "interfaces.h"
#include "task.runner.h"
#include <memory>

class TaskRunner;


class RobotFabricator : public BuildFabricator
{
public:

    RobotFabricator(void);

    void buildDisplayAnimator(void);
    void buildMatrixAnimator(void);
    void buildDisplayPin(void);

    Idleloop getIdleloop(void);


protected:

    void schedule(uint16_t time, Runnable task);

    Runnable   assembleDisplayAnimator(uint8_t Scl, uint8_t Sda);
    Runnable   assembleMatrixAnimator(uint8_t Scl, uint8_t Sda);
    Runnable   assembleDisplayAnalogPin(uint8_t pinNumber, uint8_t Scl, uint8_t Sda);
    Runnable   assembleMatrixDisplayAnalogPin(uint8_t pinNumber, uint8_t Scl, uint8_t Sda);


private:

    TaskRunner _scheduler;

};


#endif
