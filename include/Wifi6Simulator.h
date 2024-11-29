#ifndef WIFI6SIMULATOR_H
#define WIFI6SIMULATOR_H

#include "Simulator.h"
#include <vector>

class WiFi6Simulator : public Simulator
{
public:
    WiFi6Simulator(int total_connected_Users, int bandwidth);
    void executeTest() override;
    double cal_throuhput(); 

    
    double avglatency();
    double maxlatency();

private:
    int subChannelWidth; 
    double dataRate;    
};

#endif
