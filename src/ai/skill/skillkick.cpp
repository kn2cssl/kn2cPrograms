#include "skillkick.h"

SkillKick::SkillKick(WorldModel* wm, QObject *parent) :
    Skill(wm, parent)
{
    isShoot = true;
}

bool SkillKick::execute(RobotCommand &rc)
{
/*cod khodam*/

//    //locating behind the ball...

//    Vector2D goal;

//    Vector2D ball2target;

//    ball2target=this->_Target - wm->ball.pos.loc;

//    ball2target.setLength(ROBOT_RADIUS+8);

//    goal=wm->ball.pos.loc - ball2target;

//    //    Vector2D checkingPoint;

//    //    ball2target.setLength(2*ROBOT_RADIUS+20);

//    //    checkingPoint=wm->ball.pos.loc - ball2target;

//    //    Segment2D *kicker2chekingPoint=new Segment2D(wm->ourRobot[index].pos.loc,checkingPoint);

//    //    Circle2D checkingCircle(wm->ball.pos.loc,ROBOT_RADIUS*2);


//    Circle2D checkingCircle(wm->ball.pos.loc,ROBOT_RADIUS);
//    Segment2D *kicker2goal=new Segment2D(wm->ourRobot[index].pos.loc,goal);

//    if( checkingCircle.HasIntersection( *kicker2goal ) )
//    {
//        ball2target.setLength(200+200);
//        Vector2D temp1=goal+(-ball2target).rotatedVector(60);
//        Vector2D temp2=goal+(-ball2target).rotatedVector(-60);
//        if((wm->ourRobot[index].pos.loc-temp1).length2()<(wm->ourRobot[index].pos.loc-temp2).length2())
//        {
//            goal=temp1;
//        }
//        else
//        {
//            goal=temp2;
//        }
//    }

//    rc.fin_pos.loc=goal;

//    rc.fin_pos.dir=ball2target.dir().radian();




//    //kicking...

//    if( wm->isSim )
//    {
//        //simulatuion
//        Vector2D centerofrarecircle;
//        ball2target.setLength(ROBOT_RADIUS+10);
//        centerofrarecircle=wm->ball.pos.loc-ball2target;
//        Circle2D rearCircle(centerofrarecircle,20);
//        Circle2D ballCircle(wm->ball.pos.loc,ROBOT_RADIUS+50);
//        if( wm->ball.isValid&&
//                ballCircle.contains(wm->ourRobot[index].pos.loc)&&
//                rearCircle.contains(wm->ourRobot[index].pos.loc)//&&
//                //              fabs((ball2target.dir().degree())-((wm->ourRobot[index].pos.dir)*180/M_PI))<3
//                )
//        {
//            if( !isShoot )
//                rc.kickspeedx = 3.5;
//            else
//                rc.kickspeedx = 8;
//        }
//    }
//    else
//    {
//        // real:

//        if( !wm->useShootSensor )
//        {
//            //without kicking sensor
//            Vector2D centerofrarecircle;
//            ball2target.setLength(ROBOT_RADIUS+10);
//            centerofrarecircle=wm->ball.pos.loc-ball2target;
//            Circle2D rearCircle(centerofrarecircle,20);
//            Circle2D ballCircle(wm->ball.pos.loc,ROBOT_RADIUS+20);
//            if( wm->ball.isValid&&
//                    ballCircle.contains(wm->ourRobot[index].pos.loc)&&
//                    rearCircle.contains(wm->ourRobot[index].pos.loc)//&&
//                    //              fabs((ball2target.dir().degree())-((wm->ourRobot[index].pos.dir)*180/M_PI))<3
//                    )
//            {
//                if( !isShoot )
//                    rc.kickspeedx = 30;
//                else
//                    rc.kickspeedx = 100;
//            }
//        }
//        else
//        {
//            //with kicking sensor
//            if(  ((wm->ball.pos.loc-wm->ourRobot[index].pos.loc).length()<500)  &&  (fabs((ball2target.dir().degree())-((wm->ourRobot[index].pos.dir)*180/M_PI))<90  || fabs((ball2target.dir().degree())-((wm->ourRobot[index].pos.dir)*180/M_PI))>270)  )
//            {
//                if( !isShoot )
//                    rc.kickspeedx = 140;
//                else
//                    rc.kickspeedx = 200;
//                //            if(passFlag)
//                //            {
//                //                rc.kickspeedx=sqrt(2*10*lossFactor*(this->_Target-wm->ourRobot[index].pos.loc).length());
//                //            }
//            }
//        }
//    }

}








//        Vector2D S=wm->oppRobot[0].pos.loc-target;//-wm->oppRobot[0].pos.loc;
//        S.setDir(wm->ourRobot[0].pos.dir*(180/M_PI));














































//    //    //    1 && 2

////    if(wm->ball.vel.loc.length()<0.05)
////    {
////        if((wm->ball.pos.loc-wm->ourRobot[0].pos.loc).length2()>(wm->ball.pos.loc-wm->ourRobot[1].pos.loc).length2())
////        {
////            kicker0=false;
////            receiver0=true;

////            kicker1=true;
////            receiver1=false;
////        }

////        else if((wm->ball.pos.loc-wm->ourRobot[0].pos.loc).length2()<(wm->ball.pos.loc-wm->ourRobot[1].pos.loc).length2())
////        {
////            kicker0=true;
////            receiver0=false;

