#include "freekick2.h"

freeKick2::freeKick2(WorldModel *wm, QObject *parent) :
    freeKick_base(wm,parent)
{
    freeKickRegion = fkRegion::RightRegion;
    oppLevel = Level::Beginner;
}

int freeKick2::enterCondition(Level level)
{
    if( wm->kn->IsInsideRect(wm->ball.pos.loc, Vector2D(0.33*Field::MaxX,Field::MaxY)
                             , Vector2D(Field::MaxX,0.33*Field::MaxY))
            ||
            wm->kn->IsInsideRect(wm->ball.pos.loc, Vector2D(0.33*Field::MaxX,0.33*Field::MinY)
                                 , Vector2D(Field::MaxX,Field::MinY)))
    {
        if( level == this->oppLevel)
            return 600;
        else
            return 300;
    }

    return 0;
}

void freeKick2::setPositions()
{
    Position leftDefPos,rightDefPos,goaliePos;
    zonePositions(tDefenderLeft->getID(),tDefenderRight->getID(),goaliePos,leftDefPos,rightDefPos);
    tDefenderLeft->setIdlePosition(leftDefPos);
    tDefenderRight->setIdlePosition(rightDefPos);
    tGolie->setIdlePosition(goaliePos);

    Position pos;

    pos.loc = Vector2D(Field::MaxX/3,-wm->ball.pos.loc.y);
    pos.dir = (Field::oppGoalCenter - pos.loc).dir().radian();
    tAttackerLeft->setIdlePosition(pos);

    pos.loc = Vector2D(Field::MaxX/3,wm->ball.pos.loc.y);
    pos.dir = (Field::oppGoalCenter - pos.loc).dir().radian();
    tAttackerRight->setIdlePosition(pos);

    tAttackerMid->setIdlePosition(wm->ourRobot[tAttackerMid->getID()].pos);
}

void freeKick2::execute()
{
    QList<int> activeAgents=wm->kn->ActiveAgents();

    if(!rolesIsInit)
    {
        initRole();
    }

    for(int i=0;i<activeAgents.size();i++)
        setTactics(activeAgents.at(i));

    setPositions();

    int recieverID = tAttackerLeft->getID();
    tAttackerMid->isKicker(recieverID);

    if(!freeKickStart)
    {
        tAttackerMid->waitTimerStart(false);
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
