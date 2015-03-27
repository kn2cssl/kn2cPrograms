#include "playpreparing.h"

PlayPreparing::PlayPreparing(WorldModel *worldmodel, QObject *parent) :
    Play("PlayPreparing", worldmodel, parent)
{
    for(int i=0;i<PLAYERS_MAX_NUM;i++)
        training[i] = new TacticPreparing(wm);

    firstInit = false;
}

int PlayPreparing::enterCondition()
{
    return 0;
}

void PlayPreparing::initRole()
{

}

void PlayPreparing::execute()
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
    return ;

}
