#pragma once

#include "Subsystem.h"
#include "Flightdata.h" 
#include <Adafruit_INA219.h>

const unsigned long deltaTimeFlightSystem = 1000; 
const unsigned long deltaTimeGroundSystem = 1000;

class System:Subsystem {
public:
	void init();
	void test();
	void flightProcess(Flightdata& flightdata, unsigned long currTime);
	void groundProcess();
	void teardown();
private:
	unsigned long lastActionTime = 0;
};