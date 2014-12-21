#ifndef PLAYTEST_H
#define PLAYTEST_H

#include "play.h"

class PlayTest : public Play
{
    Q_OBJECT
public:
    explicit PlayTest(WorldModel *worldmodel, QObject *parent = 0);
    virtual void execute();
    //virtual Tactic* getTactic(int id);
    virtual int enterCondition();

private:
    TacticTest* training[PLAYERS_MAX_NUM];

    QList<int> readyRobots;
    int index;
    bool firstInit;
    virtual void initRole();
};

#endif // PLAYTEST_H