////            kicker1=false;
////            receiver1=true;
////        }


////    }




////    if(index==0)
////    {
////        if(kicker0)
////        {
////            //locating behind the ball...

////            Vector2D ball2target;



////            Vector2D target=wm->ourRobot[1].pos.loc;//{2470,0};

////            ball2target=target-wm->ball.pos.loc;

////            ball2target.setLength(95);


////            rc.fin_pos.loc=wm->ball.pos.loc - ball2target;

////            rc.fin_pos.dir=ball2target.dir().radian();



////            ///////////////////////////////////////////////////////////////////////////////////////////////////////////////

////            // kicking

////            if( wm->isSim )
////            {
////                //simulation:
////                Vector2D A;
////                ball2target.setLength(115);
////                A=wm->ball.pos.loc-ball2target;
////                Circle2D C2(A,120);
////                Circle2D C(wm->ball.pos.loc,ROBOT_RADIUS+20);
////                if( wm->ball.isValid&&
////                        C.contains(wm->ourRobot[index].pos.loc)&&
////                        C2.contains(wm->ourRobot[index].pos.loc)&&
////                        (fabs(((wm->ourRobot[1].pos.loc-wm->ourRobot[index].pos.loc).dir().degree())-(ball2target.dir().degree())<10))
////                        )
////                {
////                    rc.kickspeedx=5;
////                    receiver0=false;
////                    kicker0=false;

////                }
////            }
////            else
////            {
////                //real:
////                Vector2D A;
////                vec2goal.setLength(115);
////                A=wm->ball.pos.loc-vec2goal;
////                Circle2D C2(A,120);
////                Circle2D C(wm->ball.pos.loc,ROBOT_RADIUS+15);
////                if( wm->ball.isValid&&
////                        C.contains(wm->ourRobot[0].pos.loc)&&
////                        C2.contains(wm->ourRobot[0].pos.loc)
////                        )
////                {
////                    rc.kickspeedx=10;
////                }
////            }
////        }

////        else if(receiver0)
////        {
//RecievingPass


//            Vector2D robot2ball=wm->ball.pos.loc-wm->ourRobot[index].pos.loc;
//            rc.fin_pos.dir=robot2ball.dir().radian();

//            rc.fin_pos.loc=wm->ourRobot[index].pos.loc;//{0,0};
//            //rc.maxSpeed=3;


//            if (wm->ball.vel.loc.length()>0.1)
//            {
//                Vector2D goal;
//                Vector2D Ballpos=wm->ball.pos.loc;
//                Ball2C = new Line2D(Ballpos , wm->ball.vel.loc.dir().degree());
//                Vector2D A,B;

//                ballvel.setDir(wm->ball.vel.loc.dir().degree());


//                if(fabs(ballvel.dir().degree()-last_ballvel.dir().degree())>10)
//                {

//                    C0.assign(wm->ourRobot[0].pos.loc,ROBOT_RADIUS+500);

//                }

//                last_ballvel.setDir(ballvel.dir().degree());



//                C0.intersection(*Ball2C,&A,&B);

//                if( C0.HasIntersection(*Ball2C))
//                {

//                    if((Ballpos-A).length2()>(Ballpos-B).length2())
//                    {
//                        goal=A;
//                    }

//                    else
//                    {
//                        goal=B;
//                    }

//                    rc.fin_pos.loc=goal;
//                    rc.fin_pos.dir=(wm->ball.vel.loc.dir().radian()+M_PI);//tttarget.dir().radian();//


//                }



//            }
//            ////////////////////////////////////////////////////////////////////////////////
//            //change decision
//            //Circle2D CD(wm->ourRobot[index].pos.loc,C0.radius()+300);
//            if((wm->ourRobot[index].pos.loc-wm->ball.pos.loc).length()<150)
//            {
//                kicker0=true;
//                receiver0=false;

//                kicker1=false;
//                receiver1=true;
//            }

////            /////////////////////////////////////////////////////////////////////////////////
////        }


////        else if(!kicker0 && !receiver0)//kicker no!!!!  receiver no!!!>>>>....
////        {
////            Vector2D robot2ball=wm->ball.pos.loc-wm->ourRobot[index].pos.loc;
////            rc.fin_pos.dir=robot2ball.dir().radian();

////            rc.fin_pos.loc=wm->ourRobot[index].pos.loc;//{0,0};
////        }

////    }

//    else if(index==1)
//    {
//        if(kicker1)
//        {
//            //locating behind the ball...

//            Vector2D ball2target;


//            Vector2D target=wm->ourRobot[0].pos.loc;//{2470,0};

//            ball2target=target-wm->ball.pos.loc;

//            ball2target.setLength(95);



//            rc.fin_pos.loc=wm->ball.pos.loc - ball2target;

//            rc.fin_pos.dir=ball2target.dir().radian();



///////////////////////////////////////////////////////////////////////////////////////////////////////////////

// kicking


//real:
//    Vector2D A;
//    vec2goal.setLength(115);
//    A=wm->ball.pos.loc-vec2goal;
//    Circle2D C2(A,120);
//    Circle2D C(wm->ball.pos.loc,ROBOT_RADIUS+15);
//    if( wm->ball.isValid&&
//        C.contains(wm->ourRobot[0].pos.loc)&&
//        C2.contains(wm->ourRobot[0].pos.loc)
//      )
//    {
//        rc.kickspeedx=10;
//    }



