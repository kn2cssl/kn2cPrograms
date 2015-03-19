#include "freekick8.h"

freeKick8::freeKick8(WorldModel *wm, QObject *parent) :
    freeKick_base(wm ,parent)
{
    this->freeKickRegion = fkRegion::LeftRegion;
    this->oppLevel = Level::Amatuer;
}

int freeKick8::enterCondition(Level level)
{
    return 200;
}

void freeKick8::setPositions()
{
    Position leftDefPos,rightDefPos,goaliePos;
    zonePositions(tDefenderLeft->getID(),tDefenderRight->getID(),goaliePos,leftDefPos,rightDefPos);
    tDefenderLeft->setIdlePosition(leftDefPos);
    tDefenderRight->setIdlePosition(rightDefPos);
    tGolie->setIdlePosition(goaliePos);

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

void freeKick8::execute()
{
    QList<int> activeAgents=wm->kn->ActiveAgents();

    if(!rolesIsInit)
        initRole();

    for(int i=0;i<activeAgents.size();i++)
        setTactics(activeAgents.at(i));

    setPositions();

    target = Field::oppGoalCenter;
    tAttackerMid->isChiper(target);
    tAttackerMid->waitTimerStart(true);
    tAttackerMid->youHavePermissionForKick();
    activeAgents.removeOne(tAttackerMid->getID());

    while(activeAgents.size() > 0)
    {
        wm->ourRobot[activeAgents.takeFirst()].Status = AgentStatus::Idle;
    }
}
