#include "playtest.h"
PlayTest::PlayTest(WorldModel *worldmodel, QObject *parent) :
    Play("PlayTest", worldmodel, parent)
{
    tTest = new TacticTest(wm);
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

    wm->debug_type=2;
    wm->debug_pos.append(wm->ball.pos.loc);
//    for(int i=0;i<wm->kn->ActiveAgents().length();i++){
//        tactics[wm->kn->ActiveAgents()[i]] = tTest;
//    }
    //wm->debug_pos.clear();
    //wm->debug_pos.append(Vector2D (0,0));
}
