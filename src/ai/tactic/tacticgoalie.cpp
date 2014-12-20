#include "tacticgoalie.h"

TacticGoalie::TacticGoalie(WorldModel *worldmodel, QObject *parent) :
    Tactic("TacticGoalie", worldmodel, parent)
{
}

RobotCommand TacticGoalie::getCommand()
{
        RobotCommand rc;

        double ballDeg;
        double ballDir;
        double yInGoal;

        //Geometric calculations
        ballDeg=atan((wm->ball.pos.loc.y-0.0)/(wm->ball.pos.loc.x+(float)(FIELD_MAX_X)));
        ballDir=(float)(wm->ball.vel.loc.y)/(float)(wm->ball.vel.loc.x);
        yInGoal=wm->ball.pos.loc.y-ballDir*(float)((float)(FIELD_MAX_X)+wm->ball.pos.loc.x);

        if(((wm->ball.vel.loc.x<0 && wm->ball.vel.loc.y<0) || (wm->ball.vel.loc.x<0 && wm->ball.vel.loc.y>0)) && (abs(yInGoal)<350))
        {
         rc.fin_pos.loc={-(float)(FIELD_MAX_X)+ROBOT_RADIUS,yInGoal};
         rc.fin_pos.dir=ballDeg;
        }
        else
        {
            rc.fin_pos.loc={-(float)(FIELD_MAX_X)+ROBOT_RADIUS,0};
            rc.fin_pos.dir=ballDeg;
        }
        //qDebug()<<ballDeg*180.0/3.14<<beta<<alpha<<dtgc;

        rc.useNav = true;
        rc.isBallObs = true;
        rc.isKickObs = true;

        if( wm->kn->IsInsideGolieArea(wm->ball.pos.loc))
        {
            Vector2D target;
            if(wm->ball.pos.loc.y >= 0)
            {
                target = target.assign(wm->ball.pos.loc.x,Field::MaxY);
            }
            else
            {
                target = target.assign(wm->ball.pos.loc.x,Field::MinY);
            }
            rc.fin_pos = wm->kn->AdjustKickPoint(wm->ball.pos.loc,target);

            if(wm->kn->CanKick(wm->ourRobot[id].pos,wm->ball.pos.loc) )
            {
                //Maybe Sometimes we have chip...
                //rc.kickspeedz = 2.5;//50;
                rc.kickspeedx = 2.5;//50;
            }
            rc.useNav = false;
        }


        if( !wm->kn->IsInsideGolieArea(wm->ourRobot[this->id].pos.loc) )
            rc.maxSpeed = 2;
        else
            rc.maxSpeed = 7;

        return rc;
}

