#include "tacticattacker.h"


TacticAttacker::TacticAttacker(WorldModel *worldmodel, QObject *parent) :
    Tactic("TacticAttacker", worldmodel, parent)
{
    everyOneInTheirPos = false;

    waitTimer = new QTimer();
    connect(waitTimer,SIGNAL(timeout()),this,SLOT(dontWait()));
}

RobotCommand TacticAttacker::getCommand()
{
    RobotCommand rc;
    if(!wm->ourRobot[id].isValid) return rc;

    if(wm->ourRobot[id].Status == AgentStatus::FollowingBall)
    {
        Vector2D v;
//        if( wm->ball.vel.loc.length() > 0.5 )
            v = wm->kn->PredictDestination(wm->ourRobot[this->id].pos.loc,
                    wm->ball.pos.loc,rc.maxSpeed,wm->ball.vel.loc);
//        else
//            v = wm->ball.pos.loc;

        tANDp target = findTarget();
        OperatingPosition p = wm->kn->AdjustKickPointB(v, target.pos,wm->ourRobot[this->id].pos);
        qDebug()<<wm->ball.vel.loc.length();
        //        qDebug()<<"Distance "<<(wm->ourRobot[this->id].pos.loc - wm->ball.pos.loc).length();
        if( p.readyToShoot )
        {
            qDebug()<<"KKKKKKKKKKIIIIIIIIIIIIIIIIIIICKKKKKKKKKKKKKKKKKKKK";
            rc.kickspeedx = detectKickSpeed(target.pos);
        }

        rc.maxSpeed = 2;
        rc.fin_pos = p.pos;
        rc.useNav = p.useNav;
        rc.isBallObs = true;
        rc.isKickObs = true;
    }
    else if(wm->ourRobot[id].Status == AgentStatus::Kicking)
    {
        if(wm->gs == STATE_Indirect_Free_kick_Our)
        {
            rc = KickTheBallIndirect();
        }
        else if(wm->gs == STATE_Free_kick_Our)
        {
            rc = KickTheBallDirect();
        }
        else if(wm->gs == STATE_Start)
        {
            rc = StartTheGame();
        }

        rc.isBallObs = true;
        rc.isKickObs = true;
    }
    else if(wm->ourRobot[id].Status == AgentStatus::RecievingPass)
    {
        rc.fin_pos = idlePosition;

        rc.maxSpeed = 1.5;

        rc.useNav = true;
        rc.isBallObs = true;
        rc.isKickObs = true;
    }
    else if(wm->ourRobot[id].Status == AgentStatus::BlockingRobot)
    {
        AngleDeg desiredDeg =  (wm->oppRobot[playerToKeep].pos.loc-Field::ourGoalCenter).dir();
        Position final;
        final.loc.x = wm->oppRobot[playerToKeep].pos.loc.x - (300*cos(desiredDeg.radian()));
        final.loc.y = wm->oppRobot[playerToKeep].pos.loc.y - (300*sin(desiredDeg.radian()));
        final.dir = desiredDeg.radian();

        if( wm->gs == GameStateType::STATE_Free_kick_Opp || wm->gs == GameStateType::STATE_Indirect_Free_kick_Opp)
        {
            if( wm->kn->IsInsideSecureArea(final.loc,wm->ball.pos.loc) )
            {
                Vector2D fstInt,secInt;
                Circle2D secArea(wm->ball.pos.loc,ALLOW_NEAR_BALL_RANGE);
//                Line2D connectedLine(wm->ball.pos.loc,final.loc);
                Line2D connectedLine(wm->oppRobot[playerToKeep].pos.loc,Field::ourGoalCenter);
                int numberOfIntersections = secArea.intersection(connectedLine,&fstInt,&secInt);

                if( numberOfIntersections == 2 )
                {
                    if( (fstInt-final.loc).length() > (secInt-final.loc).length() )
                        rc.fin_pos.loc = secInt;
                    else
                        rc.fin_pos.loc = fstInt;
                }
                else if( numberOfIntersections == 1 )
                {
                    rc.fin_pos.loc = fstInt;
                }
                else
                    rc.fin_pos = wm->ourRobot[this->id].pos;
            }
            else
            {
                rc.fin_pos = final;
            }
        }
        else
        {
            rc.fin_pos = final;
        }

        rc.maxSpeed = 2;

        rc.useNav = true;
        rc.isBallObs = true;
        rc.isKickObs = true;
    }
    else if(wm->ourRobot[id].Status == AgentStatus::Idle)
    {
        rc.fin_pos = idlePosition;

        rc.maxSpeed = 1;

        rc.useNav = true;
        rc.isBallObs = true;
        rc.isKickObs = true;

        if( wm->gs == STATE_Stop )
            return rc;
    }

    if( wm->kn->IsInsideGolieArea(rc.fin_pos.loc) )
    {
        Circle2D attackerCircles(Field::ourGoalCenter , Field::goalCircle_R+300);
        Line2D robotRay(wm->oppRobot[playerToKeep].pos.loc,wm->ourRobot[this->id].pos.loc);
        Vector2D firstPoint,secondPoint;
        attackerCircles.intersection(robotRay,&firstPoint,&secondPoint);

        if( (wm->oppRobot[this->id].pos.loc-firstPoint).length() < (wm->oppRobot[this->id].pos.loc-secondPoint).length() )
            rc.fin_pos.loc = firstPoint;
        else
            rc.fin_pos.loc = secondPoint;
    }

    return rc;
}

