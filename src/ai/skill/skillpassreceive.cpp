#include "skillpassreceive.h"

SkillPassReceive::SkillPassReceive(WorldModel* wm, QObject *parent) :
    Skill(wm, parent)
{
    this->firstTime = true;
}

bool SkillPassReceive::execute(RobotCommand &rc)
{
    if( firstTime )
    {
        currentposition=wm->ourRobot[index].pos.loc;
        firstTime = false;
    }

    Vector2D robot2ball=wm->ball.pos.loc-wm->ourRobot[index].pos.loc;
    rc.fin_pos.dir=robot2ball.dir().radian();
    rc.fin_pos.loc=currentposition;

    if (wm->ball.vel.loc.length()>0.1)
    {
        Vector2D goal;
        Vector2D Ballpos=wm->ball.pos.loc;
        Ball2C = new Line2D(Ballpos , wm->ball.vel.loc.dir().degree());
        Vector2D intersection1,intersection2;

        ballvel.setDir(wm->ball.vel.loc.dir().degree());


        if(fabs(ballvel.dir().degree()-last_ballvel.dir().degree())>10)
        {

            CR.assign(wm->ourRobot[index].pos.loc,ROBOT_RADIUS+500);

        }

        last_ballvel.setDir(ballvel.dir().degree());

        CR.intersection(*Ball2C,&intersection1,&intersection2);

        if( CR.HasIntersection(*Ball2C))
        {

            if((Ballpos-intersection1).length2()>(Ballpos-intersection2).length2())
            {
                goal=intersection1;
            }

            else
            {
                goal=intersection2;
            }

            rc.fin_pos.loc=goal;
            rc.fin_pos.dir=(wm->ball.vel.loc.dir().radian()+M_PI);
        }
    }

    if((wm->ourRobot[index].pos.loc-wm->ball.pos.loc).length()<150)
    {

        this->firstTime = true;
        return true;
    }

    return false;
}
