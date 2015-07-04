#ifndef SSLVISION_H
#define SSLVISION_H

#include <QObject>
#include <QTime>

#include "messages_robocup_ssl_wrapper.pb.h"
#include "base.h"
#include "constants.h"
#include "sslreceiver.h"
#include "geom.h"
#include "util.h"
#include "worldmodel.h"

class SSLVision : public SSLReceiver
{
    Q_OBJECT

public:
    explicit SSLVision(QString ip, int port, TeamColorType color, TeamSideType side, CameraConfigType camera, WorldModel *wm, QObject *parent = 0);
    virtual int getFPS(int c) = 0;

protected:
    QTime _time;
    TeamColorType _color;
    TeamSideType _side;
    CameraConfigType _camera;
    WorldModel *_wm;

    virtual void parse(SSL_DetectionFrame &pck) = 0;

private slots:
    void readPendingPacket(QByteArray data, QString ip, int port);

};

#endif // SSLVISION_H
