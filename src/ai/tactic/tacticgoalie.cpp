#include "tacticgoalie.h"

TacticGoalie::TacticGoalie(WorldModel *worldmodel, QObject *parent) :
    Tactic("TacticGoalie", worldmodel, parent)
{
    reach2Ball = false;
}

RobotCommand TacticGoalie::getCommand()
{
    RobotCommand rc;

    //        double ballDeg;
    //        double ballDir;
    //        double yInGoal;

    //        //Geometric calculations
    //        ballDeg=atan((wm->ball.pos.loc.y-0.0)/(wm->ball.pos.loc.x+(float)(Field::MaxX)));
    //        ballDir=(float)(wm->ball.vel.loc.y)/(float)(wm->ball.vel.loc.x);
    //        yInGoal=wm->ball.pos.loc.y-ballDir*(float)((float)(Field::MaxX)+wm->ball.pos.loc.x);

    //        if(((wm->ball.vel.loc.x<0 && wm->ball.vel.loc.y<0) || (wm->ball.vel.loc.x<0 && wm->ball.vel.loc.y>0)) && (abs(yInGoal)<400))
    //        {
    //         rc.fin_pos.loc={-(float)(Field::MaxX)+ROBOT_RADIUS,yInGoal};
    //         rc.fin_pos.dir=ballDeg;
    //        }
    //        else
    //        {
    //            rc.fin_pos.loc={-(float)(Field::MaxX)+ROBOT_RADIUS,0};
    //            rc.fin_pos.dir=ballDeg;
    //        }
    //        //qDebug()<<ballDeg*180.0/3.14<<beta<<alpha<<dtgc;

    if( wm->kn->IsInsideGolieArea(wm->ball.pos.loc) && wm->cmgs.canKickBall() && (wm->ball.vel.loc.length() < 0.5)
            && !isVeryCloseToGoal(wm->ball.pos.loc) )
    {
        Vector2D target;

        rc.maxSpeed = 0.5;

//        Vector2D ballPredictedPos = wm->kn->PredictDestination(wm->ourRobot[this->id].pos.loc,
//                wm->ball.pos.loc,rc.maxSpeed,wm->ball.vel.loc);

//        Vector2D first,second,chipPoint;
//        chipPoint = ballPredictedPos;
//        chipPoint.x = chipPoint.x - 2*ROBOT_RADIUS;

        target = wm->ball.pos.loc;
        target.x = target.x + 2*ROBOT_RADIUS;

        OperatingPosition chipPoint = BallControl(target, 100, this->id,rc.maxSpeed);


//        double firstDist , secondDist;
//        firstDist = (wm->ourRobot[this->id].pos.loc - first).length();
//        secondDist = (wm->ourRobot[this->id].pos.loc - second).length();
//        if( firstDist < secondDist)
//        {
//            target = second;
//            chipPoint = first;
//        }
//        else
//        {
//            target = first;
//            chipPoint = second;
//        }

        bool chipTheBall = true;

        rc.fin_pos = chipPoint.pos;
        rc.useNav = chipPoint.useNav;

        if( wm->kn->ReachedToPos(wm->ourRobot[this->id].pos.loc,wm->ball.pos.loc,ROBOT_RADIUS) || reach2Ball )
        {
            reach2Ball = true;

            QList<int> ourPlayers = wm->kn->findNearestTo(wm->ball.pos.loc);
            ourPlayers.removeOne(this->id);

            Ray2D chipDir(wm->ourRobot[this->id].pos.loc,target);

            for(int i=0;i<ourPlayers.size();i++)
            {
                if ( chipDir.inRightDir(wm->ourRobot[ourPlayers.at(i)].pos.loc,15) )
                {
                    if( (wm->ourRobot[ourPlayers.at(i)].pos.loc - wm->ball.pos.loc).length() < 500 )
                    {
                        chipTheBall = false;
                        break;
                    }
                }
            }

            if( chipTheBall )
            {
                QList<int> oppPlayers = wm->kn->findNearestOppositeTo(wm->ball.pos.loc);

                for(int i=0;i<oppPlayers.size();i++)
                {
                    if ( chipDir.inRightDir(wm->oppRobot[oppPlayers.at(i)].pos.loc,15) )
                    {
                        if( (wm->oppRobot[oppPlayers.at(i)].pos.loc - wm->ball.pos.loc).length() < 500 )
                        {
                            chipTheBall = false;
                            break;
                        }
                    }
                }
            }

//            if( chipPoint.readyToShoot && chipTheBall )
//            {
//                rc.kickspeedx = detectChipSpeed(chipPoint.shootSensor);
//                qDebug()<<"chipp...............";
//            }
        }
//        else
//            reach2Ball = false;
    }
    else
    {
        if( isVeryCloseToGoal(wm->ball.pos.loc) )
        {
            qDebug()<<"is very close";
            rc.fin_pos = wm->ourRobot[this->id].pos;
            rc.maxSpeed = 0;
        }
        else
        {
            rc.fin_pos = idlePosistion;
            rc.maxSpeed = 2;

            rc.useNav = false;
            rc.isBallObs = true;
            rc.isKickObs = true;
        }
    }

    rc.useNav=true;////////////////////////////////////////////////////////////badan pak shavad...
    rc.isBallObs = true;
    rc.isKickObs = true;

    return rc;
}

void TacticGoalie::setIdlePosition(Position pos)
{
    this->idlePosistion = pos;
}

void TacticGoalie::setIdlePosition(Vector2D pos)
{
    this->idlePosistion.loc = pos;
}

bool TacticGoalie::isVeryCloseToGoal(Vector2D ballPoint)
{
    int picOfCir = PICOFCIR - 4*ROBOT_RADIUS;
    int marginFromGoalPost = MARGINFROMGOALPOST - 4*ROBOT_RADIUS;

    double halfOfGoal = (Field::ourGoalPost_L.y-Field::ourGoalPost_R.y)/2;

    if( wm->kn->IsInsideCircle(ballPoint, Vector2D(Field::MinX-halfOfGoal-marginFromGoalPost+picOfCir, 0), halfOfGoal + marginFromGoalPost))
        return true;

    return false;
}

