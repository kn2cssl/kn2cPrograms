#include "skillonetouch.h"

SkillOneTouch::SkillOneTouch(WorldModel* wm, QObject *parent) :
    Skill(wm, parent)
{
    this->firstTime = true;
}

bool SkillOneTouch::execute(RobotCommand &rc)
{
    //    if( firstTime )
    //    {
    //        currentposition=wm->ourRobot[index].pos.loc;
    //        firstTime = false;
    //    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // done...version 1.0
    rc.maxSpeed=3;
    Vector2D ballPos=wm->ball.pos.loc;
    Vector2D kickerPos=wm->ourRobot[index].pos.loc;
    Vector2D target = this->target;
    Vector2D robot2target=target-wm->ourRobot[index].pos.loc;
    Vector2D ballVelrobotCircleintersection;
    Vector2D target2robotLine;
    Vector2D ballVelRobotLineIntersection;
    Vector2D target2robotCircle;

    //Locating in the predicted point to recieve the ball
    float lowPassFilterFactor=0.2;
    ballVelAngel=((wm->ball.vel.loc.dir().degree()-ballVelAngel)*lowPassFilterFactor)+ballVelAngel;
    Line2D *filteredballVel = new Line2D(ballPos,ballVelAngel);
    Line2D *ballVel= new Line2D(ballPos,wm->ball.vel.loc.dir().degree());
    Circle2D checkingCircle(kickerPos,ROBOT_RADIUS+500);

    if(!(checkingCircle.HasIntersection(*ballVel)) || wm->ball.vel.loc.length()<0.2 ||  !(wm->ball.isValid) )
    {
        movementFlag=true;
        goal = this->position;
        qDebug()<<"ready";
    }
    else
    {
        qDebug()<<"locating";
        if(movementFlag)//movementflag bayad dar kick.cpp true shavad...vaqti dastooor shooot myad...
        {
            robotCircle.assign(kickerPos,ROBOT_RADIUS+500);
            Vector2D temp1,temp2;
            robotCircle.intersection(*ballVel,&temp1,&temp2);

            if((ballPos-temp1).length2()>(ballPos-temp2).length2())
            {
                ballVelrobotCircleintersection=temp1;
            }
            else
            {
                ballVelrobotCircleintersection=temp2;
            }

            target2robotCircle=ballVelrobotCircleintersection-target;
            Vector2D temp=target2robotCircle.rotatedVector(90);
            robotLine=new Line2D(ballVelrobotCircleintersection,temp.dir().degree());

            movementFlag=false;
        }
        ballVelRobotLineIntersection=robotLine->intersection(*filteredballVel);
        target2robotLine=ballVelRobotLineIntersection-target;
        target2robotLine.setLength(ROBOT_RADIUS+10);
        goal=ballVelRobotLineIntersection+target2robotLine;
    }

    rc.fin_pos.loc=goal;
    rc.fin_pos.dir=robot2target.dir().radian();

    //kicking
    if(   ((wm->ball.pos.loc-wm->ourRobot[index].pos.loc).length()<500)  &&  (   (fabs((-target2robotLine).dir().degree()-(wm->ourRobot[index].pos.dir*180/M_PI))<90)  ||  (fabs((-target2robotLine).dir().degree()-(wm->ourRobot[index].pos.dir*180/M_PI))>270)  ) )
    {
        rc.kickspeedx=200;
        //        this->firstTime = true;
        //        return true;
    }

    //        return false;

    //returning from onetouch state
    if(wm->ball.vel.loc.length()<0.2)
    {
        return false;
    }
    else
    {
        if( fabs((-target2robotLine).dir().degree()-wm->ball.vel.loc.dir().degree())>45 && fabs((-target2robotLine).dir().degree()-wm->ball.vel.loc.dir().degree())<135 )
        {
            return false;
        }
    }

    return true;

}

void SkillOneTouch::setTarget(const Vector2D target)
{
    this->target = target;
}

void SkillOneTouch::setPosition(const Vector2D position)
{
    this->position = position;
}
