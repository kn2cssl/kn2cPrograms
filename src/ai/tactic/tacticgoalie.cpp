#include "tacticgoalie.h"

TacticGoalie::TacticGoalie(WorldModel *worldmodel, QObject *parent) :
    Tactic("TacticGoalie", worldmodel, parent)
{
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


    rc.fin_pos = idlePosistion;

    //    if( !wm->kn->IsInsideGolieArea(wm->ourRobot[this->id].pos.loc) )
    //        rc.maxSpeed = 2;
    //    else
    rc.maxSpeed = 2;

    rc.useNav = false;
    rc.isBallObs = true;
    rc.isKickObs = true;

    bool chipTheBall = true;

    if( wm->kn->IsInsideGolieArea(wm->ball.pos.loc) && wm->cmgs.canKickBall() && (wm->ball.vel.loc.length() < 0.5) )
    {
        Vector2D target;

        Vector2D ballPredictedPos = wm->kn->PredictDestination(wm->ourRobot[this->id].pos.loc,
                wm->ball.pos.loc,rc.maxSpeed,wm->ball.vel.loc);
        Line2D line(ballPredictedPos, wm->ourRobot[this->id].pos.loc);
        Circle2D cir(wm->ball.pos.loc, 60);
        Vector2D first,second,chipPoint;
        cir.intersection(line,&first,&second);
        if( first.x < wm->ball.pos.loc.x)
        {
            target = second;
            chipPoint = first;
        }
        else
        {
            target = first;
            chipPoint = second;
        }

        if( wm->kn->ReachedToPos(wm->ourRobot[this->id].pos.loc,target,120) || reach2Ball )
        {
            reach2Ball = true;

            QList<int> ourPlayers = wm->kn->findNearestTo(wm->ball.pos.loc);
            ourPlayers.removeOne(this->id);

            Ray2D chipDir(wm->ourRobot[this->id].pos.loc,target);

            for(int i=0;i<ourPlayers.size();i++)
            {
                if ( chipDir.inRightDir(wm->ourRobot[ourPlayers.at(i)].pos.loc,30) )
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
                    if ( chipDir.inRightDir(wm->oppRobot[oppPlayers.at(i)].pos.loc,30) )
                    {
                        if( (wm->oppRobot[oppPlayers.at(i)].pos.loc - wm->ball.pos.loc).length() < 500 )
                        {
                            chipTheBall = false;
                            break;
                        }
                    }
                }
            }
        }
        else
            reach2Ball = false;


        OperatingPosition kickCommands = BallControl(target, 100, this->id, rc.maxSpeed);
        rc.fin_pos = kickCommands.pos;
        rc.useNav = kickCommands.useNav;

        if( kickCommands.readyToShoot && chipTheBall )
        {
            rc.kickspeedz = detectChipSpeed(kickCommands.shootSensor);
            qDebug()<<"chipp...............";
        }

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

