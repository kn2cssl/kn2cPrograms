#include "playkickoffour.h"

PlayKickoffOur::PlayKickoffOur(WorldModel *worldmodel, QObject *parent) :
    Play("PlayKickoffOur", worldmodel, parent)
{
    tGolie=new TacticGoalie(wm);

    tDefenderMid=new TacticDefender(wm);
    tDefenderLeft=new TacticDefender(wm);
    tDefenderRight=new TacticDefender(wm);

    tAttackerLeft = new TacticAttacker(wm);
    tAttackerMid = new TacticAttacker(wm);
    tAttackerRight = new TacticAttacker(wm);
}

int PlayKickoffOur::enterCondition()
{
    if(wm->cmgs.ourKickoff())
        return 100;
    else
        return 0;
}

void PlayKickoffOur::initRole()
{
    QList<int> activeAgents=wm->kn->ActiveAgents();
    numberOfPlayers = activeAgents.size();
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
}

void PlayKickoffOur::setTactics(int index)
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

void PlayKickoffOur::setPositions(int index)
{
    switch(wm->ourRobot[index].Role)
    {
    case AgentRole::AttackerMid:
        tAttackerMid->setIdlePosition(wm->kn->AdjustKickPoint(Vector2D(wm->ball.pos.loc.x-100,wm->ball.pos.loc.y),Field::oppGoalCenter));
        break;
    case AgentRole::AttackerRight:
        tAttackerRight->setIdlePosition(wm->kn->AdjustKickPoint(Vector2D(wm->ball.pos.loc.x - 250 , 1550),Field::oppGoalCenter));
        break;
    case AgentRole::AttackerLeft:
        tAttackerLeft->setIdlePosition(wm->kn->AdjustKickPoint(Vector2D(wm->ball.pos.loc.x - 250 , -1550),Field::oppGoalCenter));
        break;
    default:
        break;
    }
}

void PlayKickoffOur::execute()
{
    QList<int> activeAgents=wm->kn->ActiveAgents();

    initRole();

    for(int i=0;i<activeAgents.size();i++)
    {
        setTactics(activeAgents.at(i));
        setPositions(activeAgents.at(i));
    }

    if( wm->cmgs.canKickBall() )
    {
        wm->ourRobot[tAttackerMid->getID()].Status =  AgentStatus::Kicking;
    }

}