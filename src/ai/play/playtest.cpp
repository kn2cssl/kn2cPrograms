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
//    std::cout << wm->kn->ActiveAgents()[0] << std::endl;
//    wm->debug_pos.clear();
//    wm->debug_pos.append(wm->ourRobot[1].pos.loc);
//    wm->debug_pos.append(wm->ourRobot[0].pos.loc);
    if(wm->ball.vel.loc.length() > 1)
        qDebug() << wm->ball.vel.loc.length();
}
