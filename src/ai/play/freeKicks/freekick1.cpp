#include "freekick1.h"

freeKick1::freeKick1(WorldModel *worldmodel, QObject *parent) :
    freeKick_base(worldmodel,parent)
{
    freeKickStart = false;

    freeKickRegion = fkRegion::RightRegion;
    oppLevel = Level::Beginner;

    tGolie = new TacticGoalie(wm);

    tDefenderLeft = new TacticDefender(wm);
    tDefenderRight = new TacticDefender(wm);
    tDefenderMid = new TacticDefender(wm);

    tAttackerLeft = new TacticAttacker(wm);
    tAttackerMid = new TacticAttacker(wm);
    tAttackerRight = new TacticAttacker(wm);
}

int freeKick1::enterCondition()
{
    if( wm->kn->IsInsideRect(wm->ball.pos.loc, Vector2D((1/3)*Field::MaxX,Field::MaxY)
                             , Vector2D(Field::MaxX,Field::MinY)))
        return 500;

    return 0;
}

void freeKick1::setPositions(int index)
{
    switch (wm->ourRobot[index].Role) {
    case AgentRole::AttackerLeft:
        tAttackerLeft->setIdlePosition(Vector2D(Field::MaxX/3,Field::oppGoalPost_L.y+200));
        break;
    case AgentRole::AttackerRight:
        tAttackerRight->setIdlePosition(Vector2D(Field::MaxX/3,Field::oppGoalPost_R.y-200));
        break;
    case AgentRole::AttackerMid:
        tAttackerMid->setIdlePosition(wm->ourRobot[index].pos);
        break;
    default:
        break;
    }
}

void freeKick1::execute()
{
    QList<int> activeAgents=wm->kn->ActiveAgents();

    if(!rolesIsInit)
    {
        initRole();
    }

    for(int i=0;i<activeAgents.size();i++)
    {
        setTactics(activeAgents.at(i));
        setPositions(activeAgents.at(i));
    }

    tAttackerMid->isKicker();

    if(!freeKickStart)
    {
        tAttackerMid->waitTimerStart();
        freeKickStart = true;
    }

    activeAgents.removeOne(tAttackerMid->getID());
    if(wm->cmgs.ourIndirectKick())
    {
        int recieverID = tAttackerMid->findBestPlayerForPass();
        if(recieverID != -1)
        {
            wm->ourRobot[recieverID].Status = AgentStatus::RecievingPass;
            activeAgents.removeOne(recieverID);
        }
    }
    while(activeAgents.size() > 0)
    {
        wm->ourRobot[activeAgents.takeFirst()].Status = AgentStatus::Idle;
    }
}
