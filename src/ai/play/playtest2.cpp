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
<<<<<<< HEAD
    if(wm->gs == STATE_Stop){
        tactics[wm->ref_goalie_our] = tTest;
        //step1
        if(wm->kn->ActiveAgents().size() == 3){
            tactics[wm->kn->ActiveAgents()[0]] = tTest;
            tactics[wm->kn->ActiveAgents()[1]] = tTest;
            tactics[wm->kn->ActiveAgents()[2]] = tTest;
        }
        if(wm->kn->ActiveAgents().size() == 4){
            tactics[wm->kn->ActiveAgents()[0]] = tTest;
            tactics[wm->kn->ActiveAgents()[1]] = tTest;
            tactics[wm->kn->ActiveAgents()[2]] = tTest;
            tactics[wm->kn->ActiveAgents()[3]] = tTest;
        }
        if(wm->kn->ActiveAgents().size() == 5){
            tactics[wm->kn->ActiveAgents()[0]] = tTest;
            tactics[wm->kn->ActiveAgents()[1]] = tTest;
            tactics[wm->kn->ActiveAgents()[2]] = tTest;
            tactics[wm->kn->ActiveAgents()[3]] = tTest;
            tactics[wm->kn->ActiveAgents()[4]] = tTest;
        }
        if(wm->kn->ActiveAgents().size() == 6){
            tactics[wm->kn->ActiveAgents()[0]] = tTest;
            tactics[wm->kn->ActiveAgents()[1]] = tTest;
            tactics[wm->kn->ActiveAgents()[2]] = tTest;
            tactics[wm->kn->ActiveAgents()[3]] = tTest;
            tactics[wm->kn->ActiveAgents()[4]] = tTest;
            tactics[wm->kn->ActiveAgents()[5]] = tTest;
        }
    }
    if(wm->gs == STATE_Halt){
        for(int i = 0 ; i < wm->kn->ActiveAgents().size() ; i++){
            tactics[i] = new TacticHalt(wm);
        }
    }
    if(wm->gs == STATE_Free_kick_Opp){
        tactics[wm->ref_goalie_our] = tTest;
    }
    if(wm->gs == STATE_Free_kick_Our){
        tactics[0] = (Tactic*) (new TacticTest(wm));
    }
=======
    for(int i=0;i<wm->kn->ActiveAgents().length();i++){
        tactics[wm->kn->ActiveAgents()[i]] = tTest;
    }
    wm->debug_pos.clear();
//    if(wm->ball.isValid){
//        wm->debug_pos.append(wm->ball.pos.loc);
//        qDebug()<<"x :"<<wm->ball.pos.loc.x;
//        qDebug()<<"y :"<<wm->ball.pos.loc.y<<"\n\n";
//    }
>>>>>>> d766c95da96dc8ee70e0992aefe4e0a62d783e28
}

//Vector2D PlayTest2::generatePos(int radius,double alpha){
//    return Vector2D(wm->ball.pos.loc.x + radius*std::sin()
//}
