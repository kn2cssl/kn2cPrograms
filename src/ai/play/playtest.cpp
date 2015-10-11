#include "playtest.h"
PlayTest::PlayTest(WorldModel *worldmodel, QObject *parent) :
    Play("PlayTest", worldmodel, parent)
{//////////////////////////////////
    test = new TacticTest(wm);
    ///////////////////////////////////
}

int PlayTest::enterCondition()
{
    return 2000000;
}

void PlayTest::initRole()
{
}

void PlayTest::execute()
{//---////////////////////////////////////////////////////
    tactics[5] = test;
 //--////////////////////////////////////////////////////
}
