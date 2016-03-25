#include <StandardCplusplus.h>
#include <functional-vlpp.h>
#include "interfaces.h"
#include "build.robotfabricator.h"


static Idleloop idleloop;


static void createAnimator(BuildFabricator &fabricator)
{
    fabricator.buildDisplayAnimator();
}


static void createWeatherStation(BuildFabricator &fabricator)
{
    fabricator.buildDisplayPin();
}


void setup(void)
{
    Serial.begin(9600);

    RobotFabricator fabricator;
    createWeatherStation(fabricator);
    idleloop = fabricator.getIdleloop();

    Serial.println("Setup complete");
}


void loop(void)
{
    idleloop();
}
