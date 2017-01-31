#include "playtest.h"
PlayTest::PlayTest(WorldModel *worldmodel, QObject *parent) :
    Play("PlayTest", worldmodel, parent)
{
    tTest = new TacticTest(wm);
<<<<<<< HEAD
    tTest2 = new TacticTest(wm);
=======
>>>>>>> d766c95da96dc8ee70e0992aefe4e0a62d783e28
}

int PlayTest::enterCondition()
{
    return 0;
}

void PlayTest::initRole()
{
}

void PlayTest::execute()
{
<<<<<<< HEAD
//    std::cout << wm->kn->ActiveAgents()[0] << std::endl;
//    wm->debug_pos.clear();
//    wm->debug_pos.append(wm->ourRobot[1].pos.loc);
//    wm->debug_pos.append(wm->ourRobot[0].pos.loc);
    tactics[4] = tTest;
=======
>>>>>>> d766c95da96dc8ee70e0992aefe4e0a62d783e28

    wm->debug_type=2;
    wm->debug_pos.append(wm->ball.pos.loc);
//    for(int i=0;i<wm->kn->ActiveAgents().length();i++){
//        tactics[wm->kn->ActiveAgents()[i]] = tTest;
//    }
    //wm->debug_pos.clear();
    //wm->debug_pos.append(Vector2D (0,0));
}
