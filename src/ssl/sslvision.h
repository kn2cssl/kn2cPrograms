#ifndef SSLVISION_H
#define SSLVISION_H

#include <QObject>
#include <QTime>

#include "proto/messages_robocup_ssl_wrapper.pb.h"
#include "base.h"
#include "constants.h"
#include "sslreceiver.h"
#include "geom.h"
#include "util.h"
#include "worldmodel.h"
#include "logplayer/vision_logplayer.h"

class SSLVision : public SSLReceiver
{
    Q_OBJECT

public:
    explicit SSLVision(QString ip, int port, TeamColorType color, TeamSideType side, CameraConfigType camera, WorldModel *wm, QObject *parent = 0);
    virtual int getFPS(int c) = 0;
    void startRecording();
    Vision_log stopRecording();
    void startPlaying();
    void stopPlaying();
    void pausePlaying();
    void loadPlaying(Vision_log logs);
    int logLength();
    void setLogFrame(int msec);

protected:
    QTime _time;
    TeamColorType _color;
    TeamSideType _side;
    CameraConfigType _camera;
    WorldModel *_wm;
    Vision_logPlayer *logplayer;

    virtual void parse(SSL_DetectionFrame &pck) = 0;
    virtual void parseLog(SSL_DetectionFrame &pck) = 0;

private slots:
    void readPendingPacket(QByteArray data, QString ip, int port);
    void logResponder();

private:
    bool recordPermission;

};

#endif // SSLVISION_H
