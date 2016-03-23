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

    Idleloop getIdleloop(void);


private:

    TaskRunner _scheduler;

    Serializer assembleDisplaySerializer(uint8_t Scl, uint8_t Sda);
    Runnable   assembleDisplayAnimator(Serializer serializer);

};


#endif
