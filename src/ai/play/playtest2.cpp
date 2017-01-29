#include "playtest2.h"

PlayTest2::PlayTest2(WorldModel *worldmodel, QObject *parent) :
    Play("PlayTest2", worldmodel, parent)
{
    tTest = new TacticTest2(wm);
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
    for(int i=0;i<wm->kn->ActiveAgents().length();i++){
        tactics[wm->kn->ActiveAgents()[i]] = tTest;
    }
    wm->debug_pos.clear();
//    if(wm->ball.isValid){
//        wm->debug_pos.append(wm->ball.pos.loc);
//        qDebug()<<"x :"<<wm->ball.pos.loc.x;
//        qDebug()<<"y :"<<wm->ball.pos.loc.y<<"\n\n";
//    }
}

