#include "playtest.h"
PlayTest::PlayTest(WorldModel *worldmodel, QObject *parent) :
    Play("PlayTest", worldmodel, parent)
{//////////////////////////////////
    test = new TacticTest(wm);
    test2 = new TacticTest2(wm);
    ///////////////////////////////////
}

int PlayTest::enterCondition()
{
    return 0;
}

void PlayTest::initRole()
{
}

void PlayTest::execute()
{//---////////////////////////////////////////////////////

        tactics[0] = test;
        tactics[1] = test;
        tactics[2] = test;

}
