#include "playkickoffopp.h"

PlayKickoffOpp::PlayKickoffOpp(WorldModel *worldmodel, QObject *parent) :
    Play("PlayKickoffOpp", worldmodel, parent)
{
    numberOfDef=NUMOFDEFENDERS;

    tGolie=new TacticGoalie(wm);
    tDefenderM=new TacticDefender(wm);
    tDefenderL=new TacticDefender(wm);
    tDefenderR=new TacticDefender(wm);
    tFixedPosM = new TacticFixedPos(wm);
    tFixedPosL = new TacticFixedPos(wm);
    tFixedPosR = new TacticFixedPos(wm);

    tDefenderM->setDefenderPos(CENTER);
    tDefenderL->setDefenderPos(LEFT);
    tDefenderR->setDefenderPos(RIGHT);

    tFixedPosM->SetFixedPosition(CENTER);
    tFixedPosL->SetFixedPosition(LEFT);
    tFixedPosR->SetFixedPosition(RIGHT);
}

int PlayKickoffOpp::enterCondition()
{
    if(wm->cmgs.theirKickoff())
        return 100;
    else
        return 0;
}

void PlayKickoffOpp::execute()
{
    QList<int> activeAgents=wm->kn->ActiveAgents();
    activeAgents.removeOne(wm->ref_goalie_our);

    tactics[wm->ref_goalie_our]=tGolie;

    switch (activeAgents.length()) {

    case 1:
        tactics[activeAgents.takeFirst()]=tDefenderM;
        break;
    case 2:
       tactics[activeAgents.takeFirst()]=tDefenderR;
       tactics[activeAgents.takeFirst()]=tDefenderL;
        break;
    case 3:
        switch (numberOfDef) {
        case 2:
            tactics[activeAgents.takeFirst()]=tDefenderR;
            tactics[activeAgents.takeFirst()]=tDefenderL;
            tactics[activeAgents.takeFirst()]=tFixedPosM;
            break;
        case 3:
            tactics[activeAgents.takeFirst()]=tDefenderR;
            tactics[activeAgents.takeFirst()]=tDefenderL;
            tactics[activeAgents.takeFirst()]=tDefenderM;
            break;
        }
        break;
    case 4:
        switch (numberOfDef) {
        case 2:
            tactics[activeAgents.takeFirst()]=tDefenderR;
            tactics[activeAgents.takeFirst()]=tDefenderL;
            tactics[activeAgents.takeFirst()]=tFixedPosM;
            tactics[activeAgents.takeFirst()]=tFixedPosR;
            break;
        case 3:
            tactics[activeAgents.takeFirst()]=tDefenderR;
            tactics[activeAgents.takeFirst()]=tDefenderM;
            tactics[activeAgents.takeFirst()]=tDefenderL;
            tactics[activeAgents.takeFirst()]=tFixedPosM;
            break;
        }
        break;
    case 5:
        switch (numberOfDef) {
        case 2:
            tactics[activeAgents.takeFirst()]=tDefenderR;
            tactics[activeAgents.takeFirst()]=tDefenderL;
            tactics[activeAgents.takeFirst()]=tFixedPosR;
            tactics[activeAgents.takeFirst()]=tFixedPosL;
            tactics[activeAgents.takeFirst()]=tFixedPosM;
            break;
        case 3:
            tactics[activeAgents.takeFirst()]=tDefenderR;
            tactics[activeAgents.takeFirst()]=tDefenderM;
            tactics[activeAgents.takeFirst()]=tDefenderL;
            tactics[activeAgents.takeFirst()]=tFixedPosR;
            tactics[activeAgents.takeFirst()]=tFixedPosM;
            break;
        }
        break;
    }
}
