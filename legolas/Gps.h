#ifndef LEGOLAS_GPS_H
#define LEGOLAS_GPS_H

#include "Subsystem.h"


class Gps:Subsystem {
    Public:
    void init();
    void test();
    void flightProcess(Flightdata& flightdata, unsigned long currTime);
    void groundProcess();
    void teardown()

};


#endif //LEGOLAS_GPS_H
