#include <Avionics.h>
#include <SoftwareSerial.h>
#include <IridiumSBD.h>

//constructor
Avionics::Avionics() {
	int readyCom = initCom();
	if (readyCom != 0) {
		//do something to tell people it's not ready
	}
}

//com methods
int Avionics::initCom() {
	SoftwareSerial nss(kPin_IRIDIUM_RX, kPin_IRIDIUM_TX);
	IridiumSBD isdb(nss, kPin_IRIDIUM_SLEEP);

	int signalQuality = -1; //I don't have to do anything in the header with this because it's inside a member?
	nss.begin(19200);
	isbd.begin();
	isbd.setPowerProfile(0);
}
void Avionics::demoCom(char message) {

}