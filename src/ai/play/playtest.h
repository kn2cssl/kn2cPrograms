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
<<<<<<< HEAD
private:
    TacticTest* tTest;
    TacticTest* tTest2;
=======

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
<<<<<<< HEAD
>>>>>>> 5aee4ed9254def077fb748ede91039b2d492a21c
=======
>>>>>>> 5aee4ed9254def077fb748ede91039b2d492a21c
};
#endif // PLAYTEST_H
