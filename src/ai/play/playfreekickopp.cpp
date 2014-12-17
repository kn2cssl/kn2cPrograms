#include "playfreekickopp.h"

PlayFreeKickOpp::PlayFreeKickOpp(WorldModel *worldmodel, QObject *parent) :
    Play("PlayFreeKickOpp", worldmodel, parent)
{
    numberOfPlayer = 0;

    pressingIsInit = false;
    rolesIsInit = false;

    tGolie = new TacticGoalie(wm);

    tDefenderLeft = new TacticDefender(wm);
    tDefenderRight = new TacticDefender(wm);
    tDefenderMid = new TacticDefender(wm);

    tAttackerLeft = new TacticAttacker(wm);
    tAttackerMid = new TacticAttacker(wm);
    tAttackerRight = new TacticAttacker(wm);
}

int PlayFreeKickOpp::enterCondition()
{
    if(wm->cmgs.theiFreeKick() || wm->cmgs.theirDirectKick())
    {
        if(wm->gs_last != wm->gs)
        {
            rolesIsInit = false;
        }
        else
        {
            rolesIsInit = conditionChanged();
        }
        return 100;
    }
    else
        return 0;
//    return 200000;
}

void PlayFreeKickOpp::initRole()
{
    QList<int> activeAgents=wm->kn->ActiveAgents();
    numberOfPlayer = activeAgents.size();
    activeAgents.removeOne(wm->ref_goalie_our);
    wm->ourRobot[wm->ref_goalie_our].Role = AgentRole::Golie;
    switch (activeAgents.length()) {
    case 1:
        wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::AttackerMid;
        break;
    case 2:
        wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::AttackerMid;
        wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::DefenderMid;
        break;
    case 3:
        wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::DefenderRight;
        wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::DefenderLeft;
        wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::AttackerMid;
        break;
    case 4:
        wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::DefenderRight;
        wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::DefenderLeft;
        wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::AttackerMid;
        wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::AttackerLeft;
        break;
    case 5:
        switch (numberOfDef) {
        case 2:
            wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::DefenderRight;
            wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::DefenderLeft;
            wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::AttackerMid;
            wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::AttackerRight;
            wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::AttackerLeft;
            break;
        case 3:
            wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::DefenderRight;
            wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::DefenderLeft;
            wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::DefenderMid;
            wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::AttackerMid;
            wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::AttackerRight;
            break;
        }
        break;
    }
    rolesIsInit = true;
}

void PlayFreeKickOpp::initPressing()
{
    qDebug() << "initPressing()";
    QList<int> oppAgents = wm->kn->ActiveOppAgents();
    oppAgents.removeOne(wm->ref_goalie_opp);
    for(int i=0;i<oppAgents.size();i++)
    {
        for(int j=0;j<oppAgents.size();j++)
        {
            double distanceI = (wm->oppRobot[oppAgents.at(i)].pos.loc - Field::ourGoalCenter).length();
            double distanceJ = (wm->oppRobot[oppAgents.at(j)].pos.loc - Field::ourGoalCenter).length();
            if(distanceI > distanceJ)
                oppAgents.swap(i,j);
        }
    }

    tAttackerMid->setPlayerToKeep(oppAgents.takeLast());
    wm->ourRobot[tAttackerMid->getID()].Status = AgentStatus::BlockingRobot;
    tAttackerLeft->setPlayerToKeep(oppAgents.takeLast());
    wm->ourRobot[tAttackerLeft->getID()].Status = AgentStatus::BlockingRobot;
    tAttackerRight->setPlayerToKeep(oppAgents.takeLast());
    wm->ourRobot[tAttackerRight->getID()].Status = AgentStatus::BlockingRobot;

    pressingIsInit = true;
    qDebug()<<"end of pressingInit";
}

void PlayFreeKickOpp::setTactics(int index)
{
    switch (wm->ourRobot[index].Role) {
    case AgentRole::Golie:
        tactics[index] = tGolie;
        break;
    case AgentRole::DefenderMid:
        tactics[index] = tDefenderMid;
        break;
    case AgentRole::DefenderLeft:
        tactics[index] = tDefenderLeft;
        break;
    case AgentRole::DefenderRight:
        tactics[index] = tDefenderRight;
        break;
    case AgentRole::AttackerMid:
        tactics[index] = tAttackerMid;
        break;
    case AgentRole::AttackerRight:
        tactics[index] = tAttackerRight;
        break;
    case AgentRole::AttackerLeft:
        tactics[index] = tAttackerLeft;
        break;
    default:
        break;
    }
}
void PlayFreeKickOpp::execute()
{
    QList<int> activeAgents=wm->kn->ActiveAgents();

    if( rolesIsInit && !pressingIsInit )
        initPressing();

    if( !rolesIsInit )
        initRole();

    for(int i=0;i<activeAgents.size();i++)
        setTactics(activeAgents.at(i));
}
