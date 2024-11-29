#include "WiFi6Simulator.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <stdexcept>
#include <numeric> 

WiFi6Simulator::WiFi6Simulator(int total_connected_Users, int bandwidth)
    : Simulator(total_connected_Users, bandwidth), subChannelWidth(4), dataRate(133.33) 
{
}

double WiFi6Simulator::cal_throuhput()
{
    if (latencies.empty())
        return 0.0;

    double totalData = latencies.size() * 8192.0;    
    double totalTime = timestamps.back();            
    return (totalData / (totalTime / 1000.0)) / 1e6; 
}

void WiFi6Simulator::executeTest()
{
    std::cout << "\n--=----*** WiFi6 OFDMA Simulation ***-------\n";

    
    int userInputSubChannelWidth;
    std::cout << "Enter sub-channel width (2Mhz, 4MHz, or 10 MHz): ";
    std::cin >> userInputSubChannelWidth;

    
    if (userInputSubChannelWidth != 2 && userInputSubChannelWidth != 4 && userInputSubChannelWidth != 10)
    {
        throw std::invalid_argument("Only 2, 4, or 10 MHz are allowed.");
    }
    subChannelWidth = userInputSubChannelWidth;

    int numSubChannels = bandwidth / subChannelWidth;                            
    double dataRatePerSubChannel = (dataRate * subChannelWidth) / 20.0;          
    double transmissionTime = (8192.0 / (dataRatePerSubChannel * 1e6)) * 1000.0; 

    if (dataRatePerSubChannel <= 0)
    {
        std::cerr << "Error: Data rate per subchannel is invalid. Exiting simulation.\n";
        return;
    }

    std::cout << "Total Bandwidth: " << bandwidth << " MHz\n";
    std::cout << "Sub-channel Width: " << subChannelWidth << " MHz\n";
    std::cout << "Number of Sub-channels: " << numSubChannels << "\n";
    std::cout << "Transmission Time per Packet: " << std::fixed << std::setprecision(4) << transmissionTime << " ms\n\n";

    latencies.clear();
    timestamps.clear();

    int remainingUsers = total_connected_Users;
    double currentTime = 0.0;

    while (remainingUsers > 0)
    {
        std::cout << " Starting Frame at " << currentTime << " ms ---\n";

        int usersThisFrame = std::min(numSubChannels, remainingUsers);
        for (int i = 0; i < usersThisFrame; ++i)
        {
            int user = total_connected_Users - remainingUsers + i;
            double latency = currentTime + transmissionTime;

            timestamps.push_back(latency);
            latencies.push_back(latency);

            std::cout << "User " << user << " transmits at " << std::fixed << std::setprecision(4) << latency << " ms.\n";
        }

        remainingUsers -= usersThisFrame;
        currentTime += 5.0; 
    }

    std::cout << "\nSimulation Results:\n";                                   
    std::cout << "Throughput: " << cal_throuhput() << " Mbps\n";        
    std::cout << "Avg_Latency: " << avglatency() << " ms\n"; 
    std::cout << "Max_Latency: " << maxlatency() << " ms\n";         
}

double WiFi6Simulator::avglatency()
{
    if (latencies.empty())
        return 0.0;

    double totalLatency = std::accumulate(latencies.begin(), latencies.end(), 0.0);
    return totalLatency / latencies.size();
}

double WiFi6Simulator::maxlatency()
{
    if (latencies.empty())
        return 0.0;

    return *std::max_element(latencies.begin(), latencies.end());
}
