#include "tacticdefender.h"

TacticDefender::TacticDefender(WorldModel *worldmodel, QObject *parent) :
    Tactic("TacticDefender", worldmodel, parent)
{
}

RobotCommand TacticDefender::getCommand()
{
    RobotCommand rc;
    if(!wm->ourRobot[id].isValid) return rc;

    if(wm->ourRobot[this->id].Status == AgentStatus::FollowingBall)
    {
        rc.maxSpeed = 1;

        Vector2D v;
        v = wm->kn->PredictDestination(wm->ourRobot[this->id].pos.loc,
                wm->ball.pos.loc,rc.maxSpeed,wm->ball.vel.loc);
        tANDp target = findTarget();

        OperatingPosition p = wm->kn->AdjustKickPointB(v, target.pos,wm->ourRobot[this->id].pos);

        if( p.readyToShoot )
        {
            rc.kickspeedx = detectKickSpeed(target.pos);
        }

        rc.maxSpeed = 1.5;
        rc.fin_pos = p.pos;
        rc.useNav = p.useNav;
        rc.isBallObs = true;
        rc.isKickObs = true;

    }
    else if(wm->ourRobot[this->id].Status == AgentStatus::RecievingPass)
    {
        rc.fin_pos = idlePosition;

        rc.maxSpeed = 2.5;

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

        rc.maxSpeed=1.5;

        rc.useNav = true;
        rc.isBallObs = true;
        rc.isKickObs = true;
    }
    else if(wm->ourRobot[this->id].Status == AgentStatus::Idle)
    {
        rc.fin_pos = idlePosition;

        rc.maxSpeed = 2;

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

void TacticDefender::setIdlePosition(Position pos)
{
    this->idlePosition = pos;
}

void TacticDefender::setIdlePosition(Vector2D pos)
{
    this->idlePosition.loc = pos;
}
