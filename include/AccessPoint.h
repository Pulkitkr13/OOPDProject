#ifndef ACCESS_POINT_H
#define ACCESS_POINT_H

#include <vector>
#include "User.h"
#include "Channel.h"

class AccessPoint
{
private:
    int total_connected_Users;            
    Channel channel;        
    std::vector<User> users_Accesspoint;

public:
    AccessPoint(int total_connected_Users, int bandwidth); 
    void registerUser(const User &user);           
    void handleDataTransfer();             
    bool checkChannelStatus();                      
    void reserveChannel();                    
    void freeChannel();                    
    int getChannelWidth() const;                
};

#endif