//            //simulation:
//            Vector2D A;
//            ball2target.setLength(115);
//            A=wm->ball.pos.loc-ball2target;
//            Circle2D C2(A,120);
//            Circle2D C(wm->ball.pos.loc,ROBOT_RADIUS+20);
//            if( wm->ball.isValid&&
//                    C.contains(wm->ourRobot[index].pos.loc)&&
//                    C2.contains(wm->ourRobot[index].pos.loc)&&
//                    (fabs(((wm->ourRobot[0].pos.loc-wm->ourRobot[index].pos.loc).dir().degree())-(ball2target.dir().degree())<5))
//                    )

//            {
//                //qDebug()<<","<<fabs(((wm->ourRobot[0].pos.loc-wm->ourRobot[index].pos.loc).dir().degree())-(ball2target.dir().degree()));
//                rc.kickspeedx=5;
//                kicker1=false;
//                receiver1=false;

//            }
//        }


//        else if(receiver1)
//        {
//            //RecievingPass

//            //rc.maxSpeed=2;


//            Vector2D robot2ball=wm->ball.pos.loc-wm->ourRobot[index].pos.loc;
//            rc.fin_pos.dir=robot2ball.dir().radian();

//            rc.fin_pos.loc=wm->ourRobot[index].pos.loc;//{0,0};//


//            if (wm->ball.vel.loc.length()>0.1)
//            {
//                Vector2D goal;
//                Vector2D Ballpos=wm->ball.pos.loc;
//                Ball2C = new Line2D(Ballpos , wm->ball.vel.loc.dir().degree());
//                Vector2D A,B;

//                ballvel.setDir(wm->ball.vel.loc.dir().degree());


//                if(fabs(ballvel.dir().degree()-last_ballvel.dir().degree())>10)
//                {

//                    C1.assign(wm->ourRobot[index].pos.loc,ROBOT_RADIUS+500);

//                }

//                last_ballvel.setDir(ballvel.dir().degree());



//                C1.intersection(*Ball2C,&A,&B);

//                if( C1.HasIntersection(*Ball2C))
//                {
//                    if((Ballpos-A).length2()>(Ballpos-B).length2())
//                    {
//                        goal=A;
//                    }

//                    else
//                    {
//                        goal=B;
//                    }

//                    rc.fin_pos.loc=goal;
//                    rc.fin_pos.dir=(wm->ball.vel.loc.dir().radian()+M_PI);


//                }



//            }

//            ////////////////////////////////////////////////////////////////////////////////
//            //change decision
//            //Circle2D CD(wm->ourRobot[index].pos.loc,100);
//            if((wm->ourRobot[index].pos.loc-wm->ball.pos.loc).length()<150)
//            {


//                kicker0=false;
//                receiver0=true;

//                kicker1=true;
//                receiver1=false;
//            }

//            /////////////////////////////////////////////////////////////////////////////////


//        }



//        else if(!kicker1 && !receiver1)//kicker no!!!!  receiver no!!!>>>>....
//        {
//            Vector2D robot2ball=wm->ball.pos.loc-wm->ourRobot[index].pos.loc;
//            rc.fin_pos.dir=robot2ball.dir().radian();

//            rc.fin_pos.loc=wm->ourRobot[index].pos.loc;//{0,0};
//        }

//    }































//    //......WON touch.....




//    if(index==0)
//    {
//        if(true)
//        {

//            //locating behind the ball...

//            Vector2D ball2target;

//            Vector2D target=wm->ourRobot[1].pos.loc;//{2470,0};

//            ball2target=target-wm->ball.pos.loc;

//            ball2target.setLength(95);

//            rc.fin_pos.loc=wm->ball.pos.loc - ball2target;

//            rc.fin_pos.dir=ball2target.dir().radian();





//            // kicking

//            //simulation:
//            Vector2D A;
//            ball2target.setLength(115);
//            A=wm->ball.pos.loc-ball2target;
//            Circle2D C2(A,120);
//            Circle2D C(wm->ball.pos.loc,ROBOT_RADIUS+20);
//            if(     wm->ball.isValid&&
//                    C.contains(wm->ourRobot[index].pos.loc)&&
//                    C2.contains(wm->ourRobot[index].pos.loc)&&
//                    (fabs(((wm->ourRobot[1].pos.loc-wm->ourRobot[index].pos.loc).dir().degree())-(ball2target.dir().degree())<3))
//                    )
//            {
//                rc.kickspeedx=5;
//            }





//        }


//    }





//    if(index==1)
//    {



//        //        qDebug()<<wm->ourRobot[index].pos.dir;


//        if(true)
//        {

//            //locating in the safe position to recieve the pass

//            rc.maxSpeed=3;


//            Vector2D target={-3000,0};

//            Vector2D robot2target=target-wm->ourRobot[index].pos.loc;
//            rc.fin_pos.dir=robot2target.dir().radian();

//            rc.fin_pos.loc=wm->ourRobot[index].pos.loc;//{0,0};//


//            if (wm->ball.vel.loc.length()>0.1)
//            {
//                Vector2D goal;
//                Vector2D Ballpos=wm->ball.pos.loc;
//                Ball2C = new Line2D(Ballpos , wm->ball.vel.loc.dir().degree());
//                Vector2D A,B;

