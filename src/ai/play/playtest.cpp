#include "playtest.h"

PlayTest::PlayTest(WorldModel *worldmodel, QObject *parent) :
    Play("PlayTest", worldmodel, parent)
{
    tAttacker = new TacticAttacker(wm);
//    tDefenderMid=new TacticDefender(wm);
//    tDefenderLeft=new TacticDefender(wm);
//    tDefenderRight=new TacticDefender(wm);
//    tHalt=new TacticHalt(wm);
    tPasser = new TacticTest(wm);
    tTT = new TacticTestFriction(wm);
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
//    tPasser->setKickerID(1);
//    tactics[1] = tPasser;
//    int recieverID = tPasser->findBestPlayerForPass();
//    if(tPasser->kicked)
//        tAttacker->go = true;
//    wm->ourRobot[recieverID].Status = AgentStatus::RecievingPass;
//    tactics[recieverID] = tAttacker;
    tactics[3] = tAttacker;

    return ;

}

