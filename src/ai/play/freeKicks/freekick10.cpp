#include "freekick10.h"

freeKick10::freeKick10(WorldModel *wm, QObject *parent) :
    freeKick_base(wm ,parent)
{
    this->freeKickRegion = fkRegion::RightRegion;
    this->oppLevel = Level::Profesional;
    state = 0;
    counter = 0;
}

int freeKick10::enterCondition(Level level)
{
    if( (wm->kn->IsInsideRect(wm->ball.pos.loc, Vector2D(0.44*Field::MaxX,Field::MaxY)
                             , Vector2D(Field::MaxX,0.82*Field::MaxY))
            ||
            wm->kn->IsInsideRect(wm->ball.pos.loc, Vector2D(0.44*Field::MaxX,0.82*Field::MinY)
                                 , Vector2D(Field::MaxX,Field::MinY)))
            && (wm->kn->CountActiveAgents() == 6) )
        return 600;

    return 0;
}

void freeKick10::setPositions(QList<int> our)
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

    for(int i =0;i<our.size();i++)
    {
        if( state == 0)
        {
            switch (wm->ourRobot[our.at(i)].Role) {
            case AgentRole::AttackerLeft:
                tAttackerLeft->setIdlePosition(Vector2D(wm->ball.pos.loc.x-1000,wm->ball.pos.loc.y-sign(wm->ball.pos.loc.y)*800));
                break;
            case AgentRole::AttackerRight:
                tAttackerRight->setIdlePosition(Vector2D(wm->ball.pos.loc.x-1000,wm->ball.pos.loc.y-sign(wm->ball.pos.loc.y)*1600));
                break;
            case AgentRole::AttackerMid:
                tAttackerMid->setIdlePosition(Vector2D(wm->ball.pos.loc.x,wm->ball.pos.loc.y+sign(wm->ball.pos.loc.y)*200));
                break;
            default:
                break;
            }

            if( (wm->kn->ReachedToPos(wm->ourRobot[tAttackerLeft->getID()].pos.loc
                                      , Vector2D(wm->ball.pos.loc.x-1000,wm->ball.pos.loc.y-sign(wm->ball.pos.loc.y)*800),200) )
                    &&
                    (wm->kn->ReachedToPos(wm->ourRobot[tAttackerRight->getID()].pos.loc
                                          , Vector2D(wm->ball.pos.loc.x-1000,wm->ball.pos.loc.y-sign(wm->ball.pos.loc.y)*1600),200)) )
                state = 1;
        }
        else if(state == 1)
        {
            switch (wm->ourRobot[our.at(i)].Role) {
            case AgentRole::AttackerLeft:
                tAttackerLeft->setIdlePosition(Vector2D(wm->ball.pos.loc.x,wm->ball.pos.loc.y+sign(wm->ball.pos.loc.y)*200));
                break;
            case AgentRole::AttackerRight:
                tAttackerRight->setIdlePosition(Vector2D(wm->ball.pos.loc.x-200,wm->ball.pos.loc.y));
                break;
            case AgentRole::AttackerMid:
                tAttackerMid->setIdlePosition(Vector2D(wm->ball.pos.loc.x+200,wm->ball.pos.loc.y));
                break;
            default:
                break;
            }

            if( (wm->kn->ReachedToPos(wm->ourRobot[tAttackerLeft->getID()].pos.loc
                                      , Vector2D(wm->ball.pos.loc.x,wm->ball.pos.loc.y+sign(wm->ball.pos.loc.y)*200),100) )
                    &&
                    (wm->kn->ReachedToPos(wm->ourRobot[tAttackerRight->getID()].pos.loc
                                          , Vector2D(wm->ball.pos.loc.x-200,wm->ball.pos.loc.y),100)) )
                state = 2;
        }
        else if(state == 2)
        {
            switch (wm->ourRobot[our.at(i)].Role) {
            case AgentRole::AttackerLeft:
                tAttackerLeft->setIdlePosition(Vector2D(wm->ball.pos.loc.x,wm->ball.pos.loc.y+sign(wm->ball.pos.loc.y)*200));
                break;
            case AgentRole::AttackerRight:
                tAttackerRight->setIdlePosition(Vector2D(wm->ball.pos.loc.x-200,wm->ball.pos.loc.y));
                break;
            case AgentRole::AttackerMid:
                tAttackerMid->setIdlePosition(Vector2D(wm->ball.pos.loc.x+200,wm->ball.pos.loc.y));
                break;
            default:
                break;
            }

            if( counter > 50 )
                state = 3;
        }
        else if(state == 3)
        {
            switch (wm->ourRobot[our.at(i)].Role) {
            case AgentRole::AttackerLeft:tAttackerLeft->setIdlePosition(Vector2D(Field::MaxX*0.25,sign(wm->ball.pos.loc.y)*0.7*Field::MaxY));
                break;
            case AgentRole::AttackerRight:
                tAttackerRight->setIdlePosition(Vector2D(Field::MaxX*0.25,-sign(wm->ball.pos.loc.y)*0.7*Field::MaxY));
                break;
            case AgentRole::AttackerMid:
                tAttackerMid->setIdlePosition(Vector2D(wm->ball.pos.loc.x,wm->ball.pos.loc.y+sign(wm->ball.pos.loc.y)*200));
                break;
            default:
                break;
            }

            if( wm->kn->ReachedToPos(wm->ourRobot[tAttackerRight->getID()].pos.loc, Vector2D(Field::MaxX*0.25,-sign(wm->ball.pos.loc.y)*0.7*Field::MaxY), 1500)
                    &&
                    wm->kn->ReachedToPos(wm->ourRobot[tAttackerLeft->getID()].pos.loc, Vector2D(Field::MaxX*0.25,sign(wm->ball.pos.loc.y)*0.7*Field::MaxY), 800)
                    )
                state = 4;
        }
        else if( state == 4)
        {
            switch (wm->ourRobot[our.at(i)].Role) {
            case AgentRole::AttackerLeft:
                tAttackerLeft->setIdlePosition(Vector2D(Field::MaxX*0.25,sign(wm->ball.pos.loc.y)*0.7*Field::MaxY));
                break;
            case AgentRole::AttackerRight:
                tAttackerRight->setIdlePosition(Vector2D(Field::MaxX*0.25,-sign(wm->ball.pos.loc.y)*0.7*Field::MaxY));
                break;
            case AgentRole::AttackerMid:
                tAttackerMid->isKicker();
                tAttackerMid->youHavePermissionForKick(-1);
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
    this->counter = 0;
}

void freeKick10::execute()
{
    QList<int> activeAgents=wm->kn->ActiveAgents();

    //    if(!rolesIsInit)
    initRole();

    for(int i=0;i<activeAgents.size();i++)
        setTactics(activeAgents.at(i));

    tAttackerMid->isKicker(Vector2D(Field::MaxX*0.7,-sign(wm->ball.pos.loc.y)*0.7*Field::MaxY));
    tAttackerMid->setFreeKickType(kickType::FreeKick10);

    setPositions(activeAgents);

    if(state > 3)
        activeAgents.removeOne(tAttackerMid->getID());

    if( state == 2)
        counter++;

    //    wm->ourRobot[tAttackerLeft->getID()].Status = AgentStatus::RecievingPass;
    //    activeAgents.removeOne(tAttackerLeft->getID());

    //    wm->ourRobot[tAttackerRight->getID()].Status = AgentStatus::RecievingPass;
    //    activeAgents.removeOne(tAttackerRight->getID());

    while(activeAgents.size() > 0)
    {
        wm->ourRobot[activeAgents.takeFirst()].Status = AgentStatus::Idle;
    }
}
