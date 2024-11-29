#include "WiFi4Simulator.h"
#include <iostream>
#include <map>   // Use std::map for user backoff
#include <vector>
#include <algorithm>
#include <random>

// Constructor definition
WiFi4Simulator::WiFi4Simulator(int total_connected_Users, int bandwidth)
    : Simulator(total_connected_Users, bandwidth) {}

// Non-template function for throughput calculation (no arguments)
double WiFi4Simulator::cal_throuhput()
{
    if (timestamps.empty())
        return 0.0;

    double totalData = timestamps.size() * 8192;   // Total data in bits (1 KB = 8192 bits)
    double totalTime = timestamps.back() / 1000.0; // Total time in seconds
    return (totalData / totalTime) / 1e6;          // Throughput in Mbps
}

// Template function for throughput calculation (with container argument)
template <typename T>
double cal_throuhput_template(const std::vector<T>& timestamps)
{
    if (timestamps.empty())
        return 0.0;

    double totalData = timestamps.size() * 8192;   // Total data in bits (1 KB = 8192 bits)
    double totalTime = timestamps.back() / 1000.0; // Total time in seconds
    return (totalData / totalTime) / 1e6;          // Throughput in Mbps
}

// Explicit instantiation of the template function (for std::vector<double>)
template double cal_throuhput_template(const std::vector<double>& timestamps);

// Run simulation
void WiFi4Simulator::executeTest()
{
    std::cout << "\nWiFi 4 Simulation Started: CSMA/CA Protocol\n";

    // Random generator for backoff times
    std::mt19937 rng(std::random_device{}());
    std::uniform_real_distribution<> backoffDist(1.0, 10.0);

    double currentTime = 0.0;
    double transmissionTime = 0.0614; 

    
    std::map<int, double> userBackoff; 
    for (int i = 0; i < total_connected_Users; ++i)
    {
        userBackoff[i] = (i == 0) ? 0.0 : backoffDist(rng); 
    }

    
    latencies.clear();
    timestamps.clear();

    while (!userBackoff.empty())
    {
        
        auto minUser = std::min_element(userBackoff.begin(), userBackoff.end(),
                                        [](const auto& a, const auto& b)
                                        { return a.second < b.second; });

        currentTime = std::max(currentTime, minUser->second);
        std::cout << "User " << minUser->first << " started transmission at " << currentTime << " ms.\n";

        currentTime += transmissionTime;
        timestamps.push_back(currentTime);
        latencies.push_back(currentTime);
        std::cout << "User " << minUser->first << " finished transmission at " << currentTime << " ms.\n";

        
        userBackoff.erase(minUser);
    }

    
    std::cout << "\nResults:\n";
    std::cout << "Throughput: " << cal_throuhput() << " Mbps\n";     
    std::cout << "Avg_Latency: " << avglatency() << " ms\n"; 
    std::cout << "Max_Latency: " << maxlatency() << " ms\n";         

    std::cout << "\nTransmission Timestamps:\n";
    for (size_t i = 0; i < timestamps.size(); ++i)
    {
        std::cout << "Packet " << i + 1 << ": " << timestamps[i] << " ms\n";
    }
}