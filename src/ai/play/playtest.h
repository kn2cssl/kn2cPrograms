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

 ////////////////////////////
private:
       int flag=0;
    TacticTest *test;
    TacticTest2 *test2;
    ///////////////////////////
};
#endif // PLAYTEST_H
