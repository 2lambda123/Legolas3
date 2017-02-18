#pragma once

#include "Subsystem.h"
#include "Flightdata.h"
#include <IridiumSBD.h> 


const unsigned long deltaTimeFlightCom = 180000; 
const unsigned long deltaTimeGroundCom = 1000000;

class Com:Subsystem {
public:
	void init();
	void test();
	void flightProcess(Flightdata& flightdata, unsigned long currTime);
	void groundProcess();
	void teardown();
private:
	int signalQuality = -1;
	unsigned long lastActionTime = 0;
	char flightdataToChar(Flightdata& flightdata, unsigned long currTime);
};
