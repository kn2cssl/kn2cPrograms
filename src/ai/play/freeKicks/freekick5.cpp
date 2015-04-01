#include "freekick5.h"

freeKick5::freeKick5(WorldModel *wm, QObject *parent) :
    freeKick_base(wm ,parent)
{
    this->freeKickRegion = fkRegion::CenterRegion;
    this->oppLevel = Level::Amatuer;
    state = 0;
    rolesIsInit = false;
}

int freeKick5::enterCondition(Level level)
{
    if( wm->kn->IsInsideRect(wm->ball.pos.loc, Vector2D(0.44*Field::MinX,Field::MaxY)
                             , Vector2D(0.44*Field::MaxX,0.82*Field::MaxY))
            ||
            wm->kn->IsInsideRect(wm->ball.pos.loc, Vector2D(0.44*Field::MinX,0.82*Field::MinY)
                                         , Vector2D(0.44*Field::MaxX,Field::MinY)))
    {
        if( level == this->oppLevel)
            return 600;
        else
            return 300;
    }

    return 0;
}

void freeKick5::setPositions()
{
    Position leftDefPos,rightDefPos,goaliePos;
    int leftID = -1, rightID = -1 , midID = -1;
    bool rightNav , leftNav;

    if( wm->ourRobot[tDefenderLeft->getID()].Role == AgentRole::DefenderLeft )
        leftID = tDefenderLeft->getID();

    if( wm->ourRobot[tDefenderRight->getID()].Role == AgentRole::DefenderRight )
        rightID = tDefenderRight->getID();

    if( leftChecker > 100 || leftID == -1 )
        midID = rightID;

    if( rightChecker > 100  || rightID == -1)
        midID = leftID;

    zonePositions(leftID,rightID,midID,goaliePos,leftDefPos,leftNav,rightDefPos,rightNav);

    tGolie->setIdlePosition(goaliePos);
    tDefenderLeft->setIdlePosition(leftDefPos);
    tDefenderLeft->setUseNav(leftNav);
    tDefenderRight->setIdlePosition(rightDefPos);
    tDefenderRight->setUseNav(rightNav);

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

    Position pos;

    QList<int> ourAttackers = wm->kn->findAttackers();
    ourAttackers.removeOne(tAttackerMid->getID());

    QList<int> ourPlayers = wm->kn->ActiveAgents();
    Positioning voronoi;
    voronoi.setWorldModel(wm);
    bool isMatched;

    QList<Positioning_Struct> positions = voronoi.kickPositions(ourAttackers,target,isMatched);

    for(int i=0;i<positions.size();i++)
    {
        Positioning_Struct tmp = positions.at(i);
        ourPlayers.removeOne(tmp.ourI);

        switch (wm->ourRobot[tmp.ourI].Role) {
        case AgentRole::AttackerLeft:
            pos.loc = tmp.loc;
            pos.dir = (Field::oppGoalCenter - pos.loc).dir().radian();
            tAttackerLeft->setIdlePosition(pos);
            break;
        case AgentRole::AttackerRight:
            pos.loc = tmp.loc;
            pos.dir = (Field::oppGoalCenter - pos.loc).dir().radian();
            tAttackerRight->setIdlePosition(pos);
            break;
        default:
            break;
        }
    }

    if( state == 0)
    {
        if( checkAttackersDistance() )
            state = 1;
    }

    for(int i=0;i<ourPlayers.size();i++)
    {
        switch (wm->ourRobot[ourPlayers.at(i)].Role) {
        case AgentRole::DefenderLeft:
            if(state == 2)
            {
                pos.loc = Vector2D(wm->ball.pos.loc.x-2000, -wm->ball.pos.loc.y);
                pos.dir = (Field::oppGoalCenter - pos.loc).dir().radian();
                tDefenderLeft->setIdlePosition(pos);
            }
            break;
        case AgentRole::AttackerMid:
            if( state == 1)
            {
                pos.loc = Vector2D(wm->ball.pos.loc.x-100,wm->ball.pos.loc.y);
                pos.dir = 0;
                tAttackerMid->setIdlePosition(pos);

                if( wm->kn->ReachedToPos(wm->ourRobot[tAttackerMid->getID()].pos.loc
                                         ,Vector2D(wm->ball.pos.loc.x-100,wm->ball.pos.loc.y)
                                         , 95))
                {
                    state = 2;
                }
            }
            else if(state == 0)
                tAttackerMid->setIdlePosition(wm->ourRobot[tAttackerMid->getID()].pos);
            break;
        default:
            break;
        }
    }
}

bool freeKick5::checkAttackersDistance()
{
    bool left = false,right = false;

    if( wm->ourRobot[tAttackerLeft->getID()].isValid )
    {
        if( (wm->ourRobot[tAttackerLeft->getID()].pos.loc - wm->ourRobot[tAttackerMid->getID()].pos.loc).length() > 300)
            left = true;
    }
    else
        left = true;

    if( wm->ourRobot[tAttackerRight->getID()].isValid )
    {
        if( (wm->ourRobot[tAttackerRight->getID()].pos.loc - wm->ourRobot[tAttackerMid->getID()].pos.loc).length() > 300 )
            right = true;
    }
    else
        right = true;

    return left&right;
}

void freeKick5::resetValues()
{
    this->rolesIsInit = false;
    this->state = 0;
}

void freeKick5::execute()
{
    QList<int> activeAgents=wm->kn->ActiveAgents();

//    if(!rolesIsInit)
        initRole();

    for(int i=0;i<activeAgents.size();i++)
        setTactics(activeAgents.at(i));

    setPositions();

    int recieverID = tDefenderLeft->getID();

    target = Vector2D(wm->ball.pos.loc.x-2000,-wm->ball.pos.loc.y);
    tAttackerMid->isKicker(target);
    tAttackerMid->setFreeKickType(kickType::FreeKick5);

    if(state > 1)
    {
        activeAgents.removeOne(tAttackerMid->getID());
        if(wm->cmgs.ourIndirectKick())
        {
            wm->ourRobot[recieverID].Status = AgentStatus::RecievingPass;
            activeAgents.removeOne(recieverID);
        }
        tAttackerMid->youHavePermissionForKick();
    }

    while(activeAgents.size() > 0)
    {
        wm->ourRobot[activeAgents.takeFirst()].Status = AgentStatus::Idle;
    }
}
