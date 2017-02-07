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

	void setTemp(double temp) {
		fTemp = temp;
	}
	void setPres(double pres) {
		fPres = pres;
	}
	void setAlt() {
		fAlt = alt;
	}
	void setHum(double hum) {
		fHum = hum;
	}

	//////////SYSTEM STATE//////////
	bool isOnGround() {
		return false;
		//!!! add logic later
	}

	//////////SUBSYSTEM STATUS//////////
	int getBme280Status() {
		return Bme280Status;
	}

	void setBme280Status(int status) {
		Bme280Status = status;
	}
private:
	//////////SENSOR DATA//////////
	float fTemp = 0;
	float fPres = 0;
	float fAlt = 0;
	float fHum = 0;

	//////////SUBSYSTEM STATUS//////////
	int Bme280Status = 0;
}