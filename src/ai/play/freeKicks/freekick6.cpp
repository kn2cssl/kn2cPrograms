#include "freekick6.h"

freeKick6::freeKick6(WorldModel *wm, QObject *parent) :
    freeKick_base(wm ,parent)
{
    this->freeKickRegion = fkRegion::LeftRegion;
    this->oppLevel = Level::Amatuer;
    rolesIsInit = false;
    state = 0;
}

int freeKick6::enterCondition(Level level)
{
    if( wm->kn->IsInsideRect(wm->ball.pos.loc, Vector2D(Field::MinX,Field::MaxY)
                             , Vector2D(0.44*Field::MinX,0.82*Field::MaxY))
            ||
            wm->kn->IsInsideRect(wm->ball.pos.loc, Vector2D(Field::MinX,0.82*Field::MinY)
                                 , Vector2D(0.44*Field::MinX,Field::MinY))
            )
    {
        if( level == this->oppLevel)
            return 600;
        else
            return 300;
    }

    return 0;
}

void freeKick6::setPositions()
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
            if( state != 0)
            {
                Vector2D first,second,final;
                Line2D t2t(wm->ball.pos.loc, Field::oppGoalCenter);
                Circle2D cir(wm->ball.pos.loc ,ALLOW_NEAR_BALL_RANGE+100);
                cir.intersection(t2t,&first,&second);
                if( wm->ball.pos.loc.x < first.x)
                    final = first;
                else
                    final = second;
                pos.loc = final;
                pos.dir = (Field::oppGoalCenter - wm->ball.pos.loc).dir().radian();
                tDefenderLeft->setIdlePosition(pos);

                if( wm->kn->ReachedToPos(wm->ourRobot[tDefenderLeft->getID()].pos.loc
                                         ,pos.loc, 95))
                state = 2;
            }
            break;
        case AgentRole::AttackerMid:
            if( state == 1)
            {
                pos.loc = Vector2D(wm->ball.pos.loc.x-200,wm->ball.pos.loc.y);
                pos.dir = 0;
                tAttackerMid->setIdlePosition(pos);
            }
            else if(state == 0)
                tAttackerMid->setIdlePosition(wm->ourRobot[tAttackerMid->getID()].pos);
            break;
        default:
            break;
        }
    }
}

bool freeKick6::checkAttackersDistance()
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

void freeKick6::resetValues()
{
    this->state = 0;
    this->rolesIsInit = false;
}

void freeKick6::execute()
{
    QList<int> activeAgents=wm->kn->ActiveAgents();

//    if(!rolesIsInit)
        initRole();

    for(int i=0;i<activeAgents.size();i++)
        setTactics(activeAgents.at(i));

    setPositions();

    int recieverID = tDefenderLeft->getID();

    target = Field::oppGoalCenter;
    tAttackerMid->isChiper(target);
    tAttackerMid->setFreeKickType(kickType::FreeKick6);

    if(state > 1)
    {
        activeAgents.removeOne(tAttackerMid->getID());
        wm->ourRobot[recieverID].Status = AgentStatus::RecievingPass;
        activeAgents.removeOne(recieverID);
        tAttackerMid->youHavePermissionForKick(-1);
    }
    else if( state == 1)
    {
        if(wm->cmgs.ourIndirectKick())
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
