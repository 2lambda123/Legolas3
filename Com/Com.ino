#define HELLO       			0x80
#define MSG_WAITING 			0X81
#define READY       			0x82
#define TERMINATOR  			0x83
#define SUCCESS   				0x84
#define FAILURE                 0x85

#define IRIDIUM_OKAY			0
#define IRIDIUM_INACTIVE		1
#define IRIDIUM_LOW_SIGNAL 		2
#define IRIDIUM_SEND_FAILURE	3

#include <SoftwareSerial.h>
#include <IridiumSBD.h>

SoftwareSerial nssMFC(8, 9);
SoftwareSerial nssIridium(10, 11);
IridiumSBD isbd(nssIridium, 7);

int iridiumStatus = IRIDIUM_INACTIVE;

void iridiumTransmit(char* telemetry) {
	int signalQuality = -1;
	isbd.begin();
	iridiumStatus = IRIDIUM_OKAY;

	//establish signal
	int err = isbd.getSignalQuality(signalQuality);
	if (err != 0) {
		iridiumStatus = IRIDIUM_LOW_SIGNAL;
		Serial.print("Iridium signal error, code: ");
		Serial.println(err);
		return;
	}
	Serial.print("Signal quality: ");
	Serial.println(signalQuality); //!!! low signal quality doesn't stop it from sending?

	//send
	err = isbd.sendSBDText(telemetry);
	if (err != 0) {
		iridiumStatus = IRIDIUM_SEND_FAILURE;
		Serial.print("Iridium send failure, Iridium code ");
		Serial.print(err);
		return;
	}

	Serial.println("Iridium send success!");
	isbd.sleep();
}

void setup() {
	Serial.begin(9600); //for debug
	nssMFC.begin(9600); //talk to MFC
	nssIridium.begin(19200); //talk to RockBlock

	//configure Rockblock
	isbd.attachConsole(Serial);
	isbd.setPowerProfile(1);
	isbd.setMinimumSignalQuality(1);
	isbd.adjustSendReceiveTimeout(60);

}

void loop() {
	char rcvdString[340];
	unsigned int rcvdIndex = 0;
	bool newString = false; //true for string reset
	nssMFC.listen();
 
	while (!newString) {
		int currByte = nssMFC.read();
		if (currByte != -1) {
		  if (currByte == HELLO) { //okay for MFC send
				nssMFC.write(READY);
				Serial.println("Com starting");
				newString = true;
			}
			else if (currByte == TERMINATOR) { //done, prepare for new string
        		rcvdString[rcvdIndex] = 0; //null terminator
        		nssIridium.listen();
				iridiumTransmit(rcvdString);
				nssMFC.listen();
        		Serial.println("Telemetry message succesfully recieved: ");
        		Serial.print(rcvdString);
				if (iridiumStatus == IRIDIUM_OKAY) {
					nssMFC.write(SUCCESS);
				}
				else {
					nssMFC.write(FAILURE);
				}
				Serial.print("Iridium status: ");
				Serial.println(iridiumStatus);
				newString = true; //reset interaction
			}
			else if (rcvdIndex >= 340) { //prevent buffer overrun
				Serial.print("Buffer overrun prevented, ");
				Serial.println(rcvdIndex);
				nssMFC.write(FAILURE);
				newString = true; //reset interaction
			}
			else { //get the message
				rcvdString[rcvdIndex] = currByte;
				rcvdIndex += 1;
			}
		}
	}
}

