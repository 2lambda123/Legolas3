#include "Com.h"

void Com::init () {
    Serial1.begin(115200);
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

        int success = sendToCom(telemetry);
        if (success == 0) {
            flightdata.setComStatus(0);
        }
        else {
            flightdata.setComStatus(1);
        }
	}

}

void Com::groundProcess() {
	return;
}

void Com::teardown() {
	return;
}

int Com::sendToCom(char* telemetry) {
    Serial1.write(HELLO);

    while (true) { //!!! DANGER DANGER VERY SCARY BAD CHANGE THIS SOON
        Serial.println("loooping in switch");
        Serial.println(Serial1.read());
        switch (Serial1.read()) {
            case READY:
                Serial1.write(telemetry);
                break;
            case SUCCESS:
                return 0;
            case FAILURE:
                return 1;
        }
        delay(5);
    }

}
