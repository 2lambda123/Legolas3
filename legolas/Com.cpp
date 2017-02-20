#include "Com.h"

void Com::init () {
	return;
}

void Com::test() {
	return;
}

void Com::flightProcess(Flightdata& flightdata, unsigned long currTime) {
	if ((lastActionTime + deltaTimeFlightCom) <= currTime) { 
		lastActionTime = currTime;

		//cast flightdata to string here because arduino sprintf doesn't work for floats/longs
		static char temp[15];
		static char pres[15];
		static char alt[15];
		static char hum[15];
		dtostrf(flightdata.getTemp(), 9, 2, temp);
		dtostrf(flightdata.getPres(), 9, 2, pres);
		dtostrf(flightdata.getAlt(), 9, 2, alt);
		dtostrf(flightdata.getHum(), 9, 2, hum);

		//combined flight data buffer sizes must be less then total telemetry buffer size
		char telemetry[340]; //max Iridium send size
		snprintf(telemetry, sizeof(telemetry), "Temp: %s\nPres: %s\nAlt:  %s\nHum:  %s\nBME280: %d\nCom: %d\n", 
				temp, pres, alt, hum, flightdata.getBme280Status(), flightdata.getComStatus());
		IridiumSBD isbd(Serial1, 30); //sleep pin 30
		Serial1.begin(19200);
    
		isbd.attachConsole(Serial);
		isbd.setPowerProfile(1);
		isbd.setMinimumSignalQuality(1);
		isbd.begin();

		int err = isbd.getSignalQuality(signalQuality);
		if (err != 0) {
			flightdata.setComStatus(1);
			Serial.print("Com.flightProcess error, Iridium code ");
			Serial.print(err);
			Serial.print(" status ");
			Serial.println(flightdata.getComStatus());
			return;
		}
		Serial.print("Signal quality: ");
		Serial.println(signalQuality); //!!! low signal quality doesn't stop it from sending?

		err = isbd.sendSBDText(telemetry);
		if (err != 0) {
			flightdata.setComStatus(1);
			Serial.print("Com.flightProcess error, Iridium code ");
			Serial.print(err);
			Serial.print(" status ");
			Serial.println(flightdata.getComStatus());
			return;
		}

		Serial.println("Send success!");

		flightdata.setComStatus(0);
		Serial.print("Com.flightProcess complete, status ");
		Serial.println(flightdata.getComStatus()); 
		
	}

}

void Com::groundProcess() {
	return;
}

void Com::teardown() {
	return;
}
