#ifndef WPACKET_H
#define WPACKET_H

#include <QList>
#include <QByteArray>
#include <QDebug>
#include <QtEndian>

//#include <netinet/in.h>

#define WP_SOP QByteArray::fromHex("a55a") // Start of Packet
#define WP_EOP QByteArray::fromHex("80")   // End   of Packet


// disable padding
#pragma pack(push)  /* push current alignment to stack */
#pragma pack(1)     /* set alignment to 1 byte boundary */

struct SendPacketHeader
{
    //unsigned short SOP;	// start of packet (2 bytes)
    unsigned char SIB;	// size in bytes
    //unsigned char NOR;	// number of robots
    unsigned char CHK;	// ckeck sum
    //RobotData R[6];
    //unsigned char EOP;	// end of packet
};

struct RobotData
{
    unsigned char RID;	// robot id
    signed short int Vx_sp;
    signed short int Vy_sp;
    signed short int Wr_sp;
    signed short int Vx;
    signed short int Vy;
    signed short int Wr;
    signed short int alpha;
    unsigned char KICK;	// kick options
    unsigned char CHIP;	// CHIP & SPIN   #SCCCCCCC
    unsigned char SPIN;
    signed short int M0;	// motor 1
    signed short int M1;	// motor 2
    signed short int M2;	// motor 3
    signed short int M3;	// motor 4
    unsigned char KCK;	// kick options
    unsigned char CHP;	// CHIP & SPIN   #SCCCCCCC

    RobotData() :
        RID(0xFF),
        Vx_sp(0),
        Vy_sp(0),
        Wr_sp(0),
        Vx(0),
        Vy(0),
        Wr(0),
        alpha(0),
        KICK(0),
        CHIP(0),
        SPIN(0)
    { }
};
#pragma pack(pop)   /* restore original alignment from stack */

class WPacket
{
public:
    WPacket();
    void AddRobot(RobotData rd);
    QByteArray GetPacket();
    void Clear();

private:
    QMap<int,RobotData> _rdata;
};

#endif // WPACKET_H
