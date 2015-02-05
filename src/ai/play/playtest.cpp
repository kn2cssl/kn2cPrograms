#include "playtest.h"

PlayTest::PlayTest(WorldModel *worldmodel, QObject *parent) :
    Play("PlayTest", worldmodel, parent)
{
    for(int i=0;i<PLAYERS_MAX_NUM;i++)
        training[i] = new TacticTest(wm);

    firstInit = false;
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
    if(!firstInit)
    {
        readyRobots = wm->kn->ActiveAgents();
        index = readyRobots.takeFirst();
        for(int i=0;i<PLAYERS_MAX_NUM;i++)
        {
            training[i]->queuePos = wm->ourRobot[i].pos;
        }
        firstInit = true;
    }

    if(training[index]->kickIt)
    {
        training[index]->kickIt = false;
        training[index]->kickPermision = false;
        readyRobots.append(index);
        index = readyRobots.takeFirst();
    }
    else
    {
        training[index]->kickPermision = true;
        tactics[index] = training[index];
    }
    qDebug()<<"kickIt["<<index<<"] : "<<training[index]->kickIt;
    return ;

}

