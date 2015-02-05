#ifndef TACTICTEST_H
#define TACTICTEST_H

#include "tactic.h"

class TacticTest : public Tactic
{
    Q_OBJECT
public:
    explicit TacticTest(WorldModel *worldmodel, QObject *parent = 0);
    virtual RobotCommand getCommand();

    Position queuePos;
    bool kickPermision;
    bool kickIt;
};

#endif // TACTICTEST_H
