#include "Flightdata.h"
#include "Bme280.h"
#include "Com.h"
#include "Gps.h"
#include "System.h"

Flightdata flightdata;

const int kGpsRxPin = 10;
const int kGpsTxPin = 11;

Bme280 bme280;
Com com;
Gps gps;
System mySystem;

void setup() {
	Serial.begin(9600);
	mySystem.init(flightdata);
	bme280.init();
	com.init();
	gps.init(kGpsRxPin, kGpsTxPin);
}

void loop() {
	if (!flightdata.isOnGround()) {
		bme280.flightProcess(flightdata, millis());
   	    com.flightProcess(flightdata, millis()); //DANGER, THIS SENDS A MESSAGE!
        gps.flightProcess(flightdata, millis());
	}
	else {
		bme280.groundProcess(flightdata, millis());
		com.groundProcess();
//        gps.groundProcess();
	}

}
