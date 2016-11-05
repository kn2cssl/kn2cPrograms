#include "playhw2_1.h"

PlayHW2_1::PlayHW2_1(WorldModel *worldmodel, QObject *parent) :
    Play("PlayTest", worldmodel, parent)
{
    tTest = new TacticTestStandingForwardEnemy(wm);
}

int PlayHW2_1::enterCondition()
{
    return 0;
}

void PlayHW2_1::initRole()
{
}

void PlayHW2_1::execute()
{
    tTest->setDistance(5);
    tactics[wm->kn->ActiveAgents()[0]] = tTest;

}