RobotCommand TacticAttacker::goBehindBall()
{
    RobotCommand rc;
    canKick=false;

    rc.maxSpeed = 1;

    float deg=atan((0-wm->ball.pos.loc.y)/(3025-wm->ball.pos.loc.x));

    if(!wm->kn->ReachedToPos(wm->ourRobot[id].pos, rc.fin_pos, 30, 180))
    {
        rc.fin_pos.loc= {wm->ball.pos.loc.x-110*cos(deg),wm->ball.pos.loc.y-110*sin(deg)};
        rc.fin_pos.dir=atan((0-wm->ball.pos.loc.y)/(3025-wm->ball.pos.loc.x));
    }


    if(!wm->kn->ReachedToPos(wm->ourRobot[id].pos, rc.fin_pos, 20, 2))
    {
        //double test=findBestPoint();
        //rc.fin_pos.dir=test;
    }
    rc.fin_pos.loc= {wm->ball.pos.loc.x-100*cos(deg),wm->ball.pos.loc.y-100*sin(deg)};

    if(wm->kn->ReachedToPos(wm->ourRobot[id].pos, rc.fin_pos, 10, 4))
    {
        canKick=true;
    }

    return rc;
}

RobotCommand TacticAttacker::KickTheBallIndirect()
{
    RobotCommand rc;

    rc.maxSpeed = 0.5;

    int index = receiverID;

    if(index != -1)
    {
        Vector2D target(wm->ourRobot[index].pos.loc.x,wm->ourRobot[index].pos.loc.y);
        Vector2D goal(target.x,target.y);

        OperatingPosition kickPoint = wm->kn->AdjustKickPointB(wm->ball.pos.loc,goal,wm->ourRobot[this->id].pos);

//        double kickRadius = ROBOT_RADIUS *3;
//        Vector2D midle_vector=Vector2D(kickRadius*sin(abs(kickPoint.dir)),kickRadius*cos(abs(kickPoint.dir)));
//        midle_vector =  midle_vector.setDir(AngleDeg(-kickPoint.dir));

//        Position midlePoint;
//        midlePoint.loc = (wm->ball.pos.loc+midle_vector);
//        midlePoint.dir = kickPoint.dir;

//        if( (midlePoint.loc - wm->ourRobot[id].pos.loc).length() > 50  && (!pastMidPoint) )
////        if( (!wm->kn->ReachedToPos(wm->ourRobot[this->id].pos,midlePoint,90,6)) && (!pastMidPoint) )
//        {
//            rc.fin_pos = midlePoint;
//            rc.useNav = true;
//        }
//        else
//        {
//            pastMidPoint = true;
            rc.fin_pos = kickPoint.pos;
            rc.useNav = kickPoint.useNav;
//            rc.maxSpeed =
//            if( (rc.fin_pos.loc-wm->ourRobot[this->id].pos.loc).length() < 150)
//            {
//                if(!everyOneInTheirPos)
//                {
//                    rc.maxSpeed = 0;
//                }
//                else
//                {
//                    rc.useNav = false;
//                    rc.maxSpeed = 0.25;
//                }
//            }
            if(  kickPoint.readyToShoot /*&& everyOneInTheirPos*/)
            {
                rc.kickspeedx = 25;// detectKickSpeed(goal);
                qDebug()<<"Kickk...";
            }
        }
        return rc;
}

