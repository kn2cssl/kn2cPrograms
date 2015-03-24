#include "freekick11.h"

freeKick11::freeKick11(WorldModel *wm, QObject *parent) :
    freeKick_base(wm ,parent)
{
    state = 0;
    this->freeKickRegion = fkRegion::RightRegion;
    this->oppLevel = Level::Amatuer;
}

int freeKick11::enterCondition(Level level)
{
    if( (wm->kn->IsInsideRect(wm->ball.pos.loc, Vector2D(0.33*Field::MaxX,Field::MaxY)
                              , Vector2D(Field::MaxX,0.33*Field::MaxY))
         ||
         wm->kn->IsInsideRect(wm->ball.pos.loc, Vector2D(0.33*Field::MaxX,0.33*Field::MinY)
                              , Vector2D(Field::MaxX,Field::MinY)))
            && (wm->kn->CountActiveAgents() == 6) )
    {
        if( level == this->oppLevel)
            return 600;
        else
            return 300;
    }

    return 0;
}

void freeKick11::setPositions(QList<int> our)
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
                pos.loc = Vector2D(0.3*Field::MaxX, sign(wm->ball.pos.loc.y)*0.5*Field::MaxY);
                pos.dir = 0;
                tAttackerLeft->setIdlePosition(pos);
                break;
            case AgentRole::AttackerRight:
                pos.loc = Vector2D(0.3*Field::MaxX, 0);
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
                                      , Vector2D(0.3*Field::MaxX, sign(wm->ball.pos.loc.y)*0.5*Field::MaxY),100))
                    &&
                    (wm->kn->ReachedToPos(wm->ourRobot[tAttackerRight->getID()].pos.loc
                                          , Vector2D(0.3*Field::MaxX, 0),100)) )
                state = 1;
        }
        else if(state == 1)
        {
            switch (wm->ourRobot[our.at(i)].Role) {
            case AgentRole::AttackerLeft:
                pos.loc = Vector2D(0.3*Field::MaxX, 0 - 300);
                pos.dir = 0;
                tAttackerLeft->setIdlePosition(pos);

                if( wm->kn->ReachedToPos(wm->ourRobot[tAttackerLeft->getID()].pos.loc, Vector2D(0.3*Field::MaxX, 0 - 300), 400) )
                    state = 2;
                break;
            case AgentRole::AttackerRight:
                pos.loc = Vector2D(0.3*Field::MaxX, 0);
                pos.dir = 0;
                tAttackerRight->setIdlePosition(pos);
                break;
            case AgentRole::AttackerMid:
                tAttackerMid->setIdlePosition(Vector2D(wm->ball.pos.loc.x-200,wm->ball.pos.loc.y));
                break;
            default:
                break;
            }
        }
        else if(state == 2)
        {
            switch (wm->ourRobot[our.at(i)].Role) {
            case AgentRole::AttackerLeft:
                pos.loc = Vector2D(0.3*Field::MaxX, -sign(wm->ball.pos.loc.y)*0.7*Field::MaxY);
                pos.dir = 0;
                tAttackerLeft->setIdlePosition(pos);

                if( wm->kn->ReachedToPos(wm->ourRobot[tAttackerLeft->getID()].pos.loc, Vector2D(0.3*Field::MaxX, -sign(wm->ball.pos.loc.y)*0.7*Field::MaxY), 1000))
                    state = 3;
                break;
            case AgentRole::AttackerRight:
                pos.loc = Vector2D(0.3*Field::MaxX, 0);
                pos.dir = 0;
                tAttackerRight->setIdlePosition(pos);
                break;
            case AgentRole::AttackerMid:
                tAttackerMid->setIdlePosition(Vector2D(wm->ball.pos.loc.x-200,wm->ball.pos.loc.y));
                break;
            default:
                break;
            }
        }
        else if(state == 3)
        {
            switch (wm->ourRobot[our.at(i)].Role) {
            case AgentRole::AttackerLeft:
                pos.loc = Vector2D(0.3*Field::MaxX, -sign(wm->ball.pos.loc.y)*0.7*Field::MaxY);
                pos.dir = 0;
                tAttackerLeft->setIdlePosition(pos);
                break;
            case AgentRole::AttackerRight:
                pos.loc = Vector2D(0.3*Field::MaxX, 0);
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

void freeKick11::resetValues()
{
    this->rolesIsInit = false;
    this->state = 0;
}

void freeKick11::execute()
{
    QList<int> activeAgents=wm->kn->ActiveAgents();

    //    if(!rolesIsInit)
    initRole();

    for(int i=0;i<activeAgents.size();i++)
        setTactics(activeAgents.at(i));

    tAttackerMid->isKicker(Vector2D(0.4*Field::MaxX, -sign(wm->ball.pos.loc.y)*(0.8)*Field::MaxY));
    tAttackerMid->waitTimerStart(true);

    setPositions(activeAgents);

    if(state > 2)
        activeAgents.removeOne(tAttackerMid->getID());

    while(activeAgents.size() > 0)
    {
        wm->ourRobot[activeAgents.takeFirst()].Status = AgentStatus::Idle;
    }
}
