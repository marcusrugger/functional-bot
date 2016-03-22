#include <StandardCplusplus.h>
#include <Vlpp.h>
#include "interfaces.h"
#include "build.robotfabricator.h"


Idleloop idleloop;


void createRobot(void)
{
    RobotFabricator fabricator;
    fabricator.buildDisplayCounter();
    idleloop = fabricator.getIdleloop();
}


void setup(void)
{
    Serial.begin(9600);
    createRobot();
    Serial.println("Exit setup");
}


void loop(void)
{
    idleloop();
}
