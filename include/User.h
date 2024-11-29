#ifndef USER_H
#define USER_H

#include "Packet.h"

class User
{
private:
    int userId;      
    int packetsSent; 

public:
    User(int id);                
    int getUserId() const;       
    Packet createPacket();     
    int getSentPacketCount() const;   
    void updateSentPacketCount(); 
};

#endif
