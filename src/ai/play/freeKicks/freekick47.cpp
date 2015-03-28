#include "freekick47.h"

freeKick47::freeKick47(WorldModel *wm, QObject *parent) :
    freeKick_base(wm ,parent)
{
    state = 0;
    this->freeKickRegion = fkRegion::RightRegion;
    this->oppLevel = Level::Profesional;
    AttackerRight = -1;
    DefenderLeft = -1;
}

int freeKick47::enterCondition(Level level)
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

void freeKick47::setPositions(QList<int> our)
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

    Position pos;

    for(int i =0;i<our.size();i++)
    {
        if( state == 0)
        {
            switch (wm->ourRobot[our.at(i)].Role) {
            case AgentRole::AttackerLeft:
                pos.loc = Vector2D(Field::MaxX -1600 ,sign(wm->ball.pos.loc.y)*Field::oppGoalCC_L.y);
                pos.dir = 0;
                tAttackerLeft->setIdlePosition(pos);
                break;
            case AgentRole::AttackerRight:
                pos.loc = Vector2D(Field::MaxX -1600 ,-sign(wm->ball.pos.loc.y)*Field::oppGoalCC_L.y);
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
                                      , Vector2D(Field::MaxX -1600 ,sign(wm->ball.pos.loc.y)*Field::oppGoalCC_L.y),50))
                    &&
                    (wm->kn->ReachedToPos(wm->ourRobot[tAttackerRight->getID()].pos.loc
                                          , Vector2D(Field::MaxX -1600 ,-sign(wm->ball.pos.loc.y)*Field::oppGoalCC_L.y),50)) )
                state = 1;
        }
        else if(state == 1)
        {
            switch (wm->ourRobot[our.at(i)].Role) {
            case AgentRole::AttackerLeft:
                pos.loc = Vector2D(Field::MaxX -1750 ,-sign(wm->ball.pos.loc.y)*Field::oppGoalCC_L.y);

                if( wm->kn->ReachedToPos(wm->ourRobot[tAttackerLeft->getID()].pos.loc, Vector2D(Field::MaxX -1750 ,-sign(wm->ball.pos.loc.y)*Field::oppGoalCC_L.y), 200))
                {
                    state = 2;
                }

                pos.dir = (Field::oppGoalCenter - wm->ourRobot[tAttackerLeft->getID()].pos.loc).dir().radian();
                tAttackerLeft->setIdlePosition(pos);
                break;
            case AgentRole::AttackerRight:
                pos.loc = Vector2D(Field::MaxX -1600 ,-sign(wm->ball.pos.loc.y)*Field::oppGoalCC_L.y);
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
                pos.loc = Vector2D(0.6*Field::MaxX, -sign(wm->ball.pos.loc.y)*(0.6)*Field::MaxY);
                pos.dir = (Field::oppGoalCenter - wm->ourRobot[tAttackerLeft->getID()].pos.loc).dir().radian();

                if( wm->kn->ReachedToPos(wm->ourRobot[tAttackerLeft->getID()].pos.loc
                                         , Vector2D(0.6*Field::MaxX, -sign(wm->ball.pos.loc.y)*(0.6)*Field::MaxY),900))
                    state = 3;
                tAttackerLeft->setIdlePosition(pos);
                break;
            case AgentRole::AttackerRight:
                pos.loc = Vector2D(Field::MaxX -1600 ,-sign(wm->ball.pos.loc.y)*Field::oppGoalCC_L.y/*+sign(wm->ball.pos.loc.y)*200*/);
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
                pos.loc = Vector2D(0.6*Field::MaxX, -sign(wm->ball.pos.loc.y)*(0.6)*Field::MaxY);
                pos.dir = (Field::oppGoalCenter - wm->ourRobot[tAttackerLeft->getID()].pos.loc).dir().radian();
                tAttackerLeft->setIdlePosition(pos);
                break;
            case AgentRole::AttackerRight:
                pos.loc = Vector2D(sign(wm->ball.pos.loc.x)*200 ,sign(wm->ball.pos.loc.y)*200);
                pos.dir = (Field::oppGoalCenter - wm->ourRobot[tAttackerLeft->getID()].pos.loc).dir().radian();
                tAttackerRight->setIdlePosition(pos);
                break;
            case AgentRole::AttackerMid:
                tAttackerMid->setIdlePosition(Vector2D(wm->ball.pos.loc.x-200,wm->ball.pos.loc.y));
                break;
            case AgentRole::DefenderLeft:
                pos.loc = Vector2D(-sign(wm->ball.pos.loc.x)*50 ,-sign(wm->ball.pos.loc.y)*50);
                pos.dir = (Field::oppGoalCenter - wm->ourRobot[tDefenderLeft->getID()].pos.loc).dir().radian();
                tDefenderLeft->setIdlePosition(pos);
                break;
            default:
                break;
            }

            if( (wm->kn->ReachedToPos(wm->ourRobot[tAttackerRight->getID()].pos.loc
                                      , Vector2D(sign(wm->ball.pos.loc.x)*200 ,sign(wm->ball.pos.loc.y)*200),900))
                    &&
                    (wm->kn->ReachedToPos(wm->ourRobot[tDefenderLeft->getID()].pos.loc
                                          , Vector2D(-sign(wm->ball.pos.loc.x)*50 ,-sign(wm->ball.pos.loc.y)*50),400)) )
            {
                AttackerRight = tAttackerRight->getID();
                DefenderLeft = tDefenderLeft->getID();
                state = 4;
            }
        }
        else if( state == 4)
        {
            switch (wm->ourRobot[our.at(i)].Role) {
            case AgentRole::AttackerLeft:
                pos.loc = Vector2D(0.6*Field::MaxX, -sign(wm->ball.pos.loc.y)*(0.6)*Field::MaxY);
                pos.dir = (Field::oppGoalCenter - wm->ourRobot[tAttackerLeft->getID()].pos.loc).dir().radian();
                tAttackerLeft->setIdlePosition(pos);
                break;
            case AgentRole::AttackerRight:
                pos.loc = Vector2D(0.3*Field::MaxX, -sign(wm->ball.pos.loc.y)*(0.6)*Field::MaxY);
                pos.dir = (Field::oppGoalCenter - pos.loc).dir().radian();
                tAttackerRight->setIdlePosition(pos);

                if( wm->kn->ReachedToPos(wm->ourRobot[tAttackerRight->getID()].pos.loc
                                         ,Vector2D(0.3*Field::MaxX, -sign(wm->ball.pos.loc.y)*(0.6)*Field::MaxY)
                                         , 400))
                        state = 5;
                break;
            case AgentRole::AttackerMid:
                tAttackerMid->setIdlePosition(Vector2D(wm->ball.pos.loc.x-200,wm->ball.pos.loc.y));
                break;
            default:
                break;
            }
        }
        else if( state == 5)
        {
            switch (wm->ourRobot[our.at(i)].Role) {
            case AgentRole::AttackerLeft:
                pos.loc = Vector2D(0.6*Field::MaxX, -sign(wm->ball.pos.loc.y)*(0.6)*Field::MaxY);
                pos.dir = (Field::oppGoalCenter - wm->ourRobot[tAttackerLeft->getID()].pos.loc).dir().radian();
                tAttackerLeft->setIdlePosition(pos);
                break;
            case AgentRole::AttackerRight:
                pos.loc = Vector2D(0.3*Field::MaxX, -sign(wm->ball.pos.loc.y)*(0.6)*Field::MaxY);
                pos.dir = (Field::oppGoalCenter - pos.loc).dir().radian();
                tAttackerRight->setIdlePosition(pos);
                break;
            case AgentRole::AttackerMid:
                tAttackerMid->isKicker();
                tAttackerMid->youHavePermissionForKick();
                break;
            default:
                break;
            }
        }
    }
}

void freeKick47::initRolesB(int AttackerRight, int DefenderLeft)
{
    wm->ourRobot[AttackerRight].Role = AgentRole::DefenderLeft;
    wm->ourRobot[DefenderLeft].Role = AgentRole::AttackerRight;
    tAttackerRight->setID(DefenderLeft);
    tDefenderLeft->setID(AttackerRight);
}

void freeKick47::resetValues()
{
    this->rolesIsInit = false;
    this->state = 0;
}

void freeKick47::execute()
{
    QList<int> activeAgents=wm->kn->ActiveAgents();

//    if(!rolesIsInit)
        initRole();

        if( state  > 3)
            initRolesB(AttackerRight,DefenderLeft);

    for(int i=0;i<activeAgents.size();i++)
        setTactics(activeAgents.at(i));

    tAttackerMid->isKicker(Vector2D(0.3*Field::MaxX, -sign(wm->ball.pos.loc.y)*(0.6)*Field::MaxY));

    setPositions(activeAgents);

    if(state > 3)
        activeAgents.removeOne(tAttackerMid->getID());

    while(activeAgents.size() > 0)
    {
        wm->ourRobot[activeAgents.takeFirst()].Status = AgentStatus::Idle;
    }
}
