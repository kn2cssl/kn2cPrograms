#ifndef AI_LOGPLAYER_H
#define AI_LOGPLAYER_H

#include <QObject>
#include "logplayer/logplayer.h"
#include "worldmodel.h"
#include "proto/AI/ssl_log.pb.h"

class AI_logPlayer : public logPlayer
{
    Q_OBJECT
public:
    explicit AI_logPlayer(WorldModel *worldmodel, QString address, QObject *parent = 0);
    virtual void playLog();
    virtual bool loadLog();
    virtual bool saveLog();
    void recordLog();

private:
    WorldModel *wm;
    QList<log_chunk> chunks;

    Robot_message_AgentStatus returnProtoStatus(AgentStatus status);
    Robot_message_AgentRole returnProtoRole(AgentRole role);
    Robot_message_AgentRegion returnProtoRegion(AgentRegion region);

signals:

public slots:
};

#endif // AI_LOGPLAYER_H
