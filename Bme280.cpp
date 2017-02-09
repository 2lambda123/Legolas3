#include "Bme280.h"
#include <Adafruit_BME280.h> //BME280 library

#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BME280 bme;

void Bme280::init() {
	return;
}

void Bme280::test() {
	return;
}

void Bme280::flightProcess (Flightdata& flightData, unsigned long time) {
	if (time >= totalDeltaTime) { 
		totalDeltaTime += deltaTimeFlight;

		if (!bme.begin()) {
			flightData.setBme280Status(1);
			return;
		}
		else {
			flightData.setBme280Status(0);
		}

		flightData.setTemp(bme.readTemperature());
		flightData.setPres(bme.readPressure());
		flightData.setAlt(bme.readAltitude(SEALEVELPRESSURE_HPA));
		flightData.setHum(bme.readHumidity());
	}
}

void Bme280::groundProcess (Flightdata& flightData, unsigned long time) {
	if (time >= totalDeltaTime) {
		totalDeltaTime += deltaTimeGround;

		if (!bme.begin()) {
			flightData.setBme280Status(1);
			return;
		}
		else {
			flightData.setBme280Status(0);
		}

		flightData.setTemp(bme.readTemperature()); 
		flightData.setPres(bme.readPressure());
		flightData.setAlt(bme.readAltitude(SEALEVELPRESSURE_HPA));
		flightData.setHum(bme.readHumidity());
	}
}

void Bme280::teardown() {
	return;
}
