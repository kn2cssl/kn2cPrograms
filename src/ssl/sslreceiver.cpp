#include "sslreceiver.h"

SSLReceiver::SSLReceiver(QString ip, int port, QObject *parent) :
    FPSCounter(parent),
    _isStarted(false)
{
    this->ip = ip;
    this->port = port;
    udpsocketSetup(ip,port);
}

void SSLReceiver::udpsocketSetup(QString ip, int port)
{
    // udp socket setup
    udpsocket = new QUdpSocket();
    bool result;
    result = udpsocket->bind(QHostAddress::AnyIPv4, port, QUdpSocket::ReuseAddressHint);
    if(!result) qDebug() << udpsocket->errorString();
    result = udpsocket->joinMulticastGroup(QHostAddress(ip));
    if(!result) qDebug() << udpsocket->errorString();
    socketIsIntialized = true;
}

void SSLReceiver::Start()
{
    if(_isStarted) return;
    if(!socketIsIntialized) udpsocketSetup(ip,port);
    connect(udpsocket, SIGNAL(readyRead()), this, SLOT(readPendingDatagrams()));
    _isStarted=true;
}

void SSLReceiver::Stop()
{
    if(!_isStarted) return;
    disconnect(udpsocket, SIGNAL(readyRead()), this, SLOT(readPendingDatagrams()));
    delete udpsocket;
    socketIsIntialized = false;
    _isStarted=false;
}

void SSLReceiver::readPendingDatagrams()
{
    while (udpsocket->hasPendingDatagrams())
    {
        QByteArray datagram;
        datagram.resize(udpsocket->pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;
        udpsocket->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);
        newReceivedPacket(datagram,sender.toString(),senderPort);
        Pulse();
    }
}

