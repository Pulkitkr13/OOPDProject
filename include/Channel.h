#ifndef CHANNEL_H
#define CHANNEL_H

class Channel
{
private:
    int bandwidth; 
    bool isBusy;  

public:
    Channel(int bandwidth);  
    bool checkChannelStatus();     
    void reserveChannel();    
    void freeChannel();    
    int getChannelWidth() const; 
};

#endif
