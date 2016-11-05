#ifndef PLAYHW2_1_H
#define PLAYHW2_1_H
#include "play.h"
#include "man2man.h"
#include "tactic/tacticteststandingforwardenemy.h"

class PlayHW2_1 : public Play
{

    Q_OBJECT
public:
    explicit PlayHW2_1(WorldModel *worldmodel, QObject *parent = 0);
    virtual void execute();
    virtual void initRole();
    virtual int enterCondition();
private:
    TacticTestStandingForwardEnemy* tTest;
};

#endif // PLAYHW2_1_H
