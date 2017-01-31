#ifndef VISION_LOGPLAYER_H
#define VISION_LOGPLAYER_H

#include "logplayer.h"
#include "proto/messages_robocup_ssl_wrapper.pb.h"
#include "proto/vision_log.pb.h"

class Vision_logPlayer : public logPlayer
{
    Q_OBJECT
public:
    explicit Vision_logPlayer(QObject *parent = 0);
    virtual int getLength();
    virtual void setFrameNumber(int msec);

    void loadLog(Vision_log logs);
    Vision_log saveLog();
    void recordLog(SSL_WrapperPacket input);

    void restartTime();
    SSL_WrapperPacket returnCurrentPacket();

public slots:
    virtual void playLog();
    virtual void pauseLog();

private:
    QList<Vision_chunk> chunks;
    QTime *elapsedTime;
    Vision_chunk current_chunk;
    
signals:
    void dataReady();

public slots:
};

#endif // VISION_LOGPLAYER_H
