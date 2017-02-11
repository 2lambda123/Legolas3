#pragma once

#include "Subsystem.h"
#include "Flightdata.h"
#include <Adafruit_BME280.h> //BME280 library

#define SEALEVELPRESSURE_HPA (1013.25)

const unsigned long deltaTimeFlight = 1000; 
const unsigned long deltaTimeGround = 10000;

class Bme280:Subsystem {
public:
	void init();
	void test();
	void flightProcess(Flightdata& flightdata, unsigned long currTime); 
	void groundProcess(Flightdata& flightdata, unsigned long currTime);
	void teardown();
private:
	unsigned long lastActionTime = 0;
	void process(Flightdata& flightdata);
};