//                ballvel.setDir(wm->ball.vel.loc.dir().degree());


//                if(fabs(ballvel.dir().degree()-last_ballvel.dir().degree())>10)
//                {

//                    C1.assign(wm->ourRobot[index].pos.loc,ROBOT_RADIUS+500);

//                }

//                last_ballvel.setDir(ballvel.dir().degree());



//                C1.intersection(*Ball2C,&A,&B);

//                if( C1.HasIntersection(*Ball2C))
//                {
//                    if((Ballpos-A).length2()>(Ballpos-B).length2())
//                    {
//                        goal=A;
//                    }

//                    else
//                    {
//                        goal=B;
//                    }

//                    rc.fin_pos.loc=goal;


//                }

//            }



//            //simulation:

//            Vector2D ball2target;

//            target={-3000,0};//wm->ourRobot[1].pos.loc;//
//            ball2target=target-wm->ball.pos.loc;




//            Vector2D A;
//            ball2target.setLength(115);
//            A=wm->ball.pos.loc-ball2target;
//            Circle2D C2(A,120);
//            Circle2D C(wm->ball.pos.loc,ROBOT_RADIUS+20);
//            if(
//                    wm->ball.isValid&&
//                    C.contains(wm->ourRobot[index].pos.loc)&&
//                    C2.contains(wm->ourRobot[index].pos.loc)&&
//                    (fabs(((target-wm->ourRobot[index].pos.loc).dir().radian())-(wm->ourRobot[index].pos.dir))<0.02*M_PI)
//                    )

//            {



//                rc.kickspeedx=10;

//            }



//        }


//    }


















































//    //    //    1 && 2 && 3

//    //        if(wm->ball.vel.loc.length()<0.05)
//    //        {
//    ////            if((wm->ball.pos.loc-wm->ourRobot[0].pos.loc).length2()>(wm->ball.pos.loc-wm->ourRobot[1].pos.loc).length2())
//    ////            {
//    ////                kicker0=false;
//    ////                receiver0=true;

//    ////                kicker1=true;
//    ////                receiver1=false;
//    ////            }

//    ////            else if((wm->ball.pos.loc-wm->ourRobot[0].pos.loc).length2()<(wm->ball.pos.loc-wm->ourRobot[1].pos.loc).length2())
//    ////            {
//    ////                kicker0=true;
//    ////                receiver0=false;

//    ////                kicker1=false;
//    ////                receiver1=true;
//    ////            }


//    //            kicker0=true;
//    //            receiver0=false;

//    //            kicker1=false;
//    //            receiver1=true;

//    //            kicker2=false;
//    //            receiver2=false;




//    //        }




//    //        if(index==0)
//    //        {
//    //            if(kicker0)
//    //            {
//    //                //locating behind the ball...

//    //                Vector2D ball2target;

//    //                Vector2D target=wm->ourRobot[1].pos.loc;//{2470,0};

//    //                ball2target=target-wm->ball.pos.loc;

//    //                ball2target.setLength(95);

//    //                rc.fin_pos.loc=wm->ball.pos.loc - ball2target;

//    //                rc.fin_pos.dir=ball2target.dir().radian();

//    //                ///////////////////////////////////////////////////////////////////////////////////////////////////////////////

//    //                // kicking


//    //                //real:
//    //                //    Vector2D A;
//    //                //    vec2goal.setLength(115);
//    //                //    A=wm->ball.pos.loc-vec2goal;
//    //                //    Circle2D C2(A,120);
//    //                //    Circle2D C(wm->ball.pos.loc,ROBOT_RADIUS+15);
//    //                //    if( wm->ball.isValid&&
//    //                //        C.contains(wm->ourRobot[0].pos.loc)&&
//    //                //        C2.contains(wm->ourRobot[0].pos.loc)
//    //                //      )
//    //                //    {
//    //                //        rc.kickspeedx=10;
//    //                //    }



//    //                //simulation:
//    //                Vector2D A;
//    //                ball2target.setLength(115);
//    //                A=wm->ball.pos.loc-ball2target;
//    //                Circle2D C2(A,120);
//    //                Circle2D C(wm->ball.pos.loc,ROBOT_RADIUS+20);
//    //                if( wm->ball.isValid&&
//    //                        C.contains(wm->ourRobot[index].pos.loc)&&
//    //                        C2.contains(wm->ourRobot[index].pos.loc)&&
//    //                        (fabs(((wm->ourRobot[1].pos.loc-wm->ourRobot[index].pos.loc).dir().degree())-(ball2target.dir().degree())<10))
//    //                        )
//    //                {
//    //                    rc.kickspeedx=5;
//    //                    receiver0=false;
//    //                    kicker0=false;

//    //                }


//    //            }

//    //            else if(receiver0)
//    //            {
//    //                //RecievingPass


//    //                Vector2D ball2target;
//    //                Vector2D target=wm->ourRobot[1].pos.loc;//{2470,0};
//    //                ball2target=target-wm->ball.pos.loc;
//    //                Vector2D robot2ball=wm->ball.pos.loc-wm->ourRobot[index].pos.loc;


//    //                //rc.fin_pos.dir=robot2ball.dir().radian();

//    //                rc.fin_pos.dir=ball2target.dir().radian();

