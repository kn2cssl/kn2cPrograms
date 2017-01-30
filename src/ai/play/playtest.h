#ifndef PLAYTEST_H
#define PLAYTEST_H
#include "play.h"
#include "man2man.h"

class PlayTest : public Play
{
    Q_OBJECT
public:
    explicit PlayTest(WorldModel *worldmodel, QObject *parent = 0);
    virtual void execute();
    virtual void initRole();
    virtual int enterCondition();

private:
    TacticTest *tTest1;
    TacticTest *tTest2;
    TacticTest *tTest3;
    TacticTest *tTest4;
    TacticTest *tTest5;
    TacticTest *tTest6;

    TacticGoalie *tGoalie;
    TacticDefender *tDefenderLeft;
    TacticDefender *tDefenderRight;
    TacticStop *tStopMid;
    TacticStop *tStopLeft;
    TacticStop *tStopRight;
    TacticAttacker *tAttackerLeft;
    TacticAttacker *tAttackerRight;

    int c = -1;
    int t = 0;
};
#endif // PLAYTEST_H
