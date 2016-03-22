#ifndef INTERFACES_H
#define INTERFACES_H

#include <Arduino.h>
#include <StandardCplusplus.h>
#include <Vlpp.h>


typedef vl::Func<void(void)> Idleloop;
typedef vl::Func<void(void)> Runnable;
typedef vl::Func<void(void)> Command;
typedef vl::Func<void(void)> Observer;


class BuildFabricator
{
public:

    virtual ~BuildFabricator(void) {}

    virtual void buildDisplayCounter(void) = 0;

    virtual Idleloop getIdleloop(void) = 0;
};


#endif
