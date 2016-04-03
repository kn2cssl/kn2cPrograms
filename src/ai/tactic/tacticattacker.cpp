#include "tacticattacker.h"


TacticAttacker::TacticAttacker(WorldModel *worldmodel, QObject *parent) :
    Tactic("TacticAttacker", worldmodel, parent)
{
    everyOneInTheirPos = false;
    maxDistance = sqrt(pow(Field::MaxX*2,2)+pow(Field::MaxY*2,2));

    sKick = new SkillKick(wm);
    sOneTouch = new SkillOneTouch(wm);

    this->holdKickPos = false;
}

RobotCommand TacticAttacker::getCommand()
{
    RobotCommand rc;
    if(!wm->ourRobot[id].isValid) return rc;

    rc.maxSpeed = 4;
    if(wm->ourRobot[id].Status == AgentStatus::FollowingBall)
    {
        tANDp target = findTarget();

        Vector2D passSenderPos = wm->ourRobot[kickerID].pos.loc;
        Vector2D OneTouchKickerPos = wm->ourRobot[this->id].pos.loc;
        Vector2D passSender2OneTouchKicker = OneTouchKickerPos-passSenderPos;
        Vector2D passSender2Ball = wm->ball.pos.loc-passSenderPos;
        Line2D *ballVel= new Line2D(wm->ball.pos.loc,passSender2Ball.dir().degree());
        Circle2D checkingCircle(OneTouchKickerPos,ROBOT_RADIUS+750);

        qDebug()<<":this id: "<<this->id;
        qDebug()<<((passSenderPos-OneTouchKickerPos).length2()>(passSenderPos-wm->ball.pos.loc).length2() ) <<" , "<<(fabs(passSender2OneTouchKicker.dir().degree()-passSender2Ball.dir().degree())<30)<<" , "<<(wm->ball.vel.loc.length()>0.2)<<" , "<<(checkingCircle.HasIntersection(*ballVel));
        if( ( (kickerID!=-1) && (passSenderPos-OneTouchKickerPos).length2()>(passSenderPos-wm->ball.pos.loc).length2() )  &&  (fabs(passSender2OneTouchKicker.dir().degree()-passSender2Ball.dir().degree())<30)  &&  (wm->ball.vel.loc.length()>0.2) && (checkingCircle.HasIntersection(*ballVel)))
        {
            qDebug()<<"11111111111111111111111111111111111111111111111111111111111111111touch";
            sOneTouch->setIndex(this->id);
            sOneTouch->setTarget(Field::oppGoalCenter);
            sOneTouch->execute(rc);
        }
        else
        {
            qDebug()<<"followingballllllllllllllllllllllllllllllllllllllllllllllllllllllllll";
            if( kickerID != -1 && ( kickerID != this->id) )
                wm->ourRobot[kickerID].Status = AgentStatus::Idle;

            sOneTouch->resetAllFlags();

            sKick->setTarget(target.pos);
            sKick->setIndex(this->id);
            sKick->setKickType(true);
            sKick->execute(rc);
        }
    }
    else if(wm->ourRobot[id].Status == AgentStatus::Kicking)
    {
        if(wm->gs == STATE_Start)
        {
            rc = StartTheGame();
        }
        else if(wm->cmgs.gameOn())
        {
            if( !holdKickPos )
            {
                holdKickPos = true;
                kickPos = wm->ourRobot[this->id].pos;
            }

            rc.fin_pos = kickPos;
            rc.useNav = true;
        }
        else
        {
            rc = KickTheBallIndirect();
        }

        rc.isBallObs = false;
        rc.isKickObs = true;
    }
    else if(wm->ourRobot[id].Status == AgentStatus::Chiping)
    {
        rc = ChipTheBallIndirect();

        rc.isBallObs = true;
        rc.isKickObs = true;
    }
    else if(wm->ourRobot[id].Status == AgentStatus::RecievingPass)
    {
        rc.fin_pos = idlePosition;
        rc.useNav = true;
        rc.isBallObs = true;
        rc.isKickObs = true;
    }
    else if(wm->ourRobot[id].Status == AgentStatus::BlockingRobot)
    {
        AngleDeg desiredDeg =  (wm->oppRobot[playerToKeep].pos.loc-Field::ourGoalCenter).dir();
        //        AngleDeg desiredDeg ;//=  (wm->oppRobot[playerToKeep].pos.loc-wm->ball.pos.loc).dir();
        //        if( wm->ball.isValid )
        //            desiredDeg =  (wm->oppRobot[playerToKeep].pos.loc-wm->ball.pos.loc).dir();
        //        else
        //            desiredDeg =  (wm->oppRobot[playerToKeep].pos.loc-Field::ourGoalCenter).dir();

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

                Line2D connectedLine(wm->ball.pos.loc,Field::ourGoalCenter);
                int numberOfIntersections = secArea.intersection(connectedLine,&fstInt,&secInt);

                rc.fin_pos.dir = (wm->oppRobot[playerToKeep].pos.loc - Field::ourGoalCenter).dir().radian();
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

        rc.useNav = true;
        rc.isBallObs = true;
        rc.isKickObs = true;
    }
    else if(wm->ourRobot[id].Status == AgentStatus::Idle)
    {
        this->holdKickPos = false;

        rc.fin_pos = idlePosition;
        rc.useNav = true;
        rc.isBallObs = true;
        rc.isKickObs = true;

        if( wm->gs == STATE_Stop )
        {
            rc.maxSpeed = 1;
            return rc;
        }
    }

    if( wm->kn->IsInsideGolieArea(rc.fin_pos.loc) )
    {
        Vector2D gc2fp = ( rc.fin_pos.loc - Field::ourGoalCenter);
        gc2fp.setLength(Field::goalCircleDEF_R);
        rc.fin_pos.loc = gc2fp + Field::ourGoalCenter;
        rc.fin_pos.dir = gc2fp.dir().radian();
    }

    if( wm->kn->IsInsideOppGolieArea(rc.fin_pos.loc) && !wm->cmgs.ourPenaltyKick())
    {
        Vector2D gc2fp = ( rc.fin_pos.loc - Field::oppGoalCenter);
        gc2fp.setLength(Field::goalCircleDEF_R + ROBOT_RADIUS);
        rc.fin_pos.loc = gc2fp + Field::oppGoalCenter;
        rc.fin_pos.dir = (Field::oppGoalCenter - wm->ourRobot[this->id].pos.loc).dir().radian();//gc2fp.dir().radian();
    }

    return rc;
}

