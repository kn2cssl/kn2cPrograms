#include "freekick4.h"

freeKick4::freeKick4(WorldModel *wm, QObject *parent) :
    freeKick_base(wm ,parent)
{
    state = 0;
    this->freeKickRegion = fkRegion::RightRegion;
    this->oppLevel = Level::Amatuer;
}

int freeKick4::enterCondition(Level level)
{
    if( (wm->kn->IsInsideRect(wm->ball.pos.loc, Vector2D(0.33*Field::MaxX,Field::MaxY)
                              , Vector2D(Field::MaxX,0.33*Field::MaxY))
         ||
         wm->kn->IsInsideRect(wm->ball.pos.loc, Vector2D(0.33*Field::MaxX,0.33*Field::MinY)
                              , Vector2D(Field::MaxX,Field::MinY)))
            && (wm->kn->CountActiveAgents() == 6) )
    {
        if(wm->gs_last != wm->gs)
        {
            rolesIsInit = false;
            state = 0;
        }

        if( level == this->oppLevel)
            return 600;
        else
            return 300;
    }

    return 0;
}

void freeKick4::setPositions(QList<int> our)
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
                pos.loc = Vector2D(Field::MaxX -1200 ,sign(wm->ball.pos.loc.y)*Field::oppGoalCC_L.y);
                pos.dir = 0;
                tAttackerLeft->setIdlePosition(pos);
                break;
            case AgentRole::AttackerRight:
                pos.loc = Vector2D(Field::MaxX -1200 ,-sign(wm->ball.pos.loc.y)*Field::oppGoalCC_L.y);
                pos.dir = 0;
                tAttackerRight->setIdlePosition(pos);
                break;
            case AgentRole::AttackerMid:
                tAttackerMid->setIdlePosition(Vector2D(wm->ball.pos.loc.x-200,wm->ball.pos.loc.y));
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
                pos.loc = Vector2D(Field::MaxX -1350 ,-sign(wm->ball.pos.loc.y)*Field::oppGoalCC_L.y);

                if( wm->kn->ReachedToPos(wm->ourRobot[tAttackerLeft->getID()].pos.loc, Vector2D(Field::MaxX -1350 ,-sign(wm->ball.pos.loc.y)*Field::oppGoalCC_L.y), 200))
                {
                    state = 2;
                }

                pos.dir = (Field::oppGoalCenter - wm->ourRobot[tAttackerLeft->getID()].pos.loc).dir().radian();
                tAttackerLeft->setIdlePosition(pos);
                break;
            case AgentRole::AttackerRight:
                pos.loc = Vector2D(Field::MaxX -1200 ,-sign(wm->ball.pos.loc.y)*Field::oppGoalCC_L.y);
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
                tAttackerMid->setIdlePosition(wm->ourRobot[our.at(i)].pos);
                tAttackerMid->youHavePermissionForKick();
                break;
            default:
                break;
            }
        }
    }
}

void freeKick4::execute()
{
    QList<int> activeAgents=wm->kn->ActiveAgents();

//    if(!rolesIsInit)
        initRole();

    for(int i=0;i<activeAgents.size();i++)
        setTactics(activeAgents.at(i));

    setPositions(activeAgents);

    int recieverID = tAttackerLeft->getID();

    tAttackerMid->isKicker(Vector2D(0.4*Field::MaxX, -sign(wm->ball.pos.loc.y)*(0.8)*Field::MaxY));

    tAttackerMid->waitTimerStart(true);

    if(state != 0)
    {
        activeAgents.removeOne(tAttackerMid->getID());
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
