#include "skillonetouch.h"

SkillOneTouch::SkillOneTouch(WorldModel* wm, QObject *parent) :
    Skill(wm, parent)
{
    this->firstTime = true;
    this->movementFlag = true;
}

bool SkillOneTouch::execute(RobotCommand &rc)
{
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // done...version 1.0
    rc.maxSpeed=4;
    Vector2D ballPos=wm->ball.pos.loc;
    Vector2D kickerPos=wm->ourRobot[index].pos.loc;
    Vector2D target = this->target;
    Vector2D robot2target=target-wm->ourRobot[index].pos.loc;
    Vector2D ballVelrobotCircleintersection;
    Vector2D target2robotLine;
    Vector2D ballVelRobotLineIntersection;
    Vector2D target2robotCircle;

    QList<int> ourIds = wm->kn->findNearestTo(wm->ball.pos.loc);



    //Locating in the predicted point to recieve the ball
    float lowPassFilterFactor=0.8;
    ballVelAngel=((wm->ball.vel.loc.dir().degree()-ballVelAngel)*lowPassFilterFactor)+ballVelAngel;
    qDebug()<<"ballVelAngel: "<<ballVelAngel;
    Line2D *filteredballVel = new Line2D(ballPos,ballVelAngel);
    Line2D *ballVel= new Line2D(ballPos,wm->ball.vel.loc.dir().degree());



    //    if(  ( wm->ball.vel.loc.length()<0.5 && (wm->ourRobot[ourIds.at(0)].pos.loc)-(ballPos).length()< )  ||  !(wm->ball.isValid)  )
    //    {
    //        movementFlag=true;
    //        goal = this->position;
    //        qDebug()<<"ready";
    //    }
    //    else
    //    {
    qDebug()<<"locating";
    qDebug()<<"movementFlag: "<<movementFlag;
    if( movementFlag )//movementflag bayad dar kick.cpp true shavad...vaqti dastooor shooot myad...
    {
        Vector2D temp1,temp2;

        robotCircle.assign(kickerPos,ROBOT_RADIUS+500);

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

        goal=wm->ourRobot[index].pos.loc;

        movementFlag=false;
    }

//    if(movementFlag)
//    {
//        robotCircle.assign(kickerPos,ROBOT_RADIUS+500);
//        goal=wm->ourRobot[index].pos.loc;
//        qDebug()<<"marizzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz";
//    }

    else
    {
        qDebug()<<"after mov flag if";
        ballVelRobotLineIntersection=robotLine->intersection(*filteredballVel);
        qDebug()<<"line1";
        target2robotLine=ballVelRobotLineIntersection-target;
        qDebug()<<"line2";
        target2robotLine.setLength(ROBOT_RADIUS+10);
        qDebug()<<"line3";
        goal=ballVelRobotLineIntersection+target2robotLine;
        qDebug()<<"rc.fin pos";
    }

    rc.fin_pos.loc=goal;
    rc.fin_pos.dir=robot2target.dir().radian();

    if( !wm->useShootSensor )
    {
        //without kicking sensor

        Vector2D ball2target= this->target - wm->ball.pos.loc;;
        Vector2D centerofrarecircle;
        ball2target.setLength(ROBOT_RADIUS+10);
        centerofrarecircle=wm->ball.pos.loc-ball2target;
        Circle2D rearCircle(centerofrarecircle,20);
        Circle2D ballCircle(wm->ball.pos.loc,ROBOT_RADIUS+20);
        if( wm->ball.isValid&&
                ballCircle.contains(wm->ourRobot[index].pos.loc)&&
                rearCircle.contains(wm->ourRobot[index].pos.loc)//&&
                //              fabs((ball2target.dir().degree())-((wm->ourRobot[index].pos.dir)*180/M_PI))<3
                )
        {
            rc.kickspeedx=40;
        }
    }
    else
    {
        //kicking
        if(   ((wm->ball.pos.loc-wm->ourRobot[index].pos.loc).length()<500)  &&  (   (fabs((-target2robotLine).dir().degree()-(wm->ourRobot[index].pos.dir*180/M_PI))<90)  ||  (fabs((-target2robotLine).dir().degree()-(wm->ourRobot[index].pos.dir*180/M_PI))>270)  ) )
        {
            rc.kickspeedx=200;
        }
    }


    return true;

}


//bool SkillOneTouch::execute(RobotCommand &rc)
//{
//    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//    // done...version 1.0
//    rc.maxSpeed=4;
//    Vector2D ballPos=wm->ball.pos.loc;
//    Vector2D kickerPos=wm->ourRobot[index].pos.loc;
//    Vector2D target = this->target;
//    Vector2D target2Ball = ballPos - target;
//    Vector2D robot2target=target-wm->ourRobot[index].pos.loc;
//    Vector2D ballVelrobotCircleintersection;

//    QList<int> ourIds = wm->kn->findNearestTo(wm->ball.pos.loc);

//    Line2D *ballVel;

//    qDebug()<<"========================================="<<movementFlag<<"======================================";
//    if( movementFlag )
//    {
//        qDebug()<<"11111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111";
//        if( (ballPos-wm->ourRobot[ourIds.at(0)].pos.loc) .length()>300)
//        {
//            qDebug()<<"=================================================="<<ourIds.at(0)<<"==============================================";
//            Vector2D temp1,temp2;
//            robotCircle.assign(kickerPos,ROBOT_RADIUS+500);
//            passSender2ball=ballPos-wm->ourRobot[ourIds.at(0)].pos.loc;

//            ballVel= new Line2D(wm->ourRobot[ourIds.at(0)].pos.loc,passSender2ball.dir().degree());

