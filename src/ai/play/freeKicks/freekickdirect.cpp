#include "freekickdirect.h"

freeKickDirect::freeKickDirect(WorldModel *wm, QObject *parent) :
    freeKick_base(wm ,parent)
{
    this->freeKickRegion = fkRegion::LeftRegion;
    this->oppLevel = Level::Amatuer;
}

int freeKickDirect::enterCondition(Level level)
{
    tANDp tandp = tAttackerMid->findTarget();

    if( wm->cmgs.directKick() && (tandp.prob > 40) )
        return 800;
    else if( wm->cmgs.ourIndirectKick() && (wm->kn->IsInsideRect(wm->ball.pos.loc, Vector2D(0.44*Field::MaxX,Field::MaxY)
                                  , Vector2D(Field::MaxX,0.82*Field::MaxY))
             ||
             wm->kn->IsInsideRect(wm->ball.pos.loc, Vector2D(0.44*Field::MaxX,0.82*Field::MinY)
                                  , Vector2D(Field::MaxX,Field::MinY))))
        return -10;

    return 10;
}

void freeKickDirect::setPositions()
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

    Positioning voronoi;
    voronoi.setWorldModel(wm);
    bool isMatched;

    QList<Positioning_Struct> positions = voronoi.find_positions(ourAttackers,isMatched);

    for(int i=0;i<positions.size();i++)
    {
        Positioning_Struct tmp = positions.at(i);

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
}

void freeKickDirect::resetValues()
{
    this->rolesIsInit = false;
    this->state = 0;
}

void freeKickDirect::execute()
{
    QList<int> activeAgents=wm->kn->ActiveAgents();

    //    if(!rolesIsInit)
    initRole();

    for(int i=0;i<activeAgents.size();i++)
        setTactics(activeAgents.at(i));

    setPositions();

    target = Field::oppGoalCenter;
    tAttackerMid->isKicker(target);
    tAttackerMid->setFreeKickType(kickType::Shoot);
    tAttackerMid->youHavePermissionForKick(-1);
    activeAgents.removeOne(tAttackerMid->getID());

    while(activeAgents.size() > 0)
    {
        wm->ourRobot[activeAgents.takeFirst()].Status = AgentStatus::Idle;
    }
}
