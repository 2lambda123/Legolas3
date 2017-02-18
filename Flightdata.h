#pragma once

#define OKAY			0
#define ERR_GENERAL		1

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

	//////////SYSTEM STATE//////////
	bool isOnGround() {
		return false;
		//!!! add logic later, maybe it makes sense to have an isOnGround bool that is periodically
		//updated rather than going through the logic each iteration. Is on ground can be checked once
		//every 10 seconds or so
	}

	//////////SUBSYSTEM STATUS//////////
	int getBme280Status() {
		return Bme280Status;
	}
	int getComStatus() {
		return comStatus;
	}

	void setBme280Status(int status) {
		Bme280Status = status;
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

	//////////SUBSYSTEM STATUS//////////
	int Bme280Status = 0;
	int comStatus = 0;
};
