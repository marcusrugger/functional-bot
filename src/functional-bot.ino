#include <StandardCplusplus.h>
#include <Vlpp.h>
#include "interfaces.h"
#include "build.robotfabricator.h"


static Idleloop idleloop;


static void createRobot(BuildFabricator &fabricator)
{
    fabricator.buildDisplayAnimator();
}


void setup(void)
{
    Serial.begin(9600);

    RobotFabricator fabricator;
    createRobot(fabricator);
    idleloop = fabricator.getIdleloop();

    Serial.println("Setup complete");
}


void loop(void)
{
    idleloop();
}
