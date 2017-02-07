#include <Flightdata.h>
#include <Bme280.h>

Flightdata flightdata; 

Bme280 bme280;

void setup() {
	bme280.init();
}

void loop() {
	unsigned long time = millis();

	if (!flightdata.isOnGround()) {
		bme280.flightProcess(time);
	}
	else {
		bme280.groundProcess();
	}

}
