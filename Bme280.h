#include <Subsystem.h>

class Bme280:Subsystem {
public:
	void init();
	void test();
	void flightProcess(&flightData, unsigned long time); //!!! do a reference thingy
	void groundProcess(&flightData, unsigned long time);
	void teardown();
private:
	unsigned long deltaTimeFlight = 100; 
	unsigned long deltaTimeGround = 10000;
	unsigned long totalDeltaTime = 0;
}