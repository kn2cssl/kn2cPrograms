#include "tacticgoalie.h"

TacticGoalie::TacticGoalie(WorldModel *worldmodel, QObject *parent) :
    Tactic("TacticGoalie", worldmodel, parent)
{
    reach2Ball = false;

    sKick = new SkillKick(wm);
}

RobotCommand TacticGoalie::getCommand()
{
    RobotCommand rc;
    rc.maxSpeed = 4;

    rc.useNav=false;
    rc.isBallObs = false;
    rc.isKickObs = true;

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

        //OperatingPosition chipPoint = BallControl(target, 100, this->id,rc.maxSpeed);
        sKick->setIndex(this->id);
        sKick->setTarget(target);
        sKick->setKickType(true);
        sKick->execute(rc);
        rc.kickspeedx = 0;


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

        //        rc.fin_pos = chipPoint.pos;
        //        rc.useNav = chipPoint.useNav;

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

        rc.useNav = true;
        rc.isBallObs = true;
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
            rc.fin_pos = idlePosistion;
    }

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
    if( wm->ball.isValid )
    {
        int picOfCir = PICOFCIR - 4*ROBOT_RADIUS;
        int marginFromGoalPost = MARGINFROMGOALPOST - 4*ROBOT_RADIUS;

        double halfOfGoal = (Field::ourGoalPost_L.y-Field::ourGoalPost_R.y)/2;

        if( wm->kn->IsInsideCircle(ballPoint, Vector2D(Field::MinX-halfOfGoal-marginFromGoalPost+picOfCir, 0), halfOfGoal + marginFromGoalPost))
            return true;

        return false;
    }

    return false;
}

