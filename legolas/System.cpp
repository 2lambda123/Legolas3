#include "System.h"

Adafruit_INA219 ina219;

void System::init(Flightdata& flightdata) {
	SD.begin(12);
	logFile = SD.open("log.csv", FILE_WRITE);
	logFile.println("col1, col2, col3, col4");
	logFile.close();
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
