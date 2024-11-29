#include "Simulator.h"
#include <algorithm>
#include <numeric>

Simulator::Simulator(int total_connected_Users, int bandwidth)
    : total_connected_Users(total_connected_Users), bandwidth(bandwidth) {}

double Simulator::cal_throuhput()
{
    if (timestamps.empty())
        return 0.0;

    double totalData = timestamps.size() * 1.0;      // 1 KB per packet
    double totalTime = timestamps.back();            // Total time in ms
    return (totalData * 8.0) / (totalTime / 1000.0); // Mbps
}

double Simulator::avglatency() // 

{
    if (latencies.empty())
        return 0.0;

    double totalLatency = std::accumulate(latencies.begin(), latencies.end(), 0.0); // A
    return totalLatency / latencies.size();
}

double Simulator::maxlatency() // 
{
    if (latencies.empty())
        return 0.0;

    return *std::max_element(latencies.begin(), latencies.end()); // P
}
