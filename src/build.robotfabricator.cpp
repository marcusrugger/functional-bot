#include "build.robotfabricator.h"
#include "task.runner.h"
#include "task.timer.h"


RobotFabricator::RobotFabricator(void)
:   _scheduler(new TaskRunner())
{}


void RobotFabricator::buildDisplayCounter(void)
{
    Runnable runner = [](){ Serial.println("Hello world"); };
    TaskTimer *timer = new TaskTimer(1000, runner);
    _scheduler->schedule(*timer);
}


Idleloop RobotFabricator::getIdleloop(void)
{
    return *_scheduler;
}
