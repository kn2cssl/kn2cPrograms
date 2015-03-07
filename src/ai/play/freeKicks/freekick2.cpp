#include "freekick2.h"

freeKick2::freeKick2(WorldModel *wm, QObject *parent) :
    freeKick_base(wm,parent)
{
    freeKickRegion = fkRegion::RightRegion;
    oppLevel = Level::Beginner;
}

int freeKick2::enterCondition()
{
    if( wm->kn->IsInsideRect(wm->ball.pos.loc, Vector2D((1/3)*Field::MaxX,Field::MaxY)
                             , Vector2D(Field::MaxX,Field::MinY)))
        return 600;

    return 0;
}

void freeKick2::setPositions(int index)
{
    Position pos;

    switch (wm->ourRobot[index].Role) {
    case AgentRole::AttackerLeft:
        pos.loc = Vector2D(Field::MaxX/3,-wm->ball.pos.loc.y);
        pos.dir = (Field::oppGoalCenter - pos.loc).dir().radian();
        tAttackerLeft->setIdlePosition(pos);
        break;
    case AgentRole::AttackerRight:
        pos.loc = Vector2D(Field::MaxX/3,wm->ball.pos.loc.y);
        pos.dir = (Field::oppGoalCenter - pos.loc).dir().radian();
        tAttackerRight->setIdlePosition(pos);
        break;
    case AgentRole::AttackerMid:
        tAttackerMid->setIdlePosition(wm->ourRobot[index].pos);
        break;
    default:
        break;
    }
}

void freeKick2::execute()
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

    int recieverID = tAttackerLeft->getID();
    tAttackerMid->isKicker(recieverID);

    if(!freeKickStart)
    {
        tAttackerMid->waitTimerStart();
        freeKickStart = true;
    }

    activeAgents.removeOne(tAttackerMid->getID());
    if(wm->cmgs.ourIndirectKick())
    {
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