////            ballVel= new Line2D(ballPos,wm->ball.vel.loc.dir().degree());


//            robotCircle.intersection(*ballVel,&temp1,&temp2);

//            if((ballPos-temp1).length2()>(ballPos-temp2).length2())
//            {
//                ballVelrobotCircleintersection=temp1;
//            }
//            else
//            {
//                ballVelrobotCircleintersection=temp2;
//            }

//            target2Ball.setLength(ROBOT_RADIUS+10);
//            goal=ballVelrobotCircleintersection+target2Ball;

//            movementFlag=false;
//        }

//        else
//        {
//            qDebug()<<"22222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222";
//            goal=wm->ourRobot[index].pos.loc;
//        }

//    }

//    rc.fin_pos.loc=goal;
//    rc.fin_pos.dir=robot2target.dir().radian();



//    if( !wm->useShootSensor )
//    {
//        //without kicking sensor

//        Vector2D ball2target= this->target - wm->ball.pos.loc;;
//        Vector2D centerofrarecircle;
//        ball2target.setLength(ROBOT_RADIUS+10);
//        centerofrarecircle=wm->ball.pos.loc-ball2target;
//        Circle2D rearCircle(centerofrarecircle,20);
//        Circle2D ballCircle(wm->ball.pos.loc,ROBOT_RADIUS+20);
//        if( wm->ball.isValid&&
//                ballCircle.contains(wm->ourRobot[index].pos.loc)&&
//                rearCircle.contains(wm->ourRobot[index].pos.loc)//&&
//                //              fabs((ball2target.dir().degree())-((wm->ourRobot[index].pos.dir)*180/M_PI))<3
//                )
//        {
//            if( wm->isSim )
//                rc.kickspeedx = 8;
//            else
//                rc.kickspeedx=40;
//        }
//    }
//    else
//    {
//        //kicking
//        if(   (((wm->ball.pos.loc-wm->ourRobot[index].pos.loc).length()<500) )  )//&& (    (fabs((-target2robotLine).dir().degree()-(wm->ourRobot[index].pos.dir*180/M_PI))<90)  ||  (fabs((-target2robotLine).dir().degree()-(wm->ourRobot[index].pos.dir*180/M_PI))>270)  ) )
//        {
//            if( wm->isSim )
//                rc.kickspeedx = 8;
//            else
//                rc.kickspeedx=200;
//        }
//    }

//    return true;

//}



//bool SkillOneTouch::execute(RobotCommand &rc)
//{
//    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//    // done...version 1.0
//    rc.maxSpeed=4;
//    Vector2D ballPos=wm->ball.pos.loc;
//    Vector2D kickerPos=wm->ourRobot[index].pos.loc;
//    Vector2D target = this->target;
//    Vector2D target2Ball= ballPos - target;
//    Vector2D robot2target=target-wm->ourRobot[index].pos.loc;
//    QList<int> ourIds = wm->kn->findNearestTo(wm->ball.pos.loc);


//    if( movementFlag )
//    {
//        qDebug()<<"11111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111";
//        if( (ballPos-wm->ourRobot[ourIds.at(0)].pos.loc) .length()>200)
//        {
//            qDebug()<<"==================================="<<ourIds.at(0)<<"===================================";
//            Line2D *robotLine =new Line2D (kickerPos,robot2target.rotatedVector(90).dir().degree());
//            passSender2ball=ballPos-wm->ourRobot[ourIds.at(0)].pos.loc;
//            Line2D *ballVel= new Line2D(ballPos,passSender2ball.dir().degree());

//            Vector2D ballVelrobotLineintersection=robotLine->intersection(*ballVel);

//            target2Ball.setLength(ROBOT_RADIUS+10);

//            goal=ballVelrobotLineintersection+target2Ball;

//            movementFlag=false;
//        }

//        else
//        {

//            qDebug()<<"222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222";
//            goal=wm->ourRobot[index].pos.loc;
//        }

//    }


//    rc.fin_pos.loc=goal;
//    rc.fin_pos.dir=robot2target.dir().radian();



//    if( !wm->useShootSensor )
//    {
//        //without kicking sensor

//        Vector2D ball2target= this->target - wm->ball.pos.loc;;
//        Vector2D centerofrarecircle;
//        ball2target.setLength(ROBOT_RADIUS+10);
//        centerofrarecircle=wm->ball.pos.loc-ball2target;
//        Circle2D rearCircle(centerofrarecircle,20);
//        Circle2D ballCircle(wm->ball.pos.loc,ROBOT_RADIUS+20);
//        if( wm->ball.isValid&&
//                ballCircle.contains(wm->ourRobot[index].pos.loc)&&
//                rearCircle.contains(wm->ourRobot[index].pos.loc)//&&
//                //              fabs((ball2target.dir().degree())-((wm->ourRobot[index].pos.dir)*180/M_PI))<3
//                )
//        {
//            rc.kickspeedx=40;
//        }
//    }
//    else
//    {
//        //kicking
//        if(   (((wm->ball.pos.loc-wm->ourRobot[index].pos.loc).length()<500) )  )//&& (    (fabs((-target2robotLine).dir().degree()-(wm->ourRobot[index].pos.dir*180/M_PI))<90)  ||  (fabs((-target2robotLine).dir().degree()-(wm->ourRobot[index].pos.dir*180/M_PI))>270)  ) )
//        {
//            rc.kickspeedx=200;
//        }
//    }

//    return true;

//}






void SkillOneTouch::setTarget(const Vector2D target)
{
    this->target = target;
}

void SkillOneTouch::resetAllFlags()
{
    this->movementFlag = true;
}