//    //                rc.fin_pos.loc=wm->ourRobot[index].pos.loc;//{0,0};
//    //                //rc.maxSpeed=3;


//    //                if (wm->ball.vel.loc.length()>0.1)
//    //                {
//    //                    Vector2D goal;
//    //                    Vector2D Ballpos=wm->ball.pos.loc;
//    //                    Ball2C = new Line2D(Ballpos , wm->ball.vel.loc.dir().degree());
//    //                    Vector2D A,B;

//    //                    ballvel.setDir(wm->ball.vel.loc.dir().degree());


//    //                    if(fabs(ballvel.dir().degree()-last_ballvel.dir().degree())>10)
//    //                    {

//    //                        C0.assign(wm->ourRobot[0].pos.loc,ROBOT_RADIUS+500);

//    //                    }

//    //                    last_ballvel.setDir(ballvel.dir().degree());



//    //                    C0.intersection(*Ball2C,&A,&B);

//    //                    if( C0.HasIntersection(*Ball2C))
//    //                    {

//    //                        if((Ballpos-A).length2()>(Ballpos-B).length2())
//    //                        {
//    //                            goal=A;
//    //                        }

//    //                        else
//    //                        {
//    //                            goal=B;
//    //                        }

//    //                        rc.fin_pos.loc=goal;
//    //                        rc.fin_pos.dir=(wm->ball.vel.loc.dir().radian()+M_PI);//tttarget.dir().radian();//


//    //                    }



//    //                }
//    //                ////////////////////////////////////////////////////////////////////////////////
//    //                //change decision
//    //                //Circle2D CD(wm->ourRobot[index].pos.loc,C0.radius()+300);
//    //                if((wm->ourRobot[index].pos.loc-wm->ball.pos.loc).length()<300)
//    //                {
//    //                    kicker0=true;
//    //                    receiver0=false;

//    //                    kicker1=false;
//    //                    receiver1=true;

//    //                    kicker2=false;
//    //                    receiver2=false;
//    //                }

//    //                /////////////////////////////////////////////////////////////////////////////////
//    //            }


//    //            else if(!kicker0 && !receiver0)//kicker no!!!!  receiver no!!!>>>>....
//    //            {
//    //                Vector2D robot2ball=wm->ball.pos.loc-wm->ourRobot[index].pos.loc;
//    //                rc.fin_pos.dir=robot2ball.dir().radian();

//    //                rc.fin_pos.loc=wm->ourRobot[index].pos.loc;//{0,0};
//    //            }

//    //        }

//    //        else if(index==1)
//    //        {
//    //            if(kicker1)
//    //            {
//    //                //locating behind the ball...

//    //                Vector2D ball2target;

//    //                Vector2D target=wm->ourRobot[2].pos.loc;//{2470,0};

//    //                ball2target=target-wm->ball.pos.loc;

//    //                ball2target.setLength(95);

//    //                rc.fin_pos.loc=wm->ball.pos.loc - ball2target;

//    //                rc.fin_pos.dir=ball2target.dir().radian();

//    //                ///////////////////////////////////////////////////////////////////////////////////////////////////////////////

//    //                // kicking


//    //                //real:
//    //                //    Vector2D A;
//    //                //    vec2goal.setLength(115);
//    //                //    A=wm->ball.pos.loc-vec2goal;
//    //                //    Circle2D C2(A,120);
//    //                //    Circle2D C(wm->ball.pos.loc,ROBOT_RADIUS+15);
//    //                //    if( wm->ball.isValid&&
//    //                //        C.contains(wm->ourRobot[0].pos.loc)&&
//    //                //        C2.contains(wm->ourRobot[0].pos.loc)
//    //                //      )
//    //                //    {
//    //                //        rc.kickspeedx=10;
//    //                //    }



//    //                //simulation:
//    //                Vector2D A;
//    //                ball2target.setLength(115);
//    //                A=wm->ball.pos.loc-ball2target;
//    //                Circle2D C2(A,120);
//    //                Circle2D C(wm->ball.pos.loc,ROBOT_RADIUS+20);
//    //                if( wm->ball.isValid&&
//    //                        C.contains(wm->ourRobot[index].pos.loc)&&
//    //                        C2.contains(wm->ourRobot[index].pos.loc)&&
//    //                        (fabs(((wm->ourRobot[2].pos.loc-wm->ourRobot[index].pos.loc).dir().degree())-(ball2target.dir().degree())<5))
//    //                  )

//    //                {
//    //                    rc.kickspeedx=5;
//    //                    kicker1=false;
//    //                    receiver1=false;

//    //                }
//    //            }


//    //            else if(receiver1)
//    //            {
//    //                //RecievingPass

//    //                //rc.maxSpeed=2;

//    //                Vector2D ball2target;
//    //                Vector2D target=wm->ourRobot[0].pos.loc;//{2470,0};
//    //                ball2target=target-wm->ball.pos.loc;
//    //                Vector2D robot2ball=wm->ball.pos.loc-wm->ourRobot[index].pos.loc;
//    //                //rc.fin_pos.dir=robot2ball.dir().radian();

//    //                rc.fin_pos.loc=wm->ourRobot[index].pos.loc;//{0,0};//

//    //                rc.fin_pos.dir=robot2ball.dir().radian();


