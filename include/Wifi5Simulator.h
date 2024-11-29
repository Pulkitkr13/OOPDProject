#ifndef WIFI5SIMULATOR_H
#define WIFI5SIMULATOR_H

#include "Simulator.h"
#include <vector>

class WiFi5Simulator : public Simulator {
public:
    WiFi5Simulator(int total_connected_Users, int bandwidth);

    void executeTest() override;

    double cal_throuhput(int totalPackets, double totalTime);
    double avglatency();
    double maxlatency();
};

#endif
