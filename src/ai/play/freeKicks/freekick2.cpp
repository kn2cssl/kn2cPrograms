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
    int leftID = -1, rightID = -1 , midID = -1;

    if( wm->ourRobot[tDefenderLeft->getID()].Role == AgentRole::DefenderLeft )
        leftID = tDefenderLeft->getID();

    if( wm->ourRobot[tDefenderRight->getID()].Role == AgentRole::DefenderRight )
        rightID = tDefenderRight->getID();

    if( leftChecker > 100 || leftID == -1 )
        midID = rightID;

    if( rightChecker > 100  || rightID == -1)
        midID = leftID;

    zonePositions(leftID,rightID,midID,goaliePos,leftDefPos,rightDefPos);

    tGolie->setIdlePosition(goaliePos);
    tDefenderLeft->setIdlePosition(leftDefPos);
    tDefenderRight->setIdlePosition(rightDefPos);

    if( leftID != -1)
    {
        if( (wm->ourRobot[leftID].pos.loc - leftDefPos.loc).length() > 250 )
            leftChecker++;
        else
            leftChecker = 0;
    }

    if( rightID != -1)
    {
        if( (wm->ourRobot[rightID].pos.loc - rightDefPos.loc).length() > 250 )
            rightChecker++;
        else
            rightChecker = 0;
    }

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
    if( wm->ourRobot[tAttackerLeft->getID()].isValid && tAttackerLeft->getID() != -1)
    {
        if( !wm->kn->ReachedToPos(wm->ourRobot[tAttackerLeft->getID()].pos.loc, leftPos.loc,150) )
            leftCheck = false;
    }

    if( wm->ourRobot[tAttackerRight->getID()].isValid && tAttackerRight->getID() != -1)
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
