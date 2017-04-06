#include "Com.h"

void Com::init() {
    Serial1.begin(9600);
}

void Com::test() {
	return;
}

void Com::flightProcess(Flightdata& flightdata, unsigned long currTime) {
	if ((lastActionTime + deltaTimeFlightCom) <= currTime) {
		lastActionTime = currTime;
		
        char telemetry = flightdata.getStrFlightdata();
        
        Serial.println(telemetry);
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

int Com::sendToCom(char *telemetry) {
    Serial1.write(HELLO);
    int startTime = millis();
    const int kTimeout = 500;
    while (millis() < startTime + kTimeout) {
        int serialByte = Serial1.read(); // try an int for now; need the signed capacity
        switch (serialByte) {
            case READY:
                Serial.println("Sending...");
                packetWrite(telemetry);
                Serial1.write(TERMINATOR);
                Serial.println("Finished sending...");
                break;
            case SUCCESS:
                Serial.println("Success");
                return 0;
            case FAILURE:
                Serial.println("Failure");
                return 1;
        }
        delay(5);
    }
    Serial.println("Timeout error");
    return 1;  // Timeout error
}


void Com::packetWrite(char* telemetry) {
    int telemLength = strlen(telemetry);
    int numPackets = telemLength / 50 + 1; //problem if divides % 0
    int telemetryIndex = 0;
    for (int i = 0; i < numPackets; i++) {
        char currPacket[51];
        int j;
        for (j = 0; j < 50 && (telemetryIndex < telemLength); j++) {
            currPacket[j] = telemetry[telemetryIndex];
            telemetryIndex++;
        }
        currPacket[j] = '\0'; //terminator
        Serial1.write(currPacket);
    }
}
