#ifndef PLAYPREPARING_H
#define PLAYPREPARING_H

#include "play.h"

class PlayPreparing : public Play
{
    Q_OBJECT
public:
    PlayPreparing(WorldModel *worldmodel, QObject *parent = 0);
    virtual void execute();
    virtual int enterCondition();

private:
    TacticPreparing* training[PLAYERS_MAX_NUM];

    QList<int> readyRobots;
    int index;
    bool firstInit;
    virtual void initRole();
};

#endif // PLAYPREPARING_H