RobotCommand TacticAttacker::goBehindBall()
{
    RobotCommand rc;
    canKick=false;

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

    if( wm->kn->ReachedToPos(wm->ourRobot[this->id].pos.loc, wm->ball.pos.loc, SECURE_DIST) )
        rc.maxSpeed = 0.5;

    Vector2D target = receiverPos;

    Line2D b2g(target,Field::oppGoalCenter);
    Circle2D cir(target,300);
    Vector2D goal,first,second;
    int numOfPoints = cir.intersection(b2g,&first,&second);
    //    if( numOfPoints == 2)
    //    {
    //        if( first.x > target.x )
    //            goal = first;
    //        else if( second.x > target.x )
    //            goal = second;
    //        else
    //            goal = target;
    //    }
    //    else if( numOfPoints == 1)
    //        goal = first;
    //    else
    goal = target;

    wm->passPoints.clear();
    wm->passPoints.push_back(goal);

    //    OperatingPosition kickPoint = BallControl(goal,100,this->id,rc.maxSpeed);

    sKick->setIndex(this->id);
    sKick->setTarget(goal);
    sKick->setKickType(false);
    sKick->execute(rc);


    if(  /*kickPoint.readyToShoot &&*/ !everyOneInTheirPos)
    {
        rc.kickspeedx = 0;//detectKickSpeed(freeKickType, kickPoint.shootSensor);
        //        Line2D ball2Target(wm->ball.pos.loc,goal);

        //        QList<int> activeOpp = wm->kn->ActiveOppAgents();
        //        bool wayIsClear = true;

        //        for(int i=0;i<activeOpp.size();i++)
        //        {
        //            double distance = ball2Target.dist(wm->oppRobot[activeOpp.at(i)].pos.loc);
        //            if( distance < ROBOT_RADIUS+BALL_RADIUS )
        //            {
        //                wayIsClear = false;
        //                break;
        //            }
        //        }

        //        if( wayIsClear )
        //        {
        //            rc.kickspeedx = 255;// detectKickSpeed(goal);
        //            qDebug()<<"Kickk...";
        //        }
        //        else
        //        {
        //            rc.kickspeedx = 3;//255;// detectKickSpeed(goal);
        //            rc.kickspeedz = 3;
        //            qDebug()<<"CHIP...";
        //        }

    }

    return rc;
}

