#ifndef PACKET_H
#define PACKET_H

class Packet
{
private:
    int size;                
    double transmissionTime; 

public:
    Packet(int size = 1);                  
    int packetsize() const;                   
    void setTransferDuration(double time); 
    double fetchTransferDuration() const;   
};

#endif
