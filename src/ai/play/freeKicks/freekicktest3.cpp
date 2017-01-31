#include "freekicktest3.h"
#include "freekick1.h"

freeKick1::freeKick1(WorldModel *worldmodel, QObject *parent) :
    freeKick_base(worldmodel,parent)
{
    freeKickStart = false;
    freeKickRegion = fkRegion::RightRegion;
    oppLevel = Level::Beginner;
}

int freeKick1::enterCondition(Level level)
{
    if( wm->kn->IsInsideRect(wm->ball.pos.loc, Vector2D(0.44*Field::MaxX,Field::MaxY)
                             , Vector2D(Field::MaxX,0.82*Field::MaxY))
            ||
            wm->kn->IsInsideRect(wm->ball.pos.loc, Vector2D(0.44*Field::MaxX,0.82*Field::MinY)
                                 , Vector2D(Field::MaxX,Field::MinY)))
    {
        if( level == this->oppLevel)
            return 600;
        else
            return 300;
    }

    return 0;
}

void freeKick1::resetValues()
{
    this->rolesIsInit = false;
}

void freeKick1::setPositions()
{
    Position leftDefPos,rightDefPos,goaliePos;
    int leftID = -1, rightID = -1 , midID = -1;
    bool leftNav, rightNav;

    if( wm->ourRobot[previousLeftID].Role != AgentRole::DefenderLeft )
        previousLeftID = -1;

    if( wm->ourRobot[previousRightID].Role != AgentRole::DefenderRight )
        previousRightID = -1;

    if( (wm->ourRobot[tDefenderLeft->getID()].Role == AgentRole::DefenderLeft) && (leftChecker < PresenceCounter) )
    {
        leftID = tDefenderLeft->getID();
        this->previousLeftID = tDefenderLeft->getID();;
    }

    if( wm->ourRobot[tDefenderRight->getID()].Role == AgentRole::DefenderRight && (rightChecker < PresenceCounter) )
    {
        rightID = tDefenderRight->getID();
        this->previousRightID = tDefenderRight->getID();;
    }

    if( leftChecker > PresenceCounter || leftID == -1 || !wm->kn->robotIsIdle(leftID))
    {
        midID = rightID;
        leftID = -1;
    }

    if( rightChecker > PresenceCounter  || rightID == -1 || !wm->kn->robotIsIdle(rightID))
    {
        midID = leftID;
        rightID = -1;
    }

    zonePositions(leftID,rightID,midID,goaliePos,leftDefPos,leftNav,rightDefPos,rightNav);

    tDefenderLeft->setIdlePosition(leftDefPos);
    tDefenderLeft->setUseNav(leftNav);
    tDefenderRight->setIdlePosition(rightDefPos);
    tDefenderRight->setUseNav(rightNav);

    if( leftID != -1)
    {
        if( (wm->kn->robotIsIdle(leftID)) && (wm->ourRobot[leftID].pos.loc - leftDefPos.loc).length() > 250 )
            leftChecker++;
        else
            leftChecker = 0;
    }
    else
    {
        if( !haltedRobotIsInField(previousLeftID) )
            leftChecker = 0;
    }

    if( rightID != -1)
    {
        if( (wm->kn->robotIsIdle(rightID)) && (wm->ourRobot[rightID].pos.loc - rightDefPos.loc).length() > 250 )
            rightChecker++;
        else
            rightChecker = 0;
    }
    else
    {
        if( !haltedRobotIsInField(previousRightID) )
            rightChecker = 0;
    }

    tGolie->setIdlePosition(goaliePos);

    Position left,right;
    if( wm->ball.pos.loc.y < 0 )
    {
        left.loc = Vector2D(Field::MaxX/3,wm->ball.pos.loc.y+200);
        right.loc = Vector2D(Field::MaxX/3,Field::oppGoalCenter.y+400);
    }
    else
    {
        left.loc = Vector2D(Field::MaxX/3,wm->ball.pos.loc.y-200);
        right.loc = Vector2D(Field::MaxX/3,Field::oppGoalCenter.y-400);
    }

    left.dir = ( Field::oppGoalCenter - wm->ourRobot[tAttackerLeft->getID()].pos.loc).dir().radian();
    tAttackerLeft->setIdlePosition(left);

    right.dir = ( Field::oppGoalCenter - wm->ourRobot[tAttackerRight->getID()].pos.loc).dir().radian();
    tAttackerRight->setIdlePosition(right);

    leftPos = left;
    rightPos = right;

    tAttackerMid->setIdlePosition(wm->ourRobot[tAttackerMid->getID()].pos);

    if( checkDistances() )
    {
        recieverID = tAttackerMid->findBestPlayerForPass();
        tAttackerMid->youHavePermissionForKick(recieverID);
    }
    else
    {
        tAttackerMid->youDontHavePermissionForKick();
        recieverID = -1;
    }
}

bool freeKick1::checkDistances()
{
    bool leftInPos = true , rightInPos = true;

    if( wm->ourRobot[tAttackerLeft->getID()].isValid && tAttackerLeft->getID() != -1)
    {
        //if( !wm->kn->ReachedToPos(wm->ourRobot[tAttackerLeft->getID()].pos.loc, Vector2D(Field::MaxX/3,Field::oppGoalPost_L.y+200), 200))
        if( (wm->ourRobot[tAttackerLeft->getID()].pos.loc - leftPos.loc).length() > 200)
            leftInPos = false;
    }

    if( wm->ourRobot[tAttackerRight->getID()].isValid && tAttackerRight->getID() != -1)
    {
        //        if( !wm->kn->ReachedToPos(wm->ourRobot[tAttackerRight->getID()].pos.loc, Vector2D(Field::MaxX/3,Field::oppGoalPost_R.y-200),200) )
        if( (wm->ourRobot[tAttackerRight->getID()].pos.loc - rightPos.loc).length() > 200)
            rightInPos = false;
    }

    return (rightInPos && leftInPos);
}

void freeKick1::execute()
{
    QList<int> activeAgents=wm->kn->ActiveAgents();

    //    if(!rolesIsInit)
    initRole();

    for(int i=0;i<activeAgents.size();i++)
        setTactics(activeAgents.at(i));


    setPositions();

    tAttackerMid->isKicker();
    tAttackerMid->setFreeKickType(kickType::FreeKick1);

    activeAgents.removeOne(tAttackerMid->getID());
    if(wm->cmgs.ourIndirectKick())
    {
        recieverID = tAttackerMid->findBestPlayerForPass();
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
