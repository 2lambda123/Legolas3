#include "System.h"

Adafruit_INA219 ina219;

void System::init(Flightdata& flightdata) {
   flightdata.logInit(12); //setup headers
   return;
}

void System::test() {
    return;
}

void System::flightProcess(Flightdata &flightdata, unsigned long currTime) {
	if ((lastActionTime + deltaTimeFlightSystem) <= currTime) {
		lastActionTime = currTime;

		float voltage = ina219.getBusVoltage_V();
		flightdata.setVolt(voltage);

	}
}

void System::groundProcess() {
    return;
}

void System::teardown() {
    return;
}