//    //                if (wm->ball.vel.loc.length()>0.1)
//    //                {
//    //                    Vector2D goal;
//    //                    Vector2D Ballpos=wm->ball.pos.loc;
//    //                    Ball2C = new Line2D(Ballpos , wm->ball.vel.loc.dir().degree());
//    //                    Vector2D A,B;

//    //                    ballvel.setDir(wm->ball.vel.loc.dir().degree());


//    //                    if(fabs(ballvel.dir().degree()-last_ballvel.dir().degree())>10)
//    //                    {

//    //                        C1.assign(wm->ourRobot[index].pos.loc,ROBOT_RADIUS+500);

//    //                    }

//    //                    last_ballvel.setDir(ballvel.dir().degree());



//    //                    C1.intersection(*Ball2C,&A,&B);

//    //                    if( C1.HasIntersection(*Ball2C))
//    //                    {
//    //                        if((Ballpos-A).length2()>(Ballpos-B).length2())
//    //                        {
//    //                            goal=A;
//    //                        }

//    //                        else
//    //                        {
//    //                            goal=B;
//    //                        }

//    //                        rc.fin_pos.loc=goal;
//    //                        rc.fin_pos.dir=(wm->ball.vel.loc.dir().radian()+M_PI);


//    //                    }



//    //                }

//    //                ////////////////////////////////////////////////////////////////////////////////
//    //                //change decision
//    //                //Circle2D CD(wm->ourRobot[index].pos.loc,100);
//    //                if((wm->ourRobot[index].pos.loc-wm->ball.pos.loc).length()<300)
//    //                {
//    //                    kicker0=false;
//    //                    receiver0=false;

//    //                    kicker1=true;
//    //                    receiver1=false;

//    //                    kicker2=false;
//    //                    receiver2=true;
//    //                }

//    //                /////////////////////////////////////////////////////////////////////////////////


//    //            }



//    //            else if(!kicker1 && !receiver1)//kicker no!!!!  receiver no!!!>>>>....
//    //            {
//    //                Vector2D robot2ball=wm->ball.pos.loc-wm->ourRobot[index].pos.loc;
//    //                rc.fin_pos.dir=robot2ball.dir().radian();

//    //                rc.fin_pos.loc=wm->ourRobot[index].pos.loc;//{0,0};
//    //            }

//    //        }





//    //        else if(index==2)
//    //        {
//    //            if(kicker2)
//    //            {
//    //                //locating behind the ball...

//    //                Vector2D ball2target;

//    //                Vector2D target=wm->ourRobot[0].pos.loc;//{2470,0};

//    //                ball2target=target-wm->ball.pos.loc;

//    //                ball2target.setLength(95);

//    //                rc.fin_pos.loc=wm->ball.pos.loc - ball2target;

//    //                rc.fin_pos.dir=ball2target.dir().radian();

//    //                ///////////////////////////////////////////////////////////////////////////////////////////////////////////////

//    //                // kicking


//    //                //real:
//    //                //    Vector2D A;
//    //                //    vec2goal.setLength(115);
//    //                //    A=wm->ball.pos.loc-vec2goal;
//    //                //    Circle2D C2(A,120);
//    //                //    Circle2D C(wm->ball.pos.loc,ROBOT_RADIUS+15);
//    //                //    if( wm->ball.isValid&&
//    //                //        C.contains(wm->ourRobot[0].pos.loc)&&
//    //                //        C2.contains(wm->ourRobot[0].pos.loc)
//    //                //      )
//    //                //    {
//    //                //        rc.kickspeedx=10;
//    //                //    }



//    //                //simulation:
//    //                Vector2D A;
//    //                ball2target.setLength(115);
//    //                A=wm->ball.pos.loc-ball2target;
//    //                Circle2D C2(A,120);
//    //                Circle2D C(wm->ball.pos.loc,ROBOT_RADIUS+20);
//    //                if( wm->ball.isValid&&
//    //                        C.contains(wm->ourRobot[index].pos.loc)&&
//    //                        C2.contains(wm->ourRobot[index].pos.loc)&&
//    //                        (fabs(((wm->ourRobot[0].pos.loc-wm->ourRobot[index].pos.loc).dir().degree())-(ball2target.dir().degree())<5))
//    //                  )

//    //                {
//    //                    rc.kickspeedx=5;
//    //                    kicker2=false;
//    //                    receiver2=false;

//    //                }
//    //            }


//    //            else if(receiver2)
//    //            {
//    //                //RecievingPass

//    //                //rc.maxSpeed=2;


//    //                Vector2D ball2target;
//    //                Vector2D target=wm->ourRobot[0].pos.loc;//{2470,0};
//    //                ball2target=target-wm->ball.pos.loc;


//    //                Vector2D robot2ball=wm->ball.pos.loc-wm->ourRobot[index].pos.loc;
//    //                //rc.fin_pos.dir=robot2ball.dir().radian();

//    //                rc.fin_pos.dir=robot2ball.dir().radian();

//    //                rc.fin_pos.loc=wm->ourRobot[index].pos.loc;//{0,0};//


//    //                if (wm->ball.vel.loc.length()>0.1)
//    //                {
//    //                    Vector2D goal;
//    //                    Vector2D Ballpos=wm->ball.pos.loc;
//    //                    Ball2C = new Line2D(Ballpos , wm->ball.vel.loc.dir().degree());
//    //                    Vector2D A,B;

