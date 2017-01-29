#ifndef TACTICTEST_H
#define TACTICTEST_H
#include "tactic.h"
#define DangerDist 300
class TacticTest : public Tactic
{
    Q_OBJECT
public:
    int flag=0;
    int flag1=0;
    int flag2=0;
    int flag3=0;
    explicit TacticTest(WorldModel *worldmodel, QObject *parent = 0);
    virtual RobotCommand getCommand();
};
#endif // TACTICTEST_H

