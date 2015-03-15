#include "playpenaltyopp.h"

PlayPenaltyOpp::PlayPenaltyOpp(WorldModel *worldmodel, QObject *parent) :
    Play("PlayPenaltyOpp", worldmodel, parent)
{
    tGoalie=new TacticGoalie(wm);
    tDefenderMid=new TacticDefender(wm);
    tDefenderRight=new TacticDefender(wm);
    tDefenderLeft=new TacticDefender(wm);
    tAttackerMid = new TacticAttacker(wm);
    tAttackerRight = new TacticAttacker(wm);
    tAttackerLeft = new TacticAttacker(wm);
}

int PlayPenaltyOpp::enterCondition()
{
    if(wm->cmgs.theirPenaltyKick())
        return 100;
    else
        return 0;
}

void PlayPenaltyOpp::setTactics(int index)
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
        tactics[index] = tAttackerMid;
        break;
    case AgentRole::AttackerLeft:
        tactics[index] = tAttackerLeft;
        break;
    case AgentRole::AttackerRight:
        tactics[index] = tAttackerRight;
        break;
    default:
        break;
    }
}

void PlayPenaltyOpp::setPositions()
{
    Position goaliePos,leftDefPos,rightDefPos;
    zonePositions(tDefenderLeft->getID(),tDefenderRight->getID(),goaliePos,leftDefPos,rightDefPos);
    tDefenderLeft->setIdlePosition(leftDefPos);
    tDefenderRight->setIdlePosition(rightDefPos);

    tAttackerMid->setIdlePosition(Field::oppPenaltyParallelLineCenter);
    tAttackerRight->setIdlePosition(Vector2D(Field::oppPenaltyParallelLineCenter.x,
                                             Field::oppPenaltyParallelLineCenter.y - (Field::MaxY*0.75)));
    tAttackerLeft->setIdlePosition(Vector2D(Field::oppPenaltyParallelLineCenter.x,
                                            Field::oppPenaltyParallelLineCenter.y + (Field::MaxY*0.75)));

}

void PlayPenaltyOpp::initRole()
{
    QList<int> activeAgents=wm->kn->ActiveAgents();


    activeAgents.removeOne(wm->ref_goalie_our);

    wm->ourRobot[wm->ref_goalie_our].Role = AgentRole::Golie;

    switch (activeAgents.length()) {

    case 1:
        wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::DefenderMid;
        break;
    case 2:
        wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::DefenderRight;
        wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::DefenderLeft;
        break;
    case 3:
        wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::DefenderRight;
        wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::DefenderLeft;
        wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::AttackerMid;

        break;
    case 4:
        wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::DefenderLeft;
        wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::DefenderRight;
        wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::AttackerRight;
        wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::AttackerLeft;
        break;
    case 5:
        wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::DefenderRight;
        wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::DefenderLeft;
        wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::AttackerMid;
        wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::AttackerLeft;
        wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::AttackerRight;
        break;
    }
}

void PlayPenaltyOpp::execute()
{
    QList<int> activeAgents=wm->kn->ActiveAgents();

    initRole();

    for(int i=0;i<activeAgents.size();i++)
    {
        wm->ourRobot[activeAgents.at(i)].Status = AgentStatus::Idle;
    }

    while( !activeAgents.isEmpty() )
    {
        int index = activeAgents.takeFirst();
        setTactics(index);
    }

    setPositions();
}
