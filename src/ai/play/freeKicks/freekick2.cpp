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

    Position leftPos,rightPos;

    rightPos.loc = Vector2D(Field::MaxX/3,-wm->ball.pos.loc.y);
    rightPos.dir = (Field::oppGoalCenter - rightPos.loc).dir().radian();
    tAttackerRight->setIdlePosition(rightPos);

    leftPos.loc = Vector2D(Field::MaxX/3,wm->ball.pos.loc.y);
    leftPos.dir = (Field::oppGoalCenter - leftPos.loc).dir().radian();
    tAttackerLeft->setIdlePosition(leftPos);

    if( checkPositions(leftPos,rightPos) )
        tAttackerMid->youHavePermissionForKick();

        tAttackerMid->setIdlePosition(wm->ourRobot[tAttackerMid->getID()].pos);
}

bool freeKick2::checkPositions(Position leftPos, Position rightPos)
{
    bool leftCheck = true , rightCheck = true;
    if( wm->ourRobot[tAttackerLeft->getID()].isValid )
    {
        if( !wm->kn->ReachedToPos(wm->ourRobot[tAttackerLeft->getID()].pos.loc, leftPos.loc,150) )
            leftCheck = false;
    }

    if( wm->ourRobot[tAttackerRight->getID()].isValid )
    {
        if( !wm->kn->ReachedToPos(wm->ourRobot[tAttackerRight->getID()].pos.loc, rightPos.loc,150) )
            rightCheck = false;
    }

    return leftCheck & rightCheck;
}

void freeKick2::resetValues()
{
    rolesIsInit = false;
}

void freeKick2::execute()
{
    QList<int> activeAgents=wm->kn->ActiveAgents();

//    if(!rolesIsInit)
        initRole();

    for(int i=0;i<activeAgents.size();i++)
        setTactics(activeAgents.at(i));

    setPositions();

    tAttackerMid->isKicker();

    activeAgents.removeOne(tAttackerMid->getID());
    while(activeAgents.size() > 0)
    {
        wm->ourRobot[activeAgents.takeFirst()].Status = AgentStatus::Idle;
    }
}
