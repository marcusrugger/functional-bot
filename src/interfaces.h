#ifndef INTERFACES_H
#define INTERFACES_H

#include <Arduino.h>
#include <StandardCplusplus.h>
#include <Vlpp.h>


using Idleloop = vl::Func<void(void)>;
using Runnable = vl::Func<void(void)>;
using Command  = vl::Func<void(void)>;
using Observer = vl::Func<void(void)>;


class BuildFabricator
{
public:

    virtual ~BuildFabricator(void) {}

    virtual void buildDisplayCounter(void) = 0;

    virtual Idleloop getIdleloop(void) = 0;
};


#endif
