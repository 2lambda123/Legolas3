#include <Bme280.h>
#include <Adafruit_BME280.h> //BME280 library

#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BME280 bme;

void init() {
	return;
}

void test() {
	return;
}

void flightProcess (&flightData, unsigned long time) {
	if (time >= totalDeltaTime) { //!!! how to deal with members?
		totalDeltaTime += deltaTimeFlight

		if (!bme.begin()) {
			flightData.setBme280Status(1);
			return;
		}
		else {
			flightData.setBme280Status(0);
		}

		flightData.setTemp(bme.readTemperature()); //!!! flightData.method okay for how it's passed in?
		flightData.setPres(bme.readPressure());
		flightData.setAlt(bme.readAltitude(SEALEVELPRESSURE_HPA));
		flightData.setHum(bme.readHumidity());
	}
}

void groundProcess (&flightData, unsigned long time) {
	if (time >= totalDeltaTime) { //!!! again, how to deal with members
		totalDeltaTime += deltaTimeGround

		if (!bme.begin()) {
			flightData.setBme280Status(1);
			return;
		}
		else {
			flightData.setBme280Status(0);
		}

		flightData.setTemp(bme.readTemperature()); //!!! same as above in flightProcess
		flightData.setPres(bme.readPressure());
		flightData.setAlt(bme.readAltitude(SEALEVELPRESSURE_HPA));
		flightData.setHum(bme.readHumidity());
	}
}