RobotCommand TacticAttacker::KickTheBallDirect()
{
    RobotCommand rc;

    if( wm->kn->ReachedToPos(wm->ourRobot[this->id].pos.loc, wm->ball.pos.loc, SECURE_DIST))
        rc.maxSpeed = 0.5;

    tANDp target = findTarget();
    //    OperatingPosition kickPoint = BallControl(target.pos, target.prob, this->id, rc.maxSpeed);

    sKick->setIndex(this->id);
    sKick->setTarget(target.pos);
    sKick->setKickType(true);
    sKick->execute(rc);

    //rc.fin_pos = kickPoint.pos;

    //    if( kickPoint.readyToShoot )
    //    {
    //        rc.kickspeedx = detectKickSpeed(kickType::Shoot, kickPoint.shootSensor);
    //        qDebug()<<"Kickk...";
    //    }
    //    rc.useNav = kickPoint.useNav;

    return rc;
}

RobotCommand TacticAttacker::StartTheGame()
{
    RobotCommand rc;

    if( wm->kn->ReachedToPos(wm->ourRobot[this->id].pos.loc, wm->ball.pos.loc, 200))
        rc.maxSpeed = 0.5;

    Vector2D target(Field::oppGoalCenter.x,Field::oppGoalCenter.y);
    //    OperatingPosition kickPoint = BallControl(target, 100, this->id, rc.maxSpeed);

    sKick->setIndex(this->id);
    sKick->setTarget(target);
    sKick->setKickType(true);
    sKick->execute(rc);

    //    rc.fin_pos = kickPoint.pos;
    //    rc.useNav = kickPoint.useNav;

    //    if( kickPoint.readyToShoot )
    //    {
    //        //rc.kickspeedz = 2.5;//50;
    //        rc.kickspeedx = detectKickSpeed(kickType::Shoot, kickPoint.shootSensor);
    //        qDebug()<<"Kickk...";
    //    }

    return rc;
}

RobotCommand TacticAttacker::ChipTheBallIndirect()
{
    RobotCommand rc;

    if(  (wm->ourRobot[this->id].pos.loc - wm->ball.pos.loc).length() < SECURE_DIST)
        rc.maxSpeed = 0.5;

    Vector2D target = receiverPos;
    Vector2D goal(target.x,target.y);

    //OperatingPosition kickPoint = BallControl(goal, 100, this->id, rc.maxSpeed,3);

    sKick->setIndex(this->id);
    sKick->setTarget(goal);
    sKick->setKickType(true);
    sKick->execute(rc);

    //    rc.fin_pos = kickPoint.pos;
    //    rc.useNav = kickPoint.useNav;

    if(  /*kickPoint.readyToShoot &&*/ !everyOneInTheirPos)
    {
        rc.kickspeedz = 0;//detectChipSpeed(kickPoint.shootSensor);
        qDebug()<<"Chip...";
    }

    return rc;
}

