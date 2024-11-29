#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <vector>

class Simulator
{
protected:
    int total_connected_Users;
    int bandwidth;
    std::vector<double> latencies;
    std::vector<double> timestamps;

public:
    Simulator(int total_connected_Users, int bandwidth); 

    virtual void executeTest() = 0;
    virtual double cal_throuhput();

    double cal_throuhput(int totalPackets, double totalTime)
    {
        double totalData = totalPackets * 1.0; 
        double store = (totalData * 8.0) / (totalTime / 1000.0);

        return store;
    }

    double avglatency();
    double maxlatency();
};

#endif
