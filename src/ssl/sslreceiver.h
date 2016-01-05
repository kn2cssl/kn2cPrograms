#ifndef SSLRECEIVER_H
#define SSLRECEIVER_H

#include <QObject>
#include <QUdpSocket>
#include <QHostAddress>
#include "fpscounter.h"

class SSLReceiver : public FPSCounter
{
    Q_OBJECT
public:
    explicit SSLReceiver(QString ip, int port, QObject *parent = 0);

private:
    void udpsocketSetup(QString ip, int port);

    QUdpSocket *udpsocket;
    bool _isStarted;
    bool socketIsIntialized;
    QString ip;
    int port;

signals:
    void newReceivedPacket(QByteArray data, QString ip, int port);

public slots:
    void Start();
    void Stop();

private slots:
    void readPendingDatagrams();

};

#endif // SSLRECEIVER_H
