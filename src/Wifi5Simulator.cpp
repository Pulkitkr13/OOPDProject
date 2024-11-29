#include "WiFi5Simulator.h"
#include <iostream>
#include <iomanip>
#include <numeric>   // For std::accumulate
#include <algorithm> // For std::max_element

WiFi5Simulator::WiFi5Simulator(int total_connected_Users, int bandwidth)
    : Simulator(total_connected_Users, bandwidth) {}

void WiFi5Simulator::executeTest()
{
    std::cout << "WiFi 5 MU-MIMO Simulation\n";

    // User input for packets per user
    int numPacketsPerUser;
    std::cout << "Enter the number of packets per user: ";
    std::cin >> numPacketsPerUser;

    // Simulation parameters
    double currentTime = 0.0;
    double broadcastTime = 0.0614;          // 1 KB broadcast packet transmission time (ms)
    double csiTime = 0.012;                 // CSI packet transmission time (ms)
    double packetTransmissionTime = 0.0614; // Data packet transmission time (ms)
    double timeSlot = 15.0;                 // Time slot for parallel communication (ms)

    int totalPackets = total_connected_Users * numPacketsPerUser; // Total packets to be sent
    int packetsSent = 0;                             // Count of sent packets

    std::vector<int> packetsRemaining(total_connected_Users, numPacketsPerUser); // Packets left for each user

    // Calculate maximum number of packets that can be sent in a 15 ms time slot
    double bandwidthMbps = static_cast<double>(bandwidth); // Bandwidth in Mbps
    double dataRate = bandwidthMbps * 8.0 * 5.0 / 6.0;     // Data rate in Kbps (20 MHz bandwidth with coding rate)
    double timeSlotDurationSec = timeSlot / 1000.0;         // 15 ms converted to seconds
    double dataInTimeSlotKbps = dataRate * timeSlotDurationSec; // Data transmitted in 15 ms (in Kbps)
    
    // Calculate number of packets that fit in 15 ms (given packet size is 1 KB or 8.192 Kbps)
    double packetSizeKbps = 8.192; // 1 KB = 8.192 Kbps
    int maxPacketsPerSlot = static_cast<int>(dataInTimeSlotKbps / packetSizeKbps); // Max packets that can fit in 15 ms

    std::cout << "Max packets per time slot: " << maxPacketsPerSlot << "\n";

    while (packetsSent < totalPackets)
    {
        // Step 1: Broadcast a packet
        currentTime += broadcastTime;

        // Step 2: Collect CSI packets sequentially from each user
        for (int i = 0; i < total_connected_Users; ++i)
        {
            currentTime += csiTime;
        }

        // Step 3: Start parallel transmission for the time slot
        double slotStart = currentTime;
        int totalPacketsThisSlot = 0;

        // Send packets in parallel, respecting the 15 ms time slot
        for (int i = 0; i < total_connected_Users; ++i)
        {
            while (packetsRemaining[i] > 0)
            {
                double transmissionEndTime = currentTime + packetTransmissionTime;

                // If the transmission exceeds the time slot, break
                if (transmissionEndTime > slotStart + timeSlot)
                {
                    break;
                }

                // Send the packet
                packetsRemaining[i]--;
                packetsSent++;
                totalPacketsThisSlot++;
                currentTime = transmissionEndTime;
                latencies.push_back(currentTime);  // Record latency
                timestamps.push_back(currentTime); // Record timestamp
            }
        }

        // Check if round-robin scheduling is required
        if (totalPacketsThisSlot > maxPacketsPerSlot)
        {
            // Round-robin scheduling is needed, redistribute packets evenly across users
            std::cout << "Round-robin scheduling applied.\n";
            for (int i = 0; i < total_connected_Users; ++i)
            {
                if (packetsRemaining[i] > 0)
                {
                    // Handle round-robin transmission logic (you can implement a more complex strategy here if needed)
                    // For simplicity, continue transmitting in the current slot
                }
            }
        }
        else
        {
            std::cout << "No round-robin needed, enough time for all packets.\n";
        }
    }

    // Display simulation results
    std::cout << "Simulation Complete:\n";
    std::cout << "Throughput: " << cal_throuhput(totalPackets, currentTime) << " Mbps\n";
    std::cout << "Average Latency: " << avglatency() << " ms\n";
    std::cout << "Max Latency: " << maxlatency() << " ms\n";
}

double WiFi5Simulator::cal_throuhput(int totalPackets, double totalTime)
{
    if (totalTime <= 0.0)
    {
        return 0.0;
    }
    double totalData = totalPackets * 1024 * 8.0; // Total data in kilobits (1 KB = 8 kilobits)
    std::cout << totalData << std::endl; 
    return totalData / (totalTime * 1000);  // Convert ms to seconds and calculate throughput in Mbps
}

double WiFi5Simulator::avglatency()
{
    if (latencies.empty())
    {
        return 0.0;
    }
    double totalLatency = std::accumulate(latencies.begin(), latencies.end(), 0.0);
    return totalLatency / latencies.size();
}

double WiFi5Simulator::maxlatency()
{
    if (latencies.empty())
    {
        return 0.0;
    }
    return *std::max_element(latencies.begin(), latencies.end());
}
