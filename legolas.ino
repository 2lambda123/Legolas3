#include "Flightdata.h"
#include "Bme280.h"

Flightdata flightdata; 

Bme280 bme280;

void setup() {
  Serial.begin(9600);
	bme280.init();
}

void loop() {
	unsigned long time = millis();

	if (!flightdata.isOnGround()) {
    Serial.println(flightdata.getTemp());
    Serial.println(flightdata.getAlt());
    Serial.println(flightdata.getPres());
    Serial.println(flightdata.getHum());
    Serial.println(flightdata.getBme280Status());
		bme280.flightProcess(flightdata, time);
	}
	else {
		bme280.groundProcess(flightdata, time);
	}

}
