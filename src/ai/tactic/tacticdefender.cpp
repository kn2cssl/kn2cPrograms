#include "tacticdefender.h"

TacticDefender::TacticDefender(WorldModel *worldmodel, QObject *parent) :
    Tactic("TacticDefender", worldmodel, parent)
{
    reach2Ball = false;
    this->useNav = false;
    oppPassReciever = -1;

    sKick = new SkillKick(wm);
}

RobotCommand TacticDefender::getCommand()
{
    RobotCommand rc;
    if(!wm->ourRobot[id].isValid) return rc;

    rc.maxSpeed = 4;
    if( wm->cmgs.canKickBall() )
    {
        if( wm->isSim )
            rc.kickspeedx = 8;
        else if( wm->useShootSensor )
            rc.kickspeedx = 200;
    }

    if(wm->ourRobot[this->id].Status == AgentStatus::FollowingBall)
    {
        Vector2D v;
        v = wm->kn->PredictDestination(wm->ourRobot[this->id].pos.loc,
                wm->ball.pos.loc,rc.maxSpeed,wm->ball.vel.loc);

        int opposite = wm->kn->findOppReciever();

        if( oppPassReciever != opposite )
        {
            oppPassReciever = opposite;
            this->resetBooleans();
        }

        Vector2D opp_v;
        double oppDistance;
        if( opposite != -1)
        {
            opp_v = wm->kn->PredictDestination(wm->oppRobot[opposite].pos.loc,
                                               wm->ball.pos.loc,wm->opp_vel,wm->ball.vel.loc);
            oppDistance = (opp_v - wm->oppRobot[opposite].pos.loc).length();
        }
        else
            oppDistance = 3500000;

        double ourDistance = (v - wm->ourRobot[this->id].pos.loc).length();

        Ray2D ballRay(wm->ball.pos.loc, wm->ball.vel.loc.dir());
        Line2D goalLine(Field::ourGoalPost_L, Field::ourGoalPost_R);
        Segment2D exactGoal(Vector2D(Field::ourGoalPost_L.x,Field::ourGoalPost_L.y+500), Vector2D(Field::ourGoalPost_R.x,Field::ourGoalPost_R.y-500));
        Vector2D intersect = ballRay.intersection(goalLine);
        bool ballTowardUsDangerously = false;
        if( exactGoal.contains(intersect) && wm->ball.vel.loc.length() > 0.5 )
            ballTowardUsDangerously = true;

        if( (oppDistance - ourDistance > 1000) && !ballTowardUsDangerously )
        {
            Vector2D ballPredictedPos = wm->kn->PredictDestination(wm->ourRobot[this->id].pos.loc,
                    wm->ball.pos.loc,rc.maxSpeed,wm->ball.vel.loc);
            //            Line2D line(ballPredictedPos, wm->ourRobot[this->id].pos.loc);
            //            Circle2D cir(wm->ball.pos.loc, 60);
            Vector2D first,second,main,chipPoint;
            //            cir.intersection(line,&first,&second);
            //            double firstDist , secondDist;
            //            firstDist = (wm->ourRobot[this->id].pos.loc - first).length();
            //            secondDist = (wm->ourRobot[this->id].pos.loc - second).length();
            //            if( firstDist < secondDist)
            //            {
            //                main = first;
            //                chipPoint = second;
            //            }
            //            else
            //            {
            //                main = second;
            //                chipPoint = first;
            //            }

            main = ballPredictedPos;
            main.x = main.x - 200;

            chipPoint = ballPredictedPos;
            chipPoint.x = chipPoint.x + 200;

            rc.fin_pos.loc = main;

            if( wm->kn->ReachedToPos(wm->ourRobot[this->id].pos.loc,main,150) || reach2Ball )
            {
                reach2Ball = true;
                tANDp target = findTarget();
                Circle2D dangerCir(wm->ourRobot[this->id].pos.loc,1000);
                QList<int> opps = wm->kn->findNearestOppositeTo(wm->ourRobot[this->id].pos.loc);
                bool inDangerousPosition = false;
                for(int i=0;i<opps.size();i++)
                {
                    if ( dangerCir.contains(wm->oppRobot[opps.at(i)].pos.loc) )
                    {
                        inDangerousPosition = true;
                        break;
                    }
                }

                if( inDangerousPosition )
                {
                    //                        qDebug()<<"in a dangerous position , chip the ball";
                    //OperatingPosition p = BallControl(chipPoint, 100, this->id, rc.maxSpeed);

                    sKick->setIndex(this->id);
                    sKick->setTarget(chipPoint);
                    sKick->setKickType(true);
                    sKick->execute(rc);

                    Ray2D chipDir(wm->ourRobot[this->id].pos.loc,chipPoint);
                    bool chipIsSuitable = true;
                    for(int i=0;i<opps.size();i++)
                    {
                        if ( chipDir.inRightDir(wm->oppRobot[opps.at(i)].pos.loc,30) )
                        {
                            chipIsSuitable = false;
                            break;
                        }
                    }

                    //                    if( p.readyToShoot && chipIsSuitable )
                    //                    {
                    //                        rc.kickspeedz = detectChipSpeed(p.shootSensor);
                    //                        qDebug()<<"Chippppppppppp";
                    //                    }

                    //                    rc.fin_pos = p.pos;
                    //                    rc.useNav = p.useNav;
                    rc.isBallObs = true;
                    rc.isKickObs = true;
                }
                else
                {
                    sKick->setIndex(this->id);
                    sKick->setTarget(target.pos);
                    sKick->setKickType(true);
                    sKick->execute(rc);

                    rc.isBallObs = true;
                    rc.isKickObs = true;
                }
            }
            else
            {
                //qDebug()<<"else";
                rc.fin_pos.loc = main;
                rc.fin_pos.dir = (main - wm->ourRobot[this->id].pos.loc).dir().radian();
                rc.useNav = true;
                rc.isBallObs = true;
                rc.isKickObs = true;
            }
        }
        else
        {
            //            qDebug()<<"dangerous distance from opp , don't go";
            rc.fin_pos = idlePosition;
            rc.useNav = false;
            rc.isBallObs = true;
            rc.isKickObs = true;
        }
    }
    else if(wm->ourRobot[this->id].Status == AgentStatus::RecievingPass)
    {
        rc.fin_pos = idlePosition;
        rc.useNav = true;
        rc.isBallObs = true;
        rc.isKickObs = true;
    }
    else if(wm->ourRobot[this->id].Status == AgentStatus::BlockingBall)
    {
        double ballDeg,beta,teta,alpha=356,gama;
        double dtgc;//distanceToGoldanCenter
        double dtgc2;
        double ballDistance;//ballDistanceToGoalCenter

        //Geometric calculations
        ballDeg = (wm->ball.pos.loc - Field::ourGoalCenter).dir().radian();

        if(ballDeg>75.0*3.14/180)
        {
            ballDeg=75.0*3.14/180;
        }

        if(ballDeg<-75.0*3.14/180)
        {
            ballDeg=-75.0*3.14/180;
        }

        gama=AngleDeg::PI/2.0-abs(ballDeg);
        beta=asin((float)(Field::defenceLineLinear)*sin(gama)/(2.0*(Field::goalCircle_R+ROBOT_RADIUS)));
        alpha=atan((float)(Field::defenceLineLinear/2)/(Field::goalCircle_R+ROBOT_RADIUS));
        dtgc=(float)(Field::goalCircleEX_R)*sin(AngleDeg::PI-gama-beta)/sin(gama);
        dtgc2 = sqrt(dtgc*dtgc+(float)(ROBOT_RADIUS+10)*(float)(ROBOT_RADIUS+10));
        teta=atan((float)(ROBOT_RADIUS+10)/dtgc);
        ballDistance=pow((pow(wm->ball.pos.loc.x+(float)(Field::MaxX),2)+pow(wm->ball.pos.loc.y,2)),0.5);

        switch(wm->ourRobot[this->id].Role)
        {
        case AgentRole::DefenderMid:
            if(abs(ballDeg)<alpha)
            {
                rc.fin_pos.dir=ballDeg;
                rc.fin_pos.loc=Vector2D(-(float)(Field::MaxX)+Field::goalCircle_R+ROBOT_RADIUS,0.0+tan(ballDeg)*(Field::goalCircle_R+ROBOT_RADIUS));
            }

            else
            {
                rc.fin_pos.dir=ballDeg;
                rc.fin_pos.loc={-(float)(Field::MaxX)+cos(ballDeg)*dtgc,0.0+sin(ballDeg)*dtgc};
            }
            break;

        case AgentRole::DefenderLeft:
            rc.fin_pos.dir=ballDeg;
            rc.fin_pos.loc={-(float)(Field::MaxX)+cos(ballDeg+teta)*dtgc2,0.0+sin(ballDeg+teta)*dtgc2};
            if(dtgc+2*ROBOT_RADIUS<ballDistance && ballDistance<dtgc+4*ROBOT_RADIUS && wm->ball.pos.loc.y>0)
            {
                if(!wm->kn->ReachedToPos(wm->ourRobot[id].pos, rc.fin_pos, 30, 180))
                {
                    rc.fin_pos.loc= {wm->ball.pos.loc.x-110*cos(ballDeg),wm->ball.pos.loc.y-110*sin(ballDeg)};
                    rc.fin_pos.dir=ballDeg;
                }

                if(wm->kn->ReachedToPos(wm->ourRobot[id].pos, rc.fin_pos, 20, 4))
                {

                    if(!wm->kn->ReachedToPos(wm->ourRobot[id].pos, rc.fin_pos, 20, 2))
                    {
                        rc.fin_pos.dir=ballDeg;
                    }
                    rc.fin_pos.loc= {wm->ball.pos.loc.x-100*cos(ballDeg),wm->ball.pos.loc.y-100*sin(ballDeg)};
                }

            }
            break;

        case AgentRole::DefenderRight:
            rc.fin_pos.dir=ballDeg;
            rc.fin_pos.loc={-(float)(Field::MaxX)+cos(ballDeg-teta)*dtgc2,0.0+sin(ballDeg-teta)*dtgc2};
            if(dtgc+2*ROBOT_RADIUS<ballDistance && ballDistance<dtgc+4*ROBOT_RADIUS && wm->ball.pos.loc.y<0)
            {
                if(!wm->kn->ReachedToPos(wm->ourRobot[id].pos, rc.fin_pos, 30, 180))
                {
                    rc.fin_pos.loc= {wm->ball.pos.loc.x-110*cos(ballDeg),wm->ball.pos.loc.y-110*sin(ballDeg)};
                    rc.fin_pos.dir=ballDeg;
                }

                if(wm->kn->ReachedToPos(wm->ourRobot[id].pos, rc.fin_pos, 20, 4))
                {

                    if(!wm->kn->ReachedToPos(wm->ourRobot[id].pos, rc.fin_pos, 20, 2))
                    {
                        rc.fin_pos.dir=ballDeg;
                    }
                    rc.fin_pos.loc= {wm->ball.pos.loc.x-100*cos(ballDeg),wm->ball.pos.loc.y-100*sin(ballDeg)};
                }
            }
            break;
        default:
            break;
        }

        rc.useNav = true;
        rc.isBallObs = true;
        rc.isKickObs = true;
    }
    else if(wm->ourRobot[this->id].Status == AgentStatus::BlockingRobot)
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
    else if(wm->ourRobot[this->id].Status == AgentStatus::Idle)
    {
        rc.fin_pos = idlePosition;
        rc.useNav = this->useNav;
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

    return rc;
}

void TacticDefender::setIdlePosition(Position pos)
{
    this->idlePosition = pos;
}

void TacticDefender::setIdlePosition(Vector2D pos)
{
    this->idlePosition.loc = pos;
}

void TacticDefender::resetBooleans()
{
    this->reach2Ball = false;
}

void TacticDefender::setUseNav(bool input)
{
    this->useNav = input;
}