RobotCommand TacticAttacker::KickTheBallDirect()
{
    RobotCommand rc;

    rc.maxSpeed = 0.5;

    tANDp target = findTarget();
    OperatingPosition kickPoint = wm->kn->AdjustKickPointB(wm->ball.pos.loc,target.pos,wm->ourRobot[this->id].pos);

    rc.fin_pos = kickPoint.pos;

    if( kickPoint.readyToShoot )
    {
        rc.kickspeedx = detectKickSpeed(target.pos);
        qDebug()<<"Kickk...";
    }

    rc.maxSpeed = 2;
    rc.useNav = kickPoint.useNav;

    return rc;
}

RobotCommand TacticAttacker::StartTheGame()
{
    RobotCommand rc;

    rc.maxSpeed = 0.5;

    Vector2D target(Field::oppGoalCenter.x,Field::oppGoalCenter.y);
    OperatingPosition kickPoint = wm->kn->AdjustKickPointB(wm->ball.pos.loc,target,wm->ourRobot[this->id].pos);

    rc.fin_pos = kickPoint.pos;

    rc.useNav = kickPoint.useNav;

    if( kickPoint.readyToShoot )
    {
        //rc.kickspeedz = 2.5;//50;
        rc.kickspeedx = detectKickSpeed(target);
        qDebug()<<"Kickk...";
    }

    return rc;
}

int TacticAttacker::findBestPlayerForPass()
{
    int index = -1;
    double min = 10000;

    QList<int> ourAgents = wm->kn->ActiveAgents();
    QList<int> freeAgents , busyAgents;

    while( !ourAgents.isEmpty() )
    {
        int index = ourAgents.takeFirst();
        if(isFree(index))
            freeAgents.append(index);
        else
            busyAgents.append(index);
    }

    while ( !freeAgents.isEmpty() )
    {
        int i = freeAgents.takeFirst();
        if(wm->ourRobot[i].isValid && this->id != i && i != wm->ref_goalie_our)
        {
            if(wm->ball.pos.loc.dist(wm->ourRobot[i].pos.loc) < min)
            {
                min = wm->ourRobot[id].pos.loc.dist(wm->ourRobot[i].pos.loc);
                index = i;
            }
        }
    }
    if( index == -1 )
    {
        while ( !busyAgents.isEmpty() )
        {
            int i = busyAgents.takeFirst();
            if(wm->ourRobot[i].isValid && this->id != i && i != wm->ref_goalie_our)
            {
                if(wm->ball.pos.loc.dist(wm->ourRobot[i].pos.loc) < min)
                {
                    min = wm->ourRobot[id].pos.loc.dist(wm->ourRobot[i].pos.loc);
                    index = i;
                }
            }
        }

        return index;
    }
    else
        return index;
}

void TacticAttacker::isKicker()
{
    wm->ourRobot[this->id].Status = AgentStatus::Kicking;
    findReciever = true;
}

void TacticAttacker::isKicker(int recieverID)
{
    wm->ourRobot[this->id].Status = AgentStatus::Kicking;
    findReciever = false;
    this->receiverID = recieverID;
}

void TacticAttacker::waitTimerStart()
{
    everyOneInTheirPos = false;
    waitTimer->start(5000);
}

void TacticAttacker::setGameOnPositions(Position pos)
{
    setIdlePosition(pos);
}

void TacticAttacker::setGameOnPositions(Vector2D pos)
{
    Position position = wm->kn->AdjustKickPoint(pos,Field::oppGoalCenter);
    setIdlePosition(position);
}

void TacticAttacker::setIdlePosition(Position pos)
{
    this->idlePosition = pos;
}

void TacticAttacker::setIdlePosition(Vector2D pos)
{
    this->idlePosition.loc = pos;
    this->idlePosition.dir = ( wm->ball.pos.loc - pos).dir().radian();
}

int TacticAttacker::returnReceiverID()
{
    return receiverID;
}

bool TacticAttacker::isFree(int index)
{
    QList<int> oppAgents = wm->kn->ActiveOppAgents();
    bool isFree = true;

    while( !oppAgents.isEmpty() )
    {
        int indexOPP = oppAgents.takeFirst();
        if( (wm->ourRobot[index].pos.loc-wm->oppRobot[indexOPP].pos.loc).length() < DangerDist &&
                fabs((wm->ourRobot[index].vel.loc - wm->oppRobot[indexOPP].vel.loc).length())<0.3 )
        {
            isFree = false;
        }

        if(!isFree)
            break;
    }
    return isFree;
}

void TacticAttacker::dontWait()
{
    everyOneInTheirPos = true;
    if( findReciever )
        receiverID = findBestPlayerForPass();
    waitTimer->stop();
}
