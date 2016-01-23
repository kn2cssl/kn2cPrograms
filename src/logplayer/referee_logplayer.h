#ifndef REFEREE_LOGPLAYER_H
#define REFEREE_LOGPLAYER_H

#include <QObject>
#include "logplayer.h"
#include "worldmodel.h"
#include "proto/referee.pb.h"

class Referee_logPlayer : public logPlayer
{
    Q_OBJECT
public:
    explicit Referee_logPlayer(WorldModel *worldmodel, QString address, QObject *parent = 0);
    virtual void playLog();
    virtual bool loadLog();
    virtual bool saveLog();
    void recordLog();

private:
    QList<SSL_Referee> chunks;
    WorldModel *wm;

signals:

public slots:
};

#endif // REFEREE_LOGPLAYER_H
