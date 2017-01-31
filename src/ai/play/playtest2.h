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
<<<<<<< HEAD
=======
    TacticTest2* tTest;
>>>>>>> d766c95da96dc8ee70e0992aefe4e0a62d783e28
    virtual void initRole();
    TacticTest2* tTest;
};

#endif // PLAYTEST2_H
