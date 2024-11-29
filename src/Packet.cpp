#include "Packet.h"
#include <iostream>

Packet::Packet(int size) : size(size), transmissionTime(0.0) {}

int Packet::packetsize() const
{
    return size;
}

void Packet::setTransferDuration(double time)
{
    transmissionTime = time;
    std::cout << "[Info] Transmissiontime set to: " << transmissionTime << " ms.\n";
}

double Packet::fetchTransferDuration() const
{
    return transmissionTime;
}