int TacticAttacker::findBestPlayerForPass()
{
    QList<int> ourAgents = wm->kn->findAttackers();
    ourAgents.removeOne(this->id);

    QList<int> freeAgents, busyAgents;

    while( !ourAgents.isEmpty() )
    {
        int index = ourAgents.takeFirst();
//        if(isFree(index))
            freeAgents.append(index);
//        else
//            busyAgents.append(index);
    }

    //    QList<double> weights;
    //    for(int i=0;i<freeAgents.size();i++)
    //    {
    //        double weight = -1000000;
    //        if( wm->ourRobot[freeAgents.at(i)].isValid )
    //        {
    //            double dist = 1 - ((wm->ball.pos.loc - wm->ourRobot[freeAgents.at(i)].pos.loc).length()/maxDistance);
    //            double prob = wm->kn->scoringChance(wm->ourRobot[freeAgents.at(i)].pos.loc) / 100;
    //            weight = /*(20 * prob) +*/ (10*dist);
    //        }
    //        weights.append(weight);
    //    }

    //    int index = -1;
    //    double max = -10000;
    //    for(int i=0;i<weights.size();i++)
    //    {
    //        if( max < weights.at(i) )
    //        {
    //            max = weights.at(i);
    //            index = freeAgents.at(i);
    //        }
    //    }

    int index = -1;
    double min = 1000000;
    for(int i=0;i<freeAgents.size();i++)
    {
        double dist = 1000000;
        if( wm->ourRobot[freeAgents.at(i)].isValid )
        {
            dist = (wm->ball.pos.loc - wm->ourRobot[freeAgents.at(i)].pos.loc).length();
            if( min > dist)
            {
                min = dist;
                index = freeAgents.at(i);
            }
        }
    }

//    if( index == -1 )
//    {
//        double min_dist = 3000000;
//        int bestBusyID = -1;
//        for(int i = 0; i < busyAgents.size(); i++)
//        {
//            if( min_dist > (wm->ourRobot[busyAgents.at(i)].pos.loc-wm->ourRobot[this->id].pos.loc).length() )
//            {
//                min_dist = (wm->ourRobot[busyAgents.at(i)].pos.loc-wm->ourRobot[this->id].pos.loc).length();
//                bestBusyID = busyAgents.at(i);
//            }
//        }
//        index = bestBusyID;
//    }

    return index;
}

void TacticAttacker::isKicker()
{
    wm->ourRobot[this->id].Status = AgentStatus::Kicking;
    findReciever = true;
}

void TacticAttacker::isChiper()
{
    wm->ourRobot[this->id].Status = AgentStatus::Chiping;
    findReciever = true;
}

void TacticAttacker::isKicker(int recieverID)
{
    wm->ourRobot[this->id].Status = AgentStatus::Kicking;
    findReciever = false;
    this->receiverPos = wm->ourRobot[recieverID].pos.loc;
}

void TacticAttacker::isKicker(Vector2D pos)
{
    wm->ourRobot[this->id].Status = AgentStatus::Kicking;
    findReciever = false;
    this->receiverPos = pos;
}

void TacticAttacker::isChiper(Vector2D pos)
{
    wm->ourRobot[this->id].Status = AgentStatus::Chiping;
    findReciever = false;
    this->receiverPos = pos;
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

void TacticAttacker::youHavePermissionForKick(int index)
{
    everyOneInTheirPos = true;
    if( findReciever )
    {
        int indexOfReciever;
        if( index > -1 && index < 12)
            indexOfReciever = index;
        else
            indexOfReciever = findBestPlayerForPass();

        if( indexOfReciever != -1 )
            receiverPos = wm->ourRobot[indexOfReciever].pos.loc;
    }
}

void TacticAttacker::youDontHavePermissionForKick()
{
    everyOneInTheirPos = false;
}

void TacticAttacker::setFreeKickType(kickType type)
{
    this->freeKickType = type;
}

void TacticAttacker::setKickerID(int id)
{
    this->kickerID = id;
}

bool TacticAttacker::isFree(int index)
{
    QList<int> oppAgents = wm->kn->ActiveOppAgents();

    while( !oppAgents.isEmpty() )
    {
        int indexOPP = oppAgents.takeFirst();
        if( (wm->ourRobot[index].pos.loc-wm->oppRobot[indexOPP].pos.loc).length() < DangerDist &&
                fabs((wm->ourRobot[index].vel.loc - wm->oppRobot[indexOPP].vel.loc).length())<0.3 )
        {
            return false;
        }
    }
    return true;
}
