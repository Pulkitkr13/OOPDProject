#include "User.h"
#include <iostream>

User::User(int id) : userId(id), packetsSent(0) {}

int User::getUserId() const
{
    return userId;
}

Packet User::createPacket()
{
    std::cout << "[Action] User " << userId << " generated a new packet.\n";
    return Packet(); // Default packet size of 1 KB
}

int User::getSentPacketCount() const  
{
    return packetsSent;
}

void User::updateSentPacketCount()
{
    packetsSent++;
    std::cout << "[Info] User " << userId << " incremented packets sent. Total: " << packetsSent << "\n";
}
