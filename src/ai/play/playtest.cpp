#include "playtest.h"
PlayTest::PlayTest(WorldModel *worldmodel, QObject *parent) :
    Play("PlayTest", worldmodel, parent)
{
    tTest = new TacticTest(wm);
    tTest2 = new TacticTest(wm);
}

int PlayTest::enterCondition()
{
    //return 20000;
    return 0;
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
    tactics[4] = tTest;
//    for(int i=0;i<wm->kn->ActiveAgents().length();i++){
//        tactics[wm->kn->ActiveAgents()[i]] = tTest;
//    }
    //wm->debug_pos.clear();
    //wm->debug_pos.append(Vector2D (0,0));
}
