#ifndef PLAYTEST2_H
#define PLAYTEST2_H

#include "play.h"
#include "QDebug"
#include "tactic/tactichalt.h"

class PlayTest2 : public Play
{
    Q_OBJECT
public:
    explicit PlayTest2(WorldModel *worldmodel, QObject *parent = 0);
    virtual void execute();
    //virtual Tactic* getTactic(int id);
    virtual int enterCondition();
    Vector2D generatePos (int radius,double alpha);

private:
    virtual void initRole();
    TacticTest2* tTest;
};

#endif // PLAYTEST2_H
