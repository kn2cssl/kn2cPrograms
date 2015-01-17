#include "playpenaltyour.h"

PlayPenaltyOur::PlayPenaltyOur(WorldModel *worldmodel, QObject *parent) :
    Play("PlayPenaltyOur", worldmodel, parent)
{
    tGoalie=new TacticGoalie(wm);
    tDefenderMid=new TacticDefender(wm);
    tDefenderLeft=new TacticDefender(wm);
    tDefenderRight=new TacticDefender(wm);
    tAttackerLeft = new TacticAttacker(wm);
    tAttackerRight = new TacticAttacker(wm);
    penaltyKicker=new TacticPenaltyKicker(wm);
}

int PlayPenaltyOur::enterCondition()
{
    if(wm->cmgs.ourPenaltyKick())
        return 100;
    else
        return 0;
}

void PlayPenaltyOur::setTactics(int index)
{
    switch (wm->ourRobot[index].Role) {
    case AgentRole::Golie:
        tactics[index] = tGoalie;
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
        tactics[index] = penaltyKicker;
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

void PlayPenaltyOur::initRole()
{
    QList<int> activeAgents=wm->kn->ActiveAgents();
    activeAgents.removeOne(wm->ref_goalie_our);

    wm->ourRobot[wm->ref_goalie_our].Role = AgentRole::Golie;

    switch (activeAgents.length()) {

    case 1:
        wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::AttackerMid;
        break;
    case 2:
        wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::DefenderMid;
        wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::AttackerMid;
        break;
    case 3:
        wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::DefenderLeft;
        wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::DefenderRight;
        wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::AttackerMid;
        break;
    case 4:
        switch (numberOfDef) {
        case 2:
            wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::DefenderLeft;
            wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::DefenderRight;
            wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::AttackerMid;
            wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::AttackerLeft;
            break;
        case 3:
            wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::DefenderLeft;
            wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::DefenderRight;
            wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::DefenderMid;
            wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::AttackerMid;
            break;
        }
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
}

void PlayPenaltyOur::execute()
{
    QList<int> activeAgents=wm->kn->ActiveAgents();

    initRole();

    for(int i=0;i<activeAgents.size();i++)
    {
        wm->ourRobot[activeAgents.at(i)].Status = AgentStatus::Idle;
    }

    for(int i=0;i<activeAgents.size();i++)
    {
        setTactics(activeAgents.at(i));
    }

    wm->ourRobot[penaltyKicker->getID()].Status = AgentStatus::Kicking;
}
