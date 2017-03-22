#pragma once

#define HELLO       			0x80
#define MSG_WAITING 			0X81
#define READY       			0x82
#define TERMINATOR  			0x83
#define SUCCESS   				0x84
#define FAILURE					0x85

#include "Subsystem.h"
#include "Flightdata.h"
#include <IridiumSBD.h> 


const unsigned long deltaTimeFlightCom = 10000; 
const unsigned long deltaTimeGroundCom = 1000000;

class Com:Subsystem {
public:
	void init();
	void test();
	void flightProcess(Flightdata& flightdata, unsigned long currTime);
	void groundProcess();
	void teardown();
private:
	int signalQuality = -1;
	unsigned long lastActionTime = 0;
	int sendToCom(char* telemetry);
  void packetWrite(char* telemetry);

};

