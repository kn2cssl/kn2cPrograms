#ifndef VISION_LOGPLAYER_H
#define VISION_LOGPLAYER_H

#include <QObject>
#include <QFile>
#include "worldmodel.h"
#include "logplayer.h"
#include "proto/messages_robocup_ssl_wrapper.pb.h"
#include "proto/vision_log.pb.h"

class Vision_logPlayer : public logPlayer
{
    Q_OBJECT
public:
    explicit Vision_logPlayer(WorldModel *worldmodel, QString address, QObject *parent = 0);
    virtual void playLog();
    virtual bool loadLog();
    bool loadLog(Vision_log logs);
    Vision_log saveLog();
    virtual void pauseLog();
    void recordLog(SSL_WrapperPacket input);
    void restartTime();
    SSL_WrapperPacket returnCurrentPacket();
    virtual int getLength();
    void setFrameNumber(int msec);

public slots:
    void pauseShot();

private:
    WorldModel *wm;
    QList<Vision_chunk> chunks;
    QTime *elapsedTime;
    QString fileAddress;
    Vision_chunk current_chunk;
    int frameNumber;
    
signals:
    void dataReady();

public slots:
};

#endif // VISION_LOGPLAYER_H