//    //                    ballvel.setDir(wm->ball.vel.loc.dir().degree());


//    //                    if(fabs(ballvel.dir().degree()-last_ballvel.dir().degree())>10)
//    //                    {

//    //                        C1.assign(wm->ourRobot[index].pos.loc,ROBOT_RADIUS+500);

//    //                    }

//    //                    last_ballvel.setDir(ballvel.dir().degree());



//    //                    C1.intersection(*Ball2C,&A,&B);

//    //                    if( C1.HasIntersection(*Ball2C))
//    //                    {
//    //                        if((Ballpos-A).length2()>(Ballpos-B).length2())
//    //                        {
//    //                            goal=A;
//    //                        }

//    //                        else
//    //                        {
//    //                            goal=B;
//    //                        }

//    //                        rc.fin_pos.loc=goal;
//    //                        rc.fin_pos.dir=(wm->ball.vel.loc.dir().radian()+M_PI);


//    //                    }



//    //                }

//    //                ////////////////////////////////////////////////////////////////////////////////
//    //                //change decision
//    //                //Circle2D CD(wm->ourRobot[index].pos.loc,100);
//    //                if((wm->ourRobot[index].pos.loc-wm->ball.pos.loc).length()<300)
//    //                {
//    //                    kicker0=false;
//    //                    receiver0=true;

//    //                    kicker1=false;
//    //                    receiver1=false;

//    //                    kicker2=true;
//    //                    receiver2=false;
//    //                }

//    //                /////////////////////////////////////////////////////////////////////////////////


//    //            }



//    //            else if(!kicker2 && !receiver2)//kicker no!!!!  receiver no!!!>>>>....
//    //            {
//    //                Vector2D robot2ball=wm->ball.pos.loc-wm->ourRobot[index].pos.loc;
//    //                rc.fin_pos.dir=robot2ball.dir().radian();

//    //                rc.fin_pos.loc=wm->ourRobot[index].pos.loc;//{0,0};
//    //            }

//    //        }











































//    //    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*

//    //    //locating behind the ball...

//    //    Vector2D vec2goal;

//    //    Vector2D target=wm->ourRobot[1].pos.loc;//{2470,0};

//    //    vec2goal=target-wm->ball.pos.loc;

//    //    vec2goal.setLength(95);

//    //    rc.fin_pos.loc=wm->ball.pos.loc - vec2goal;

//    //    rc.fin_pos.dir=vec2goal.dir().radian();


//    //    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*
//    ////        Circle2D C(wm->ball.pos.loc,ROBOT_RADIUS+25);
//    ////        if(  C.contains(wm->ourRobot[0].pos.loc)   &&  ( (wm->ourRobot[0].pos.loc-target).length2()>(wm->ball.pos.loc-target).length2()  )
//    ////          )
//    ////        {
//    ////            rc.kickspeedx=3;
//    ////        }

//    //    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*

//    //    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////**
//    //// kicking
//    //    //real:
//    //    //    Vector2D A;
//    //    //    vec2goal.setLength(115);
//    //    //    A=wm->ball.pos.loc-vec2goal;
//    //    //    Circle2D C2(A,120);
//    //    //    Circle2D C(wm->ball.pos.loc,ROBOT_RADIUS+15);
//    //    //    if( wm->ball.isValid&&
//    //    //        C.contains(wm->ourRobot[0].pos.loc)&&
//    //    //        C2.contains(wm->ourRobot[0].pos.loc)
//    //    //      )
//    //    //    {
//    //    //        rc.kickspeedx=10;
//    //    //    }



//    //    //simulation:
//    //    Vector2D A;
//    //    vec2goal.setLength(107);
//    //    A=wm->ball.pos.loc-vec2goal;
//    //    Circle2D C2(A,120);
//    //    Circle2D C(wm->ball.pos.loc,ROBOT_RADIUS+20);
//    //    if( wm->ball.isValid&&
//    //            C.contains(wm->ourRobot[index].pos.loc)&&
//    //            C2.contains(wm->ourRobot[index].pos.loc)&&
//    //            (fabs(((wm->ourRobot[1].pos.loc-wm->ourRobot[index].pos.loc).dir().degree())-(vec2goal.dir().degree())<3))
//    //            )
//    //    {
//    //        rc.kickspeedx=6;
//    //    }







//    //    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////**

//    //    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////***

//    //    //    Vector2D A,A1,A2;

//    //    //    vec2goal.setLength(100);

//    //    //    A=wm->ball.pos.loc-vec2goal;

//    //    //    A1=A.rotatedVector(90);
//    //    //    A2=A.rotatedVector(-90);


//    //    //    qDebug()<<"A:"<<A.dir().degree()<<","<<A.length()<<"A1:"<<A1.dir().degree()<<","<<A1.length()<<"A2:"<<A2.dir().degree()<<","<<A2.length();
//    //    //    qDebug()<<"...............";


//    //    ////    Circle2D C(wm->ball.pos.loc,ROBOT_RADIUS+60000);
//    //    //    Circle2D C1(A1,300);
//    //    //    Circle2D C2(A2,300);

//    //    //    if(    (C1.contains(wm->ourRobot[0].pos.loc))  &&   (C2.contains(wm->ourRobot[0].pos.loc)) )//(C.contains(wm->ourRobot[0].pos.loc))) )
//    //    //    {
//    //    //        rc.kickspeedx=10;
//    //    //        qDebug()<<"shoot";
//    //    //    }


