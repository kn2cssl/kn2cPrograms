#include "freekick10.h"

freeKick10::freeKick10(WorldModel *wm, QObject *parent) :
    freeKick_base(wm ,parent)
{
    state = 0;
    this->freeKickRegion = fkRegion::CenterRegion;
    this->oppLevel = Level::Amatuer;
}

int freeKick10::enterCondition(Level level)
{
    if( wm->kn->IsInsideRect(wm->ball.pos.loc, Vector2D(0.33*Field::MinX,Field::MaxY)
                             , Vector2D(0.33*Field::MaxX,0.33*Field::MaxY))  )
    {
        if( level == this->oppLevel)
            return 600;
        else
            return 300;
    }

    return 0;
}

void freeKick10::setPositions(QList<int> our)
{
    Position leftDefPos,rightDefPos,goaliePos;
    zonePositions(tDefenderLeft->getID(),tDefenderRight->getID(),goaliePos,leftDefPos,rightDefPos);
    tDefenderLeft->setIdlePosition(leftDefPos);
    tDefenderRight->setIdlePosition(rightDefPos);
    tGolie->setIdlePosition(goaliePos);

    Position pos;

    for(int i =0;i<our.size();i++)
    {
        if( state == 0)
        {
            switch (wm->ourRobot[our.at(i)].Role) {
            case AgentRole::AttackerLeft:
                pos.loc = Vector2D( wm->ball.pos.loc.x - 300 , 0 );
                pos.dir = 0;
                tAttackerLeft->setIdlePosition(pos);

                if( wm->kn->ReachedToPos(wm->ourRobot[tAttackerLeft->getID()].pos.loc, Vector2D(wm->ball.pos.loc.x - 300,0),200))
                    state = 1;
                break;
            case AgentRole::AttackerRight:
                tAttackerRight->setIdlePosition(wm->ourRobot[tAttackerRight->getID()].pos);
                break;
            case AgentRole::AttackerMid:
                tAttackerMid->setIdlePosition(wm->ourRobot[tAttackerRight->getID()].pos);
                break;
            default:
                break;
            }

            if( (wm->kn->ReachedToPos(wm->ourRobot[tAttackerLeft->getID()].pos.loc
                                      , Vector2D(Field::MaxX -1200 ,sign(wm->ball.pos.loc.y)*Field::oppGoalCC_L.y),50))
                    &&
                    (wm->kn->ReachedToPos(wm->ourRobot[tAttackerRight->getID()].pos.loc
                                          , Vector2D(Field::MaxX -1200 ,-sign(wm->ball.pos.loc.y)*Field::oppGoalCC_L.y),50)) )
                state = 1;
        }
        else if(state == 1)
        {
            switch (wm->ourRobot[our.at(i)].Role) {
            case AgentRole::AttackerLeft:
                pos.loc = Vector2D( wm->ball.pos.loc.x-300, 0);
                pos.dir = 0;
                tAttackerLeft->setIdlePosition(pos);
                break;
            case AgentRole::AttackerRight:
                pos.loc = Vector2D( wm->ball.pos.loc.x-550, 0);
                pos.dir = 0;
                tAttackerRight->setIdlePosition(pos);
                break;
            case AgentRole::AttackerMid:
                tAttackerMid->setIdlePosition(wm->ourRobot[our.at(i)].pos);
                break;
            default:
                break;
            }
        }
        else if(state == 2)
        {
            switch (wm->ourRobot[our.at(i)].Role) {
            case AgentRole::AttackerLeft:
                pos.loc = Vector2D(0.6*Field::MaxX, -sign(wm->ball.pos.loc.y)*(0.6)*Field::MaxY);
                pos.dir = (Field::oppGoalCenter - wm->ourRobot[tAttackerLeft->getID()].pos.loc).dir().radian();

                if( wm->kn->ReachedToPos(wm->ourRobot[tAttackerLeft->getID()].pos.loc
                                         , Vector2D(0.6*Field::MaxX, -sign(wm->ball.pos.loc.y)*(0.6)*Field::MaxY),200))
                    state = 3;
                tAttackerLeft->setIdlePosition(pos);
                break;
            case AgentRole::AttackerRight:
                pos.loc = Vector2D(Field::MaxX -1200 ,-sign(wm->ball.pos.loc.y)*Field::oppGoalCC_L.y/*+sign(wm->ball.pos.loc.y)*200*/);
                pos.dir = 0;
                tAttackerRight->setIdlePosition(pos);
                break;
            case AgentRole::AttackerMid:
                tAttackerMid->setIdlePosition(wm->ourRobot[our.at(i)].pos);
                break;
            default:
                break;
            }
        }
        else if(state == 3)
        {
            switch (wm->ourRobot[our.at(i)].Role) {
            case AgentRole::AttackerLeft:
                pos.loc = Vector2D(0.6*Field::MaxX, -sign(wm->ball.pos.loc.y)*(0.6)*Field::MaxY);
                pos.dir = (Field::oppGoalCenter - wm->ourRobot[tAttackerLeft->getID()].pos.loc).dir().radian();
                tAttackerLeft->setIdlePosition(pos);
                break;
            case AgentRole::AttackerRight:
                pos.loc = Vector2D(Field::MaxX -1200 ,-sign(wm->ball.pos.loc.y)*Field::oppGoalCC_L.y);
                pos.dir = 0;
                tAttackerRight->setIdlePosition(pos);
                break;
            case AgentRole::AttackerMid:
                tAttackerMid->isKicker();
                tAttackerMid->setIdlePosition(wm->ourRobot[our.at(i)].pos);
                tAttackerMid->youHavePermissionForKick();
                break;
            default:
                break;
            }
        }
    }
}

void freeKick10::resetValues()
{
    this->rolesIsInit = false;
    this->state = 0;
}

void freeKick10::execute()
{
    QList<int> activeAgents=wm->kn->ActiveAgents();

//    if(!rolesIsInit)
        initRole();

    for(int i=0;i<activeAgents.size();i++)
        setTactics(activeAgents.at(i));

    tAttackerMid->isKicker(Vector2D(0.4*Field::MaxX, -sign(wm->ball.pos.loc.y)*(0.8)*Field::MaxY));
    tAttackerMid->waitTimerStart(true);

    setPositions(activeAgents);

    if(state != 0)
        activeAgents.removeOne(tAttackerMid->getID());

    while(activeAgents.size() > 0)
    {
        wm->ourRobot[activeAgents.takeFirst()].Status = AgentStatus::Idle;
    }
}
