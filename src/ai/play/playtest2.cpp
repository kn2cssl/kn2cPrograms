#include "playtest2.h"

PlayTest2::PlayTest2(WorldModel *worldmodel, QObject *parent) :
    Play("PlayTest2", worldmodel, parent)
{
    // Goaler.
    tGolie = new TacticGoalie(wm);
    tTF = new TacticTestFriction(wm);
    thalt = new TacticHalt(wm);
    tTest = new TacticTest(wm);
}

int PlayTest2::enterCondition()
{
    return 0;
}

void PlayTest2::initRole()
{

}

void PlayTest2::execute()
{
//    tactics[wm->ref_goalie_our] = tGolie;
    tactics[3] = tTest;
    qDebug()<<"Ball Speed is "<<wm->ball.vel.loc.length();
}

