#include "playtest.h"
PlayTest::PlayTest(WorldModel *worldmodel, QObject *parent) :
    Play("PlayTest", worldmodel, parent)
{
    tTest = new TacticTest(wm);
    tTest2 = new TacticTest(wm);
}

int PlayTest::enterCondition()
{
    return 99990;
}

void PlayTest::initRole()
{
}

void PlayTest::execute()
{
    tactics[5]= tTest;
    wm->debug_type=2;
    wm->debug_pos.append(wm->ourRobot[5].pos.loc);
}
