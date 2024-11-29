#include "Channel.h"
#include <iostream>

Channel::Channel(int bandwidth) : bandwidth(bandwidth), isBusy(false) {}

bool Channel::checkChannelStatus()
{
    // Simulate channel state (50% chance of being busy)
    bool isAvailable = !isBusy && (rand() % 2 == 0);
    std::cout << "[Debug] Channel state checked. Available: " << (isAvailable ? "Yes" : "No") << "\n";
    return isAvailable;
}

void Channel::reserveChannel()
{
    isBusy = true;
    std::cout << "[Action] Right Now Channel is now occupied.\n";
}

void Channel::freeChannel()
{
    isBusy = false;
    std::cout << "[Action] Right Now Channel is Free.\n";
}

int Channel::getChannelWidth() const
{
    return bandwidth;
}
