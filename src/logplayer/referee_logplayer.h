#ifndef REFEREE_LOGPLAYER_H
#define REFEREE_LOGPLAYER_H

#include "logplayer.h"
#include "proto/ref_log.pb.h"
#include "proto/referee.pb.h"

class Referee_logPlayer : public logPlayer
{
    Q_OBJECT
public:
    explicit Referee_logPlayer(QObject *parent = 0);
    virtual int getLength();
    virtual void setFrameNumber(int msec);

    void loadLog(Ref_log logs);
    Ref_log saveLog();
    void recordLog(SSL_Referee input);

    void restartTime();
    SSL_Referee returnCurrentPacket();

public slots:
    virtual void playLog();
    virtual void pauseLog();

private:
    QList<Ref_chunk> chunks;
    QTime *elapsedTime;
    Ref_chunk current_chunk;

signals:
    void dataReady();

public slots:
};

#endif // REFEREE_LOGPLAYER_H
