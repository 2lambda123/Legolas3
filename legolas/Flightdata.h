#pragma once

#define OKAY			0
#define ERR_GENERAL		1

/*#include <stdlib.h>
#include <stdio.h>*/
#include <IridiumSBD.h> //!!stdio seems to break serial, isbd works in the interim
#include <SD.h>

class Flightdata {
public:
	//////////SENSOR DATA//////////
	float getTemp() {
		return fTemp;
	}
	float getPres() {
		return fPres;
	}
	float getAlt() {
		return fAlt;
	}
	float getHum() {
		return fHum;
	}
	float getVolt() {
		return fVolt;
	}

	void setTemp(float temp) {
		fTemp = temp;
	}
	void setPres(float pres) {
		fPres = pres;
	}
	void setAlt(float alt) {
		fAlt = alt;
	}
	void setHum(float hum) {
		fHum = hum;
	}
	void setVolt(float volt) {
		fVolt = volt;
	}

	//////////UTILITIES//////////
	bool isOnGround() {
		return false;
		//!!! add logic later, maybe it makes sense to have an isOnGround bool that is periodically
		//updated rather than going through the logic each iteration. Is on ground can be checked once
		//every 10 seconds or so
	}
	char* getStrFlightdata() {
		static char temp[15];
		static char pres[15];
		static char alt[15];
		static char hum[15];
		static char volt[15];
		dtostrf(fTemp, 9, 2, temp);
		dtostrf(fPres, 9, 2, pres);
		dtostrf(fAlt, 9, 2, alt);
		dtostrf(fHum, 9, 2, hum);
		dtostrf(fVolt, 9, 2, volt);

        char flightdata[340]; //max Iridium send size
        snprintf(flightdata, sizeof(flightdata), "Temp: %s\nPres: %s\nAlt:  %s\nHum:  %s\nVolt: %s\nBME280: %d\nCom: %d\n",
                temp, pres, alt, hum, volt, bme280Status, comStatus);

        return flightdata;
	}

   void logInit(int pin) {
      SD.begin(pin);
      File logFile = SD.open("log.csv", FILE_WRITE);
      logFile.println("head1, head2, head3, head4");
      logFile.close();
   }

	void log() {
		File logFile = SD.open("log.csv", FILE_WRITE);
		logFile.println("new1, new2, new3, new4");
		logFile.close();

	}
	void log(char* data){
      File logFile = SD.open("log.csv", FILE_WRITE);
      logFile.println(data);
      logFile.close();
	}

	//////////SUBSYSTEM STATUS//////////
	int getBme280Status() {
		return bme280Status;
	}
	int getComStatus() {
		return comStatus;
	}

	void setBme280Status(int status) {
		bme280Status = status;
	}
	int setComStatus(int status) {
		comStatus = status;
	}
private:
	//////////SENSOR DATA//////////
	float fTemp = 0;
	float fPres = 0;
	float fAlt = 0;
	float fHum = 0;
	float fVolt = 0;

	//////////SUBSYSTEM STATUS//////////
	int bme280Status = 0;
	int comStatus = 0;
};
