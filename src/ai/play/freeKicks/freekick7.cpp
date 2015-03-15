#include "freekick7.h"

freeKick7::freeKick7(WorldModel *wm, QObject *parent) :
    freeKick_base(wm ,parent)
{
    state = 0;
    this->freeKickRegion = fkRegion::RightRegion;
    this->oppLevel = Level::Profesional;
}

int freeKick7::enterCondition(Level level)
{
    if( ( wm->kn->IsInsideRect(wm->ball.pos.loc, Vector2D(0.33*Field::MaxX,Field::MaxY)
                               , Vector2D(Field::MaxX,0.33*Field::MaxY))
          ||
          wm->kn->IsInsideRect(wm->ball.pos.loc, Vector2D(0.33*Field::MaxX,0.33*Field::MinY)
                               , Vector2D(Field::MaxX,Field::MinY)))
            && (wm->kn->CountActiveAgents() == 6)  )
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

void freeKick7::setPositions(QList<int> our)
{
    Position leftDefPos,rightDefPos,goaliePos;
    zonePositions(tDefenderLeft->getID(),tDefenderRight->getID(),goaliePos,leftDefPos,rightDefPos);
    tDefenderLeft->setIdlePosition(leftDefPos);
    tDefenderRight->setIdlePosition(rightDefPos);

    Position pos;

    for(int i =0;i<our.size();i++)
    {
        if( state == 0)
        {
            switch (wm->ourRobot[our.at(i)].Role) {
            case AgentRole::AttackerLeft:
                pos.loc = Vector2D(sign(wm->ball.pos.loc.x)*0.66*Field::MaxX ,sign(wm->ball.pos.loc.y)*200);
                pos.dir = 0;
                tAttackerLeft->setIdlePosition(pos);
                break;
            case AgentRole::AttackerRight:
                pos.loc = Vector2D(0.6*Field::MaxX, -sign(wm->ball.pos.loc.y)*(0.6)*Field::MaxY);
                pos.dir = (Field::oppGoalCenter - pos.loc).dir().radian();
                tAttackerRight->setIdlePosition(pos);
                break;
            case AgentRole::AttackerMid:
                tAttackerMid->setIdlePosition(Vector2D(wm->ball.pos.loc.x-200,wm->ball.pos.loc.y));
                break;
            case AgentRole::DefenderLeft:
                tDefenderLeft->setIdlePosition(wm->ourRobot[tDefenderLeft->getID()].pos);
                break;
            default:
                break;
            }
        }
        else if(state == 1)
        {
            switch (wm->ourRobot[our.at(i)].Role) {
            case AgentRole::AttackerLeft:
                pos.loc = Vector2D(sign(wm->ball.pos.loc.x)*200 ,sign(wm->ball.pos.loc.y)*200);
                pos.dir = (Field::oppGoalCenter - wm->ourRobot[tAttackerLeft->getID()].pos.loc).dir().radian();
                tAttackerLeft->setIdlePosition(pos);
                break;
            case AgentRole::AttackerRight:
                pos.loc = Vector2D(0.6*Field::MaxX, -sign(wm->ball.pos.loc.y)*(0.6)*Field::MaxY);
                pos.dir = (Field::oppGoalCenter - pos.loc).dir().radian();
                tAttackerRight->setIdlePosition(pos);
                break;
            case AgentRole::DefenderLeft:
                pos.loc = Vector2D(-sign(wm->ball.pos.loc.x)*50 ,-sign(wm->ball.pos.loc.y)*50);
                pos.dir = (Field::oppGoalCenter - wm->ourRobot[tDefenderLeft->getID()].pos.loc).dir().radian();
                tDefenderLeft->setIdlePosition(pos);
                break;
            default:
                break;
            }
        }
        else if(state == 2)
        {
            switch (wm->ourRobot[our.at(i)].Role) {
            case AgentRole::AttackerRight:
                pos.loc = Vector2D(0.6*Field::MaxX, -sign(wm->ball.pos.loc.y)*(0.6)*Field::MaxY);
                pos.dir = (Field::oppGoalCenter - pos.loc).dir().radian();
                tAttackerRight->setIdlePosition(pos);
                break;
            case AgentRole::AttackerLeft:
                pos.loc = Vector2D(0.3*Field::MaxX, -sign(wm->ball.pos.loc.y)*(0.6)*Field::MaxY);
                pos.dir = (Field::oppGoalCenter - pos.loc).dir().radian();
                tAttackerLeft->setIdlePosition(pos);

                if( wm->kn->ReachedToPos(wm->ourRobot[tAttackerLeft->getID()].pos.loc
                                         ,Vector2D(0.3*Field::MaxX, -sign(wm->ball.pos.loc.y)*(0.6)*Field::MaxY)
                                         , 200))
                    tAttackerMid->youHavePermissionForKick();
                break;
            default:
                break;
            }
        }
    }

    if( state == 0 && zeroCheckAttackersDistance() )
        state = 1;
    else if( state == 1 && firstCheckDistance() )
    {
        state = 2;
        AttackerLeft = tAttackerLeft->getID();
        DefenderLeft = tDefenderLeft->getID();
    }
}

bool freeKick7::zeroCheckAttackersDistance()
{
    if( (wm->kn->ReachedToPos(wm->ourRobot[tAttackerLeft->getID()].pos.loc
                              , Vector2D(sign(wm->ball.pos.loc.x)*0.66*Field::MaxX ,sign(wm->ball.pos.loc.y)*200),50))
            &&
            ( wm->kn->ReachedToPos(wm->ourRobot[tAttackerRight->getID()].pos.loc
                                   , Vector2D(0.6*Field::MaxX, -sign(wm->ball.pos.loc.y)*(0.6)*Field::MaxY),1000)))
        return true;

    return false;
}

bool freeKick7::firstCheckDistance()
{
    if( (wm->kn->ReachedToPos(wm->ourRobot[tAttackerLeft->getID()].pos.loc
                              , Vector2D(sign(wm->ball.pos.loc.x)*200 ,sign(wm->ball.pos.loc.y)*200),900))
            &&
            (wm->kn->ReachedToPos(wm->ourRobot[tDefenderLeft->getID()].pos.loc
                                  , Vector2D(-sign(wm->ball.pos.loc.x)*50 ,-sign(wm->ball.pos.loc.y)*50),400)) )
        return true;

    return false;
}

void freeKick7::initRolesB(int AttackerLeft, int DefenderLeft)
{
    wm->ourRobot[AttackerLeft].Role = AgentRole::DefenderLeft;
    wm->ourRobot[DefenderLeft].Role = AgentRole::AttackerLeft;
    tAttackerLeft->setID(DefenderLeft);
    tDefenderLeft->setID(AttackerLeft);
}

void freeKick7::execute()
{
    QList<int> activeAgents=wm->kn->ActiveAgents();

    if(!rolesIsInit)
        initRole();

    if( state == 2)
        initRolesB(AttackerLeft,DefenderLeft);

    for(int i=0;i<activeAgents.size();i++)
        setTactics(activeAgents.at(i));

    setPositions(activeAgents);

    int recieverID;

    tAttackerMid->isKicker(Vector2D(0.3*Field::MaxX, -sign(wm->ball.pos.loc.y)*(0.6)*Field::MaxY));
    tAttackerMid->waitTimerStart(true);

    if(state > 1)
    {
        recieverID = tAttackerLeft->getID();

        activeAgents.removeOne(tAttackerMid->getID());
        if(wm->cmgs.ourIndirectKick())
        {
            wm->ourRobot[recieverID].Status = AgentStatus::RecievingPass;
            activeAgents.removeOne(recieverID);
        }
    }
    else
    {
        if( state == 1)
            activeAgents.removeOne(tAttackerMid->getID());

        recieverID = tDefenderLeft->getID();
        wm->ourRobot[recieverID].Status = AgentStatus::RecievingPass;
        activeAgents.removeOne(recieverID);
    }

    while(activeAgents.size() > 0)
    {
        wm->ourRobot[activeAgents.takeFirst()].Status = AgentStatus::Idle;
    }
}