//    //    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////***


//    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//    //    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//    //    /// //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//    //    /// //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//    //    /// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//    ////    //following ball...


//    ////    if(wm->ball.isValid  &&  wm->ball.vel.loc.length()>0.15  )//&& (wm->ourRobot[0].pos.loc-wm->ball.pos.loc).length()>115 )
//    ////    {
//    ////        double delta=0;
//    ////        rc.maxSpeed=2.5;

//    ////        Vector2D Ballpos=wm->ball.pos.loc;
//    ////        Vector2D Ballvel=wm->ball.vel.loc;

//    ////        Ballvel.setLength(130);
//    ////        Vector2D A=Ballvel.rotatedVector(delta);

//    ////        Vector2D goal=Ballpos+A;

//    ////        if((wm->ourRobot[0].pos.loc-goal).length()<15)
//    ////        {
//    ////            rc.maxSpeed=wm->ball.vel.loc.length();
//    ////        }

//    ////        //qDebug()<<"V:"<<B.length();




//    ////        rc.fin_pos.loc=goal;
//    ////        rc.fin_pos.dir=(wm->ball.pos.loc-wm->ourRobot[0].pos.loc).dir().radian();

//    ////    }

//    //////    qDebug()<<"ball angel:"<<B.dir().degree()<<"final angel"<<B1.dir().degree();
//    /////
//    /////
//    ///// ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//    //    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//    //    /// //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//    //    /// //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//    //    /// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//    ////    //RecievingPass


//    ////    Vector2D robot2ball=wm->ball.pos.loc-wm->ourRobot[0].pos.loc;
//    ////    rc.fin_pos.dir=robot2ball.dir().radian();

//    ////    rc.fin_pos.loc={2470,0};


//    ////    if (wm->ball.vel.loc.length()>0.1)
//    ////    {
//    ////        Vector2D goal;
//    ////        Vector2D Ballpos=wm->ball.pos.loc;
//    ////        Ball2C = new Line2D(Ballpos , wm->ball.vel.loc.dir().degree());
//    ////        Vector2D A,B;

//    ////        ballvel.setDir(wm->ball.vel.loc.dir().degree());


//    ////        if(fabs(ballvel.dir().degree()-last_ballvel.dir().degree())>10)
//    ////        {

//    ////            C.assign(wm->ourRobot[0].pos.loc,ROBOT_RADIUS+300);

//    ////        }

//    ////        last_ballvel.setDir(ballvel.dir().degree());



//    ////        C.intersection(*Ball2C,&A,&B);

//    ////        if( C.HasIntersection(*Ball2C))
//    ////        {
//    ////            if((Ballpos-A).length2()>(Ballpos-B).length2())
//    ////            {
//    ////                goal=B;
//    ////            }

//    ////            else
//    ////            {
//    ////                goal=A;
//    ////            }

//    ////            rc.fin_pos.loc=goal;
//    ////            rc.fin_pos.dir=(wm->ball.vel.loc.dir().radian()+M_PI);//tttarget.dir().radian();//


//    ////        }



//    ////    }
//    //  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//    //    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//    //    /// //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//    //    /// ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//    //    ///
//    //    ///

//    ////    //sth like one touch...


//    //////    Vector2D vec2goal;

//    ////    target={2480,2790};//wm->ourRobot[1].pos.loc;//

//    ////    vec2goal=target-wm->ball.pos.loc;

//    ////    vec2goal.setLength(95);










//    ////    Vector2D robot2ball=wm->ball.pos.loc-wm->ourRobot[0].pos.loc;
//    ////    rc.fin_pos.dir=robot2ball.dir().radian();

//    ////    rc.fin_pos.loc={2470,0};

//    ////    target={1500,0};


//    ////    if (wm->ball.vel.loc.length()>0.1)
//    ////    {
//    ////        Vector2D goal;
//    ////        Vector2D Ballpos=wm->ball.pos.loc;
//    ////        Ball2C = new Line2D(Ballpos , wm->ball.vel.loc.dir().degree());
//    ////        Vector2D A,B;

//    ////        ballvel.setDir(wm->ball.vel.loc.dir().degree());


//    ////        if(fabs(ballvel.dir().degree()-last_ballvel.dir().degree())>15)
//    ////        {

//    ////            C.assign(wm->ourRobot[0].pos.loc,ROBOT_RADIUS+200);

//    ////        }

//    ////        last_ballvel.setDir(ballvel.dir().degree());



//    ////        C.intersection(*Ball2C,&A,&B);

//    ////        if( C.HasIntersection(*Ball2C))
//    ////        {
//    ////            if((target-A).length2()>(target-B).length2())
//    ////            {
//    ////                goal=A;
//    ////            }

//    ////            else
//    ////            {
//    ////                goal=B;
//    ////            }


//    ////            rc.fin_pos.loc=goal - vec2goal;

//    ////            rc.fin_pos.dir=vec2goal.dir().radian();


//    ////        }



//    ////    }



//}




void SkillKick::setTarget(const Vector2D &Target)
{
    _Target=Target;
}

void SkillKick::setKickType(bool isShoot)
{
    this->isShoot = isShoot;
}
