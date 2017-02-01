#ifndef SSLREFBOXNEW_H
#define SSLREFBOXNEW_H

#include "sslrefbox.h"
#include "proto/referee.pb.h"
#include "logplayer/referee_logplayer.h"

class SSLRefBoxNew : public SSLRefBox
{
    Q_OBJECT

public:
    explicit SSLRefBoxNew(QString ip, int port, TeamColorType color, float ball_min, WorldModel* wm, QObject *parent = 0);
    void startRecording();
    Ref_log stopRecording();
    void startPlaying();
    void stopPlaying();
    void pausePlaying();
    void loadPlaying(Ref_log logs);
    int logLength();
    void setLogFrame(int msec);

private:
    Referee_logPlayer *logplayer;
    bool recordPermission;

    void GameStatePacketParser(SSL_Referee packet, bool isSim);

private slots:
    virtual void readPendingPacket(QByteArray data, QString ip, int port);
    void logResponder();
};

#endif // SSLREFBOXNEW_H
