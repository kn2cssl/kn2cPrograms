#ifndef AI_LOGPLAYER_H
#define AI_LOGPLAYER_H

#include <QObject>
#include "logplayer/logplayer.h"
#include "worldmodel.h"
#include "proto/ssl_log.pb.h"

class AI_logPlayer : public logPlayer
{
    Q_OBJECT
public:
    explicit AI_logPlayer(QObject *parent = 0);
    virtual void playLog();
    virtual bool loadLog();
    bool loadLog(SSL_log logs);
    SSL_log saveLog();
    void recordLog(WorldModel* wm, QList<RobotCommand> RCs);
    void pauseLog();
    void restartTime();
    WorldModel* returnCurrentPacket();
    virtual int getLength();

    virtual void setFrameNumber(int msec);

    Robot_message_AgentStatus returnProtoStatus(AgentStatus status);
    AgentStatus returnAgentStatus(Robot_message_AgentStatus status);

    Robot_message_AgentRole returnProtoRole(AgentRole role);
    AgentRole returnAgentRole(Robot_message_AgentRole role);

    Robot_message_AgentRegion returnProtoRegion(AgentRegion region);
    AgentRegion returnAgentRegion(Robot_message_AgentRegion region);

public slots:
    void timerShot();
    void pauseShot();

private:
    QList<log_chunk> chunks;
    QTime *elapsedTime;
    QString fileAddress;
    log_chunk current_chunk;
    int frameNumber;
    int interval;

signals:
    void dataReady();

public slots:
};

#endif // AI_LOGPLAYER_H
