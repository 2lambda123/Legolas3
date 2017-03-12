#include "Flightdata.h"
#include "Bme280.h"
#include "Com.h"
#include "Gps.h"

Flightdata flightdata; 

Bme280 bme280;
Com com;
Gps gps;

void setup() {
	Serial.begin(9600);
	bme280.init();
	com.init();
    gps.init();
}

void loop() {
	unsigned long currTime = millis();

	if (!flightdata.isOnGround()) {
		bme280.flightProcess(flightdata, currTime);
   	    com.flightProcess(flightdata, currTime); //DANGER, THIS SENDS A MESSAGE!
        gps.groundProcess();
	}
	else {
		bme280.groundProcess(flightdata, currTime);
		com.groundProcess();
        gps.groundProcess();
	}

}
