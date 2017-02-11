#include "Bme280.h"
#include <Adafruit_BME280.h> //BME280 library

Adafruit_BME280 bme;

void Bme280::init() {
	return;
}

void Bme280::test() {
	return;
}

void Bme280::flightProcess (Flightdata& flightdata, unsigned long currTime) {
	if ((lastActionTime + deltaTimeFlight) <= currTime) { 
		lastActionTime = currTime;

		process(flightdata);

    	//debug messages
	    Serial.println(flightdata.getTemp());
	    Serial.println(flightdata.getAlt());
	    Serial.println(flightdata.getPres());
	    Serial.println(flightdata.getHum());
	    Serial.println(flightdata.getBme280Status());
	}
}

void Bme280::groundProcess (Flightdata& flightdata, unsigned long currTime) {
	if ((lastActionTime + deltaTimeGround) <= currTime) {
		lastActionTime = currTime;

		process(flightdata);
	}
}

void Bme280::teardown() {
	return;
}

void Bme280::process(Flightdata& flightdata) {
	if (!bme.begin()) {
		flightdata.setBme280Status(1);
		return;
	}
	else {
		flightdata.setBme280Status(0);
	}
	flightdata.setTemp(bme.readTemperature());
	flightdata.setPres(bme.readPressure());
	flightdata.setAlt(bme.readAltitude(SEALEVELPRESSURE_HPA));
	flightdata.setHum(bme.readHumidity());
}
