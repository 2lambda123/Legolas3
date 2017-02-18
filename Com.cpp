#include "Com.h"

void Com::init () {
	return;
}

//test not currently useful/necessarily working
void Com::test() {
	IridiumSBD isbd(Serial1, 30); //sleep pin 30
	Serial1.begin(19200);

	isbd.attachConsole(Serial);
	isbd.setPowerProfile(1);
  isbd.adjustSendReceiveTimeout(15); //15 second timeout vs default 300
	int hasBegun = isbd.begin();
	Serial.print("isbd.begin status: ");
	Serial.println(hasBegun);

	int err = isbd.getSignalQuality(signalQuality);
	if (err != 0) {
		Serial.print("SignalQuality failed: error ");
		Serial.println(err);
		return;
	}
	Serial.print("Signal quality: ");
	Serial.println(signalQuality);
/*
	err = isbd.sendSBDText("Hello, world!");
	if (err != 0) {
		Serial.print("sendSBDText failed: error ");
		Serial.println(err);
		return;
	}

	Serial.println("Send success!");
*/
}

void Com::flightProcess(Flightdata& flightdata, unsigned long currTime) {
	if ((lastActionTime + deltaTimeFlightCom) <= currTime) { 
		lastActionTime = currTime;

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

		err = isbd.sendSBDText(flightdataToChar(flightdata, currTime));
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

char Com::flightdataToChar(Flightdata& flightdata, unsigned long currTime) {
	char charSeparator = reinterpret_cast<char>(", "); //!!! how should this really be done?
  
	char sysTime = static_cast<char>(currTime);							
	char temp = static_cast<char>(flightdata.getTemp());
	char pres = static_cast<char>(flightdata.getPres());
	char alt = static_cast<char>(flightdata.getAlt());
	char hum = static_cast<char>(flightdata.getHum());
	char message = sysTime + charSeparator + temp + charSeparator + pres + charSeparator + alt; //pretty sure there's a better was than separator
  return message;
}
