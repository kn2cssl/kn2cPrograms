#include "tactictestfriction.h"

TacticTestFriction::TacticTestFriction(WorldModel *worldmodel, QObject *parent) :
    Tactic("TacticTestFriction", worldmodel, parent)
{
}

RobotCommand TacticTestFriction::getCommand()
{
    RobotCommand rc;
    if(!wm->ourRobot[id].isValid) return rc;

//    qDebug() << " This Is The Friction Test Tactic !" ;
    double speed = 1.2;

    if(wm->ball.isValid && wm->ball.pos.loc.x <-100 && wm->ball.pos.loc.x > -2000)
    {
        Vector2D v;
        if(wm->ball.vel.loc.length() > 0.06)
        {
            v = wm->kn->PredictDestination(wm->ourRobot[id].pos.loc, wm->ball.pos.loc, speed , wm->ball.vel.loc);
        }
        else
        {
            v = wm->ball.pos.loc;
        }

        Position p = wm->kn->AdjustKickPoint(v, Field::ourGoalCenter);

        rc.fin_pos = p;

        Vector2D R2B=wm->ball.pos.loc-wm->ourRobot[id].pos.loc;
        double delta_ang=wm->ourRobot[id].pos.dir-R2B.dir().radian();
        if (delta_ang > M_PI) delta_ang -= (M_PI * 2);
        if (delta_ang < -M_PI) delta_ang += (M_PI * 2);

        qDebug() << "Lenght To Ball : " << R2B.length();
        qDebug() << "Delta Angle : " << AngleDeg::rad2deg(delta_ang);
        if(wm->kn->IsReadyForKick(wm->ourRobot[id].pos,p,wm->ball.pos.loc))
//        if(fabs(delta_ang) < AngleDeg::deg2rad(20) && R2B.length() < 500)
        {
            qDebug() << "KIKKKIKIKIKIKIK " << wm->ball.pos.loc.x;
            rc.kickspeedx = 2.55;
        }
    }
    else
    {
        rc.fin_pos.loc = Vector2D(-200,900);
        rc.fin_pos.dir = AngleDeg::PI;
    }

    rc.fin_pos.dir = (Vector2D(-2500,0) - wm->ourRobot[id].pos.loc).dir().radian();

    rc.maxSpeed = speed;

    rc.useNav = false;

    return rc;
}


