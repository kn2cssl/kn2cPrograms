#include "skillonetouch.h"

SkillOneTouch::SkillOneTouch(WorldModel* wm, QObject *parent) :
    Skill(wm, parent)
{
    this->firstTime = true;
}

bool SkillOneTouch::execute(RobotCommand &rc)
{
    if( firstTime )
    {
        currentposition=wm->ourRobot[index].pos.loc;
        firstTime = false;
    }

    //locating in the predicted position to receive the ball...

    Vector2D robot2target= this->_Target - wm->ourRobot[index].pos.loc;
    rc.fin_pos.dir=robot2target.dir().radian();
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
        }
    }

    //kicking...
    Vector2D ball2target;

    ball2target=this->_Target - wm->ball.pos.loc;

    if( wm->isSim )
    {
        //simulation:
        Vector2D centerofrarecircle;
        ball2target.setLength(115);
        centerofrarecircle=wm->ball.pos.loc-ball2target;
        Circle2D C2(centerofrarecircle,120);
        Circle2D C(wm->ball.pos.loc,ROBOT_RADIUS+20);
        if(     wm->ball.isValid&&
                C.contains(wm->ourRobot[index].pos.loc)&&
                C2.contains(wm->ourRobot[index].pos.loc)&&
                (fabs((wm->ourRobot[index].pos.dir)-(ball2target.dir().radian())<0.08))
                )
        {
            this->firstTime = true;
            rc.kickspeedx=5;
            return true;

        }

    }
    else
    {
        //real:
        Vector2D centerofrarecircle;
        ball2target.setLength(115);
        centerofrarecircle=wm->ball.pos.loc-ball2target;
        Circle2D C2(centerofrarecircle,120);
        Circle2D C(wm->ball.pos.loc,ROBOT_RADIUS+15);
        if(     wm->ball.isValid&&
                C.contains(wm->ourRobot[index].pos.loc)&&
                C2.contains(wm->ourRobot[index].pos.loc)
                )
        {
            this->firstTime = true;
            rc.kickspeedx=10;
            return true;
        }
    }

    return false;
}








