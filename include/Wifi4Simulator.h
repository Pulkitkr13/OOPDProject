#ifndef WIFI4SIMULATOR_H
#define WIFI4SIMULATOR_H

#include "Simulator.h"
#include <vector>

class WiFi4Simulator : public Simulator {
public:
    WiFi4Simulator(int total_connected_Users, int bandwidth);

    void executeTest() override;

    double cal_throuhput(); 
};

#endif 
