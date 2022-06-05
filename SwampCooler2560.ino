#include "src/SwampCooler2560.h"
SwampCooler2560 sc;

void setup() 
{
	sc.begin();
}

void loop() 
{
	sc.update();
}
