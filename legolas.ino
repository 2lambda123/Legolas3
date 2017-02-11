#include "Flightdata.h"
#include "Bme280.h"

Flightdata flightdata; 

Bme280 bme280;

void setup() {
	Serial.begin(9600);
	bme280.init();
}

void loop() {
	unsigned long currTime = millis();

	if (!flightdata.isOnGround()) {
		bme280.flightProcess(flightdata, currTime);
	}
	else {
		bme280.groundProcess(flightdata, currTime);
	}

}
