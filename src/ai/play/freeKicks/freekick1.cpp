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

    tAttackerLeft->setIdlePosition(Vector2D(Field::MaxX/3,Field::oppGoalPost_L.y+200));
    tAttackerRight->setIdlePosition(Vector2D(Field::MaxX/3,Field::oppGoalPost_R.y-200));
    tAttackerMid->setIdlePosition(wm->ourRobot[tAttackerMid->getID()].pos);

    if( checkDistances() )
        tAttackerMid->youHavePermissionForKick();
}

bool freeKick1::checkDistances()
{
    bool leftInPos = true , rightInPos = true;

    if( wm->ourRobot[tAttackerLeft->getID()].isValid && tAttackerLeft->getID() != -1)
    {
        if( !wm->kn->ReachedToPos(wm->ourRobot[tAttackerLeft->getID()].pos.loc, Vector2D(Field::MaxX/3,Field::oppGoalPost_L.y+200), 200))
            leftInPos = false;
    }

    if( wm->ourRobot[tAttackerRight->getID()].isValid && tAttackerRight->getID() != -1)
    {
        if( !wm->kn->ReachedToPos(wm->ourRobot[tAttackerRight->getID()].pos.loc, Vector2D(Field::MaxX/3,Field::oppGoalPost_R.y-200),200) )
            rightInPos = false;
    }

    return rightInPos & leftInPos;
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
