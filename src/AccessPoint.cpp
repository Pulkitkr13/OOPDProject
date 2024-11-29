#include "AccessPoint.h"
#include "User.h"     // Full header inclusion
#include "Channel.h"  // Full header inclusion
#include <iostream>
using namespace std;

AccessPoint::AccessPoint(int total_connected_Users, int bandwidth) : total_connected_Users(total_connected_Users), channel(bandwidth) {}

void AccessPoint::registerUser(const User &user)
{
    users_Accesspoint.push_back(user);
    cout << "Added User " << user.getUserId() << " to the Access Point.\n";
}

bool AccessPoint::checkChannelStatus()
{
    return channel.checkChannelStatus();
}

void AccessPoint::reserveChannel()
{
    channel.reserveChannel();
}

void AccessPoint::freeChannel()
{
    channel.freeChannel();
}

int AccessPoint::getChannelWidth() const
{
    return channel.getChannelWidth();
}

void AccessPoint::handleDataTransfer()
{
    for (auto &user : users_Accesspoint)
    {
        bool success = false;
        while (!success)
        {
            if (channel.checkChannelStatus())
            {
                channel.reserveChannel();
                Packet packet = user.createPacket();
                cout << "[Info] User " << user.getUserId() << " transmitting a packet of a size----> "
                     << packet.packetsize() << " KB.\n";
                user.getSentPacketCount();
                success = true;
                channel.freeChannel();
            }
            else
            {
                int backoffTime = rand() % 10 + 1; // Random backoff between 1-10 ms
                cout << "[Warning] User " << user.getUserId() << " backsoff for " << backoffTime << " ms.\n";
            }
        }
    }
}
