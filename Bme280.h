#pragma once

#include "Subsystem.h"
#include "Flightdata.h"
#include <Adafruit_BME280.h> //BME280 library

const unsigned long deltaTimeFlight = 1000; 
const unsigned long deltaTimeGround = 10000;

class Bme280:Subsystem {
public:
	void init();
	void test();
	void flightProcess(Flightdata& flightData, unsigned long time); 
	void groundProcess(Flightdata& flightData, unsigned long time);
	void teardown();
private:

	unsigned long totalDeltaTime = 0;
};
