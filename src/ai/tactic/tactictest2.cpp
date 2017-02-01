#include "tactictest2.h"

Vector2D* TacticTest2::getFinalPos()
{
    return &finalPos;
}

void TacticTest2::setFinalPos(Vector2D value)
{
    finalPos = value;
}

int TacticTest2::getBallVelocity() const
{
    return ballVelocity;
}

void TacticTest2::setBallVelocity(int value)
{
    ballVelocity = value;
}
TacticTest2::TacticTest2(WorldModel *worldmodel, QObject *parent) :
    Tactic("TacticTest2", worldmodel, parent)
{
}

RobotCommand TacticTest2::getCommand()
{
    RobotCommand rc;
    if(!wm->ourRobot[id].isValid) return rc;
    Vector2D p2 = Field::ourGoalCenter;
    Vector2D p1 = wm->ball.pos.loc;
    Segment2D ballViewMidSeg(p2,p1);
    //goal keeper
    if(id == wm->ref_goalie_our){
    if(wm->ball.vel.loc.r() < 0.1){
        rc.fin_pos.loc = Field::ourGoalCenter;
        rc.fin_pos.dir = ballViewMidSeg.direction().radian();
        rc.maxSpeed = 2;
        return rc;
    }
    rc.useNav = true;
    rc.maxSpeed = 3;
    Ray2D seg(wm->ball.pos.loc,wm->ball.vel.loc.dir());
    rc.fin_pos.loc = seg.intersection(Field::leftLine);
    //    rc.fin_pos.dir = seg.direction().deg2rad(seg.direction().degree());
    if((rc.fin_pos.loc.y < Field::ourGoalPost_L.y+5) && (rc.fin_pos.loc.y > Field::ourGoalPost_R.y-5) && (rc.fin_pos.loc.x = Field::ourGoalPost_L.x))
        return rc;
    else
        rc.fin_pos.loc = Field::ourGoalCenter;
        rc.maxSpeed = 2;
        return rc;
    }
    double ang = 7;
    AngleDeg zaveEkhtelaf(30);
//    Vector2D p2 = Field::ourGoalPost_L;
//    Vector2D p3 = Field::ourGoalPost_R;

    /*
    Segment2D SegBallView1(wm->ball.pos.loc,Field::ourDefPost_R);
    Segment2D SegBallView2(wm->ball.pos.loc,Field::ourDefPost_L);*/
//    ballViewMidSeg.direction().;
/*    Segment2D ballViewBotLine(p1,p3);
    Segment2D ballViewTopLine(p1,p2)*/;
    if(id == wm->kn->ActiveAgents()[1]){
        Segment2D* seg;
        if(wm->ball.vel.loc.r() > 0.1){
            seg = new Segment2D(p2,Field::goalCircle_R + 200,*(new AngleDeg(ballViewMidSeg.direction().degree() + 1)));
            rc.useNav = true;
            rc.maxSpeed = 6;

        }
        else{
            seg = new Segment2D(p2,Field::goalCircle_R + 200,*(new AngleDeg(ballViewMidSeg.direction().degree() + ang)));
            rc.useNav = true;
            rc.maxSpeed = 4;
        }
        rc.fin_pos.loc = seg->terminal();
        rc.fin_pos.dir = seg->direction().radian();
        rc.maxSpeed = 4;
    }
    if(id == wm->kn->ActiveAgents()[2]){
        Segment2D* seg;
        if(wm->ball.vel.loc.r() > 0.1){
            seg = new Segment2D(p2,Field::goalCircle_R + 200,*(new AngleDeg(ballViewMidSeg.direction().degree() - 1)));
            rc.useNav = true;
            rc.maxSpeed = 6;
        }
        else{
            seg = new Segment2D(p2,Field::goalCircle_R + 200,*(new AngleDeg(ballViewMidSeg.direction().degree()- ang)));
            rc.useNav = true;
            rc.maxSpeed = 4;
        }
        rc.fin_pos.loc = seg->terminal();
        rc.fin_pos.dir = seg->direction().radian();
    }
    if(wm->kn->ActiveAgents().size() > 3){
        if(id == wm->kn->ActiveAgents()[3]){
            Segment2D* seg;
            if(wm->ball.vel.loc.r() > 0.1){
                Segment2D seg2(p2,wm->ball.pos.loc);
                if(seg2.length() > Field::goalCircle_R + 300){
                    seg = new Segment2D(p2,seg2.length() - 500,*(new AngleDeg(ballViewMidSeg.direction().degree())));
                }
                else{
                    seg = new Segment2D(p2,Field::goalCircle_R + 300,*(new AngleDeg(ballViewMidSeg.direction().degree())));
                }
                rc.useNav = true;
                rc.maxSpeed = 6;

            }
            else{
                Segment2D seg2(p2,wm->ball.pos.loc);
                if(seg2.length() > Field::goalCircle_R + 300){
                    seg = new Segment2D(p2,seg2.length() - 500,*(new AngleDeg(ballViewMidSeg.direction().degree())));
                }
                else{
                    seg = new Segment2D(p2,Field::goalCircle_R + 300,*(new AngleDeg(ballViewMidSeg.direction().degree())));
                }
                rc.useNav = true;
                rc.maxSpeed = 4;
            }
            rc.fin_pos.loc = seg->terminal();
            rc.fin_pos.dir = seg->direction().radian();
            rc.maxSpeed = 4;
        }
    }
    if(wm->kn->ActiveAgents().size() == 5){
        if(id == wm->kn->ActiveAgents()[4]){
            Segment2D* seg;
            if(wm->ball.vel.loc.r() > 0.1){
                Segment2D seg2(p2,wm->ball.pos.loc);
                if(seg2.length() > Field::goalCircle_R + 500){
                    Segment2D seg5(wm->ball.pos.loc,p2);
                    Segment2D seg4(wm->ball.pos.loc , 500 , seg5.direction() - zaveEkhtelaf);
                    rc.fin_pos.loc = seg4.terminal();
                    Segment2D seg3(seg4.terminal(),wm->ball.pos.loc);
                    rc.fin_pos.dir = seg3.direction().radian();
                }
                else{
                    seg = new Segment2D(p2,Field::goalCircle_R + 300,*(new AngleDeg(ballViewMidSeg.direction().degree() - 2*ang)));
                    rc.fin_pos.loc = seg->terminal();
                    rc.fin_pos.dir = seg->direction().radian();
                }
                rc.useNav = true;
                rc.maxSpeed = 6;

            }
            else{
                Segment2D seg2(p2,wm->ball.pos.loc);
                if(seg2.length() > Field::goalCircle_R + 500){
                    Segment2D seg5(wm->ball.pos.loc,p2);
                    Segment2D seg4(wm->ball.pos.loc , 500 , seg5.direction() - zaveEkhtelaf);
                    rc.fin_pos.loc = seg4.terminal();
                    Segment2D seg3(seg4.terminal(),wm->ball.pos.loc);
                    rc.fin_pos.dir = seg3.direction().radian();
                }
                else{
                    seg = new Segment2D(p2,Field::goalCircle_R + 300,*(new AngleDeg(ballViewMidSeg.direction().degree() - 2*ang)));
                    rc.fin_pos.loc = seg->terminal();
                    rc.fin_pos.dir = seg->direction().radian();
                }
                rc.useNav = true;
                rc.maxSpeed = 4;
            }
            rc.maxSpeed = 4;
        }
    }
    if(wm->kn->ActiveAgents().size() == 6){
        Vector2D* j1 = new Vector2D();
        Vector2D* j2 = new Vector2D();
        if((id == wm->kn->ActiveAgents()[4]) || (id == wm->kn->ActiveAgents()[5])){
            Segment2D* seg;
            if(wm->ball.vel.loc.r() > 0.1){
                Segment2D seg2(p2,wm->ball.pos.loc);
                if(seg2.length() > Field::goalCircle_R + 500){
                    Segment2D seg5(wm->ball.pos.loc,p2);
                    Segment2D seg4(wm->ball.pos.loc , 500 , seg5.direction() - zaveEkhtelaf);
                    rc.fin_pos.loc = seg4.terminal();
                    Segment2D seg3(seg4.terminal(),wm->ball.pos.loc);
                    rc.fin_pos.dir = seg3.direction().radian();
                    /*
                    Circle2D cir1(p2,Field::goalCircle_R + 600 + (((seg2.length() - Field::goalCircle_R - 500)/3)*2));
                    Circle2D cir2(wm->ball.pos.loc,200 + ((seg2.length() - Field::goalCircle_R - 500)/3));
                    cir1.intersection(cir2,j1,j2);
                    std::cout << "j21 x" << j2->x << std::endl;
                    rc.fin_pos.loc = *j1;
                    Segment2D seg3(*j1,wm->ball.pos.loc);
                    rc.fin_pos.dir = seg3.direction().radian();*/
                }
                else{
                    seg = new Segment2D(p2,Field::goalCircle_R + 300,*(new AngleDeg(ballViewMidSeg.direction().degree() + 2*ang)));
                    rc.fin_pos.loc = seg->terminal();
                    rc.fin_pos.dir = seg->direction().radian();
                }
                rc.useNav = true;
                rc.maxSpeed = 6;

            }
            else{
                Segment2D seg2(p2,wm->ball.pos.loc);
                if(seg2.length() > Field::goalCircle_R + 500){
                    Segment2D seg5(wm->ball.pos.loc,p2);
                    Segment2D seg4(wm->ball.pos.loc , 500 , seg5.direction() - zaveEkhtelaf);
                    rc.fin_pos.loc = seg4.terminal();
                    Segment2D seg3(seg4.terminal(),wm->ball.pos.loc);
                    rc.fin_pos.dir = seg3.direction().radian();
                    /*
                    Circle2D cir1(p2,Field::goalCircle_R + 600 + (((seg2.length() - Field::goalCircle_R - 500)/3)*2));
                    Circle2D cir2(wm->ball.pos.loc,200 + ((seg2.length() - Field::goalCircle_R - 500)/3));
                    cir1.intersection(cir2,j1,j2);
                    std::cout << "j22 x" << j2->x << std::endl;
                    rc.fin_pos.loc = *j1;
                    Segment2D seg3(*j1,wm->ball.pos.loc);
                    rc.fin_pos.dir = seg3.direction().radian();*/
                }
                else{
                    seg = new Segment2D(p2,Field::goalCircle_R + 300,*(new AngleDeg(ballViewMidSeg.direction().degree() + 2*ang)));
                    rc.fin_pos.loc = seg->terminal();
                    rc.fin_pos.dir = seg->direction().radian();
                }
                rc.useNav = true;
                rc.maxSpeed = 4;
            }
            rc.maxSpeed = 4;
        }
        if(id == wm->kn->ActiveAgents()[5]){
            Segment2D* seg;
            if(wm->ball.vel.loc.r() > 0.1){
                Segment2D seg2(p2,wm->ball.pos.loc);
                if(seg2.length() > Field::goalCircle_R + 500){
                    Segment2D seg5(wm->ball.pos.loc,p2);
                    Segment2D seg4(wm->ball.pos.loc , 500 , seg5.direction() + zaveEkhtelaf);
                    rc.fin_pos.loc = seg4.terminal();
                    Segment2D seg3(seg4.terminal(),wm->ball.pos.loc);
                    rc.fin_pos.dir = seg3.direction().radian();
                    //                    std::cout << "x : " << j2->x << std::endl;
//                    std::cout << "y : " << j2->y << std::endl;
//                    rc.fin_pos.loc = *j2;
//                    std::cout << "1x : " << j2->x << std::endl;
//                    std::cout << "1y : " << j2->y << std::endl;
////                    std::cout << "fasele do dayere" << cir1.center().dist(cir2.center()) << "   jame shoaha" << (cir1.radius() + cir2.radius()) << std::endl;
//                    Segment2D seg3(*j2,wm->ball.pos.loc);
//                    rc.fin_pos.dir = seg3.direction().radian();
                }
                else{
                    seg = new Segment2D(p2,Field::goalCircle_R + 300,*(new AngleDeg(ballViewMidSeg.direction().degree() - 2*ang)));
                    rc.fin_pos.loc = seg->terminal();
                    rc.fin_pos.dir = seg->direction().radian();
                }
                rc.useNav = true;
                rc.maxSpeed = 6;

            }
            else{
                Segment2D seg2(p2,wm->ball.pos.loc);
                if(seg2.length() > Field::goalCircle_R + 500){
                    Segment2D seg5(wm->ball.pos.loc,p2);
                    Segment2D seg4(wm->ball.pos.loc , 500 , seg5.direction() + zaveEkhtelaf);
                    rc.fin_pos.loc = seg4.terminal();
                    Segment2D seg3(seg4.terminal(),wm->ball.pos.loc);
                    rc.fin_pos.dir = seg3.direction().radian();
                    //                    std::cout << "2x : " << j2->x << std::endl;
//                    std::cout << "2y : " << j2->y << std::endl;
////                    std::cout << "fasele do dayere" << cir1.center().dist(cir2.center()) << "   jame shoaha" << (cir1.radius() + cir2.radius()) << std::endl;
//                    rc.fin_pos.loc = *j2;
//                    Segment2D seg3(*j2,wm->ball.pos.loc);
//                    rc.fin_pos.dir = seg3.direction().radian();
                }
                else{
                    seg = new Segment2D(p2,Field::goalCircle_R + 300,*(new AngleDeg(ballViewMidSeg.direction().degree() - 2*ang)));
                    rc.fin_pos.loc = seg->terminal();
                    rc.fin_pos.dir = seg->direction().radian();
                }
                rc.useNav = true;
                rc.maxSpeed = 4;
            }
            rc.maxSpeed = 4;
        }
    }
















    qDebug() << ballViewMidSeg.direction().radian();
    if((ballViewMidSeg.direction().radian() > 1.1)&& (id == 4) && (wm->kn->ActiveAgents().size() == 6)){
        Segment2D* seg;
        if(wm->ball.vel.loc.r() > 0.1){
            Segment2D seg2(p2,wm->ball.pos.loc);
            if(seg2.length() > Field::goalCircle_R + 500){
                Segment2D seg5(wm->ball.pos.loc,p2);
                Segment2D seg4(wm->ball.pos.loc , 500 , seg5.direction() + zaveEkhtelaf + zaveEkhtelaf);
                rc.fin_pos.loc = seg4.terminal();
                Segment2D seg3(seg4.terminal(),wm->ball.pos.loc);
                rc.fin_pos.dir = seg3.direction().radian();
                //                    std::cout << "x : " << j2->x << std::endl;
//                    std::cout << "y : " << j2->y << std::endl;
//                    rc.fin_pos.loc = *j2;
//                    std::cout << "1x : " << j2->x << std::endl;
//                    std::cout << "1y : " << j2->y << std::endl;
////                    std::cout << "fasele do dayere" << cir1.center().dist(cir2.center()) << "   jame shoaha" << (cir1.radius() + cir2.radius()) << std::endl;
//                    Segment2D seg3(*j2,wm->ball.pos.loc);
//                    rc.fin_pos.dir = seg3.direction().radian();
            }
            else{
                seg = new Segment2D(p2,Field::goalCircle_R + 300,*(new AngleDeg(ballViewMidSeg.direction().degree() + 2*ang)));
                rc.fin_pos.loc = seg->terminal();
                rc.fin_pos.dir = seg->direction().radian();
            }
            rc.useNav = true;
            rc.maxSpeed = 6;

        }
        else{
            Segment2D seg2(p2,wm->ball.pos.loc);
            if(seg2.length() > Field::goalCircle_R + 500){
                Segment2D seg5(wm->ball.pos.loc,p2);
                Segment2D seg4(wm->ball.pos.loc , 500 , seg5.direction() + zaveEkhtelaf + zaveEkhtelaf);
                rc.fin_pos.loc = seg4.terminal();
                Segment2D seg3(seg4.terminal(),wm->ball.pos.loc);
                rc.fin_pos.dir = seg3.direction().radian();
                //                    std::cout << "2x : " << j2->x << std::endl;
//                    std::cout << "2y : " << j2->y << std::endl;
////                    std::cout << "fasele do dayere" << cir1.center().dist(cir2.center()) << "   jame shoaha" << (cir1.radius() + cir2.radius()) << std::endl;
//                    rc.fin_pos.loc = *j2;
//                    Segment2D seg3(*j2,wm->ball.pos.loc);
//                    rc.fin_pos.dir = seg3.direction().radian();
            }
            else{
                seg = new Segment2D(p2,Field::goalCircle_R + 300,*(new AngleDeg(ballViewMidSeg.direction().degree() + 2*ang)));
                rc.fin_pos.loc = seg->terminal();
                rc.fin_pos.dir = seg->direction().radian();
            }
            rc.useNav = true;
            rc.maxSpeed = 4;
        }
        rc.maxSpeed = 4;
    }






















    if((ballViewMidSeg.direction().radian() < -1.1)&& (id == 5) && (wm->kn->ActiveAgents().size() == 6)){
        Segment2D* seg;
        if(wm->ball.vel.loc.r() > 0.1){
            Segment2D seg2(p2,wm->ball.pos.loc);
            if(seg2.length() > Field::goalCircle_R + 500){
                Segment2D seg5(wm->ball.pos.loc,p2);
                Segment2D seg4(wm->ball.pos.loc , 500 , seg5.direction() - zaveEkhtelaf - zaveEkhtelaf);
                rc.fin_pos.loc = seg4.terminal();
                Segment2D seg3(seg4.terminal(),wm->ball.pos.loc);
                rc.fin_pos.dir = seg3.direction().radian();
                //                    std::cout << "x : " << j2->x << std::endl;
//                    std::cout << "y : " << j2->y << std::endl;
//                    rc.fin_pos.loc = *j2;
//                    std::cout << "1x : " << j2->x << std::endl;
//                    std::cout << "1y : " << j2->y << std::endl;
////                    std::cout << "fasele do dayere" << cir1.center().dist(cir2.center()) << "   jame shoaha" << (cir1.radius() + cir2.radius()) << std::endl;
//                    Segment2D seg3(*j2,wm->ball.pos.loc);
//                    rc.fin_pos.dir = seg3.direction().radian();
            }
            else{
                seg = new Segment2D(p2,Field::goalCircle_R + 300,*(new AngleDeg(ballViewMidSeg.direction().degree() - 2*ang)));
                rc.fin_pos.loc = seg->terminal();
                rc.fin_pos.dir = seg->direction().radian();
            }
            rc.useNav = true;
            rc.maxSpeed = 6;

        }
        else{
            Segment2D seg2(p2,wm->ball.pos.loc);
            if(seg2.length() > Field::goalCircle_R + 500){
                Segment2D seg5(wm->ball.pos.loc,p2);
                Segment2D seg4(wm->ball.pos.loc , 500 , seg5.direction() - zaveEkhtelaf - zaveEkhtelaf);
                rc.fin_pos.loc = seg4.terminal();
                Segment2D seg3(seg4.terminal(),wm->ball.pos.loc);
                rc.fin_pos.dir = seg3.direction().radian();
                //                    std::cout << "2x : " << j2->x << std::endl;
//                    std::cout << "2y : " << j2->y << std::endl;
////                    std::cout << "fasele do dayere" << cir1.center().dist(cir2.center()) << "   jame shoaha" << (cir1.radius() + cir2.radius()) << std::endl;
//                    rc.fin_pos.loc = *j2;
//                    Segment2D seg3(*j2,wm->ball.pos.loc);
//                    rc.fin_pos.dir = seg3.direction().radian();
            }
            else{
                seg = new Segment2D(p2,Field::goalCircle_R + 300,*(new AngleDeg(ballViewMidSeg.direction().degree() - 2*ang)));
                rc.fin_pos.loc = seg->terminal();
                rc.fin_pos.dir = seg->direction().radian();
            }
            rc.useNav = true;
            rc.maxSpeed = 4;
        }
        rc.maxSpeed = 4;
    }
//    Vector2D* p4;
//    Segment2D* S1;
//    if(ballViewBotLine.length() < ballViewTopLine.length()){
//        AngleDeg A1(ballViewMidSeg.direction().degree() + 90);
//        Line2D l1(p3,A1);
//        p4 = &ballViewBotLine.intersection(l1);
//        S1 = new Segment2D(p3,&p4);
//        int ScaleNum = (S1->length()/(2*robotSize));
//        AngleDeg A2(-ballViewBotLine.direction().degree());
//        Segment2D MainTriBot(p1,ScaleNum*ballViewBotLine,A2);

<<<<<<< HEAD
//    }
//    else{
//        AngleDeg A1(ballViewMidSeg.direction().degree() + 90);
//        Line2D l1(p2,A1);
//        p4 = &ballViewBotLine.intersection(l1);
//        S1 = new Segment2D(p2,&p4);
//        int ScaleNum = (S1->length()/(2*robotSize));
//        AngleDeg A2(-ballViewTopLine.direction().degree());
//        Segment2D MainTriTop(p1,ScaleNum*ballViewBotLine,A2);
//    }
=======
    if(id==5){ //3
        Circle2D ballArea(wm->ball.pos.loc,300);
        Circle2D ballShoutArea(wm->ball.pos.loc,ROBOT_RADIUS-40);
        //Line2D shutLine(wm->ball.pos.loc,Field::ourGoalCenter);
        Line2D shutLine(wm->ball.pos.loc,Field::ourGoalCenter);
        Vector2D f1,f2,r;
        Vector2D s1,s2,rf;
        ballArea.intersection(shutLine,&f1,&f2);
        if(Field::ourGoalCenter.dist(f1)>Field::ourGoalCenter.dist(f2)){
            r=f1;
        }
        else{
            r=f2;
        }
        if(r.dist(wm->ourRobot[id].pos.loc)>200 && flag==0){
            rc.fin_pos.loc=r;
            wm->debug_pos.append(r);
            rc.maxSpeed=2;
            rc.useNav=true;
            rc.isBallObs=true;
            qDebug()<<"ba navigatione roshan mire poshtesh";
//            //flag1=0;

        }
        else{
            qDebug()<<"reside poshtesh";
            rc.fin_pos.loc=r;
            rc.maxSpeed=1;
            rc.useNav=true;
            rc.isBallObs=true;
            //if(((wm->ourRobot[id].pos.dir)-(wm->ball.pos.loc-Field::ourGoalCenter).dir().radian())<0.9){
                qDebug()<<"zavie ro ok karde flag ro 1 mikone ";
                flag=1;
            //}
        }
        ballShoutArea.intersection(shutLine,&s1,&s2);
        if(Field::ourGoalCenter.dist(s1)>Field::ourGoalCenter.dist(s2)){
            rf=s1;
        }
        else{
            rf=s2;
        }
        if(flag==1){
            qDebug()<<"ba sorate yek az posht be tup nazdik mishe";
            rc.maxSpeed=0.5;
////            if(wm->ourRobot[id].pos.loc.dist(wm->ball.pos.loc)>400){
////                flag=0;
////            }
            rc.fin_pos.loc=rf;
            wm->debug_pos.append(rf);
            rc.useNav=false;
        }
        if(wm->ourRobot[id].pos.loc.dist(rf)<ROBOT_RADIUS-40){
            qDebug()<<"be fasele shut reside";
            rc.maxSpeed=0;
            //if(wm->ball.isValid && ((wm->ourRobot[id].pos.dir)-(wm->ball.pos.loc-Field::ourGoalCenter).dir().radian())<1){
                qDebug()<<"dasture shut !";
                rc.kickspeedx=100;
            //}
            rc.useNav=false;
            //rc.isBallObs=false;
            //rc.isKickObs=true;
//            flag=0;

        }
        rc.fin_pos.dir=(Field::ourGoalCenter-wm->ball.pos.loc).dir().radian();
    }
    if(id==4){
        //way.append(wm->ball.pos.dir);
        Position goaliePos;
        if(wm->ball.vel.loc.length()<0.3){
                int kickerId;
                QList <int> opp = wm->kn->findNearestTo(wm->ball.pos.loc);
                for(int i=0;i<opp.length();i++){
                    if(opp.at(i)==4){
                        opp.removeAt(i);
                    }
                }
                if(opp.length()!=0){
                    kickerId=opp.at(0);
                    Line2D shot(wm->ball.pos.loc,wm->ourRobot[kickerId].pos.loc);
                    Segment2D gLine(Field::ourGoalPost_L,Field::ourGoalPost_R);
                    goaliePos.loc=gLine.intersection(shot);
                    if(gLine.contains(goaliePos.loc)==false){
                        goaliePos.loc=Field::ourGoalCenter;
                    }
                    goaliePos.dir=(wm->ball.pos.loc-goaliePos.loc).dir().radian();
                 }
                else{
                    goaliePos.loc=Field::ourGoalCenter;
                }
                    //
        }
        else{
            qDebug()<<"else !!!!!";
                Vector2D f;
                Vector2D a;
                Vector2D sum;
                Vector2D avg;
                sum.x=0;
                sum.y=0;
                f.x=wm->ball.pos.loc.x+wm->ball.vel.loc.x;
                f.y=wm->ball.pos.loc.y+wm->ball.vel.loc.y;

                //avg.x=way.at(0).x+way.at(1).x+way.at(2).x;
                //avg.y=way.at(0).y+way.at(1).y+way.at(2).y;
                Line2D shot(wm->ball.pos.loc,f);
                Vector2D GL,GR;
                GL=Field::ourGoalPost_L;
                GR=Field::ourGoalPost_R;
                if(Field::ourGoalPost_L.y>0){
                    GL.y+=100;
                }
                else{
                    GL.y-=100;
                }
                if(Field::ourGoalPost_R.y>0){
                    GR.y+=100;
                }
                else{
                    GR.y-=100;
                }
                Segment2D gLine(GL,GR);
                a=gLine.intersection(shot);
                if(gLine.contains(a)){
                    goaliePos.loc=a;
                }
                else{
                    goaliePos.loc=Field::ourGoalCenter;
                }
//                if(goaliePos.loc.dist(Field::ourGoalCenter)<150){
                if(wm->ball.pos.loc.dist(Field::ourGoalCenter)>450){
                    if(wm->ourRobot[id].pos.loc.dist(goaliePos.loc)>100){
                            if(goaliePos.loc.y>Field::ourGoalCenter.y){
                                goaliePos.loc.y+=50;
                            }
                            if(goaliePos.loc.y<Field::ourGoalCenter.y){
                                goaliePos.loc.y-=50;
                            }
                    }
                }
//                }

        }
        goaliePos.dir=(wm->ball.pos.loc-goaliePos.loc).dir().radian();
        rc.fin_pos.loc=goaliePos.loc;
        rc.fin_pos.dir=goaliePos.dir;
        wm->debug_pos.append(goaliePos.loc);
        rc.useNav=false;
        rc.maxSpeed=4;
    }

<<<<<<< HEAD
    //wm->debug_pos.append(Field::ourGoalCenter);
    //wm->debug_pos.append(Field::ourGoalPost_L);
    //wm->debug_pos.append(Field::ourGoalPost_R);
>>>>>>> d766c95da96dc8ee70e0992aefe4e0a62d783e28
=======
    if(id==5){ //3
        Circle2D ballArea(wm->ball.pos.loc,300);
        Circle2D ballShoutArea(wm->ball.pos.loc,ROBOT_RADIUS-40);
        //Line2D shutLine(wm->ball.pos.loc,Field::ourGoalCenter);
        Line2D shutLine(wm->ball.pos.loc,Field::ourGoalCenter);
        Vector2D f1,f2,r;
        Vector2D s1,s2,rf;
        ballArea.intersection(shutLine,&f1,&f2);
        if(Field::ourGoalCenter.dist(f1)>Field::ourGoalCenter.dist(f2)){
            r=f1;
        }
        else{
            r=f2;
        }
        if(r.dist(wm->ourRobot[id].pos.loc)>200 && flag==0){
            rc.fin_pos.loc=r;
            wm->debug_pos.append(r);
            rc.maxSpeed=2;
            rc.useNav=true;
            rc.isBallObs=true;
            qDebug()<<"ba navigatione roshan mire poshtesh";
//            //flag1=0;

        }
        else{
            qDebug()<<"reside poshtesh";
            rc.fin_pos.loc=r;
            rc.maxSpeed=1;
            rc.useNav=true;
            rc.isBallObs=true;
            //if(((wm->ourRobot[id].pos.dir)-(wm->ball.pos.loc-Field::ourGoalCenter).dir().radian())<0.9){
                qDebug()<<"zavie ro ok karde flag ro 1 mikone ";
                flag=1;
            //}
        }
        ballShoutArea.intersection(shutLine,&s1,&s2);
        if(Field::ourGoalCenter.dist(s1)>Field::ourGoalCenter.dist(s2)){
            rf=s1;
        }
        else{
            rf=s2;
        }
        if(flag==1){
            qDebug()<<"ba sorate yek az posht be tup nazdik mishe";
            rc.maxSpeed=0.5;
////            if(wm->ourRobot[id].pos.loc.dist(wm->ball.pos.loc)>400){
////                flag=0;
////            }
            rc.fin_pos.loc=rf;
            wm->debug_pos.append(rf);
            rc.useNav=false;
        }
        if(wm->ourRobot[id].pos.loc.dist(rf)<ROBOT_RADIUS-40){
            qDebug()<<"be fasele shut reside";
            rc.maxSpeed=0;
            //if(wm->ball.isValid && ((wm->ourRobot[id].pos.dir)-(wm->ball.pos.loc-Field::ourGoalCenter).dir().radian())<1){
                qDebug()<<"dasture shut !";
                rc.kickspeedx=100;
            //}
            rc.useNav=false;
            //rc.isBallObs=false;
            //rc.isKickObs=true;
//            flag=0;

        }
        rc.fin_pos.dir=(Field::ourGoalCenter-wm->ball.pos.loc).dir().radian();
    }
    if(id==4){
        //way.append(wm->ball.pos.dir);
        Position goaliePos;
        if(wm->ball.vel.loc.length()<0.3){
                int kickerId;
                QList <int> opp = wm->kn->findNearestTo(wm->ball.pos.loc);
                for(int i=0;i<opp.length();i++){
                    if(opp.at(i)==4){
                        opp.removeAt(i);
                    }
                }
                if(opp.length()!=0){
                    kickerId=opp.at(0);
                    Line2D shot(wm->ball.pos.loc,wm->ourRobot[kickerId].pos.loc);
                    Segment2D gLine(Field::ourGoalPost_L,Field::ourGoalPost_R);
                    goaliePos.loc=gLine.intersection(shot);
                    if(gLine.contains(goaliePos.loc)==false){
                        goaliePos.loc=Field::ourGoalCenter;
                    }
                    goaliePos.dir=(wm->ball.pos.loc-goaliePos.loc).dir().radian();
                 }
                else{
                    goaliePos.loc=Field::ourGoalCenter;
                }
                    //
        }
        else{
            qDebug()<<"else !!!!!";
                Vector2D f;
                Vector2D a;
                Vector2D sum;
                Vector2D avg;
                sum.x=0;
                sum.y=0;
                f.x=wm->ball.pos.loc.x+wm->ball.vel.loc.x;
                f.y=wm->ball.pos.loc.y+wm->ball.vel.loc.y;

                //avg.x=way.at(0).x+way.at(1).x+way.at(2).x;
                //avg.y=way.at(0).y+way.at(1).y+way.at(2).y;
                Line2D shot(wm->ball.pos.loc,f);
                Vector2D GL,GR;
                GL=Field::ourGoalPost_L;
                GR=Field::ourGoalPost_R;
                if(Field::ourGoalPost_L.y>0){
                    GL.y+=100;
                }
                else{
                    GL.y-=100;
                }
                if(Field::ourGoalPost_R.y>0){
                    GR.y+=100;
                }
                else{
                    GR.y-=100;
                }
                Segment2D gLine(GL,GR);
                a=gLine.intersection(shot);
                if(gLine.contains(a)){
                    goaliePos.loc=a;
                }
                else{
                    goaliePos.loc=Field::ourGoalCenter;
                }
//                if(goaliePos.loc.dist(Field::ourGoalCenter)<150){
                if(wm->ball.pos.loc.dist(Field::ourGoalCenter)>450){
                    if(wm->ourRobot[id].pos.loc.dist(goaliePos.loc)>100){
                            if(goaliePos.loc.y>Field::ourGoalCenter.y){
                                goaliePos.loc.y+=50;
                            }
                            if(goaliePos.loc.y<Field::ourGoalCenter.y){
                                goaliePos.loc.y-=50;
                            }
                    }
                }
//                }

        }
        goaliePos.dir=(wm->ball.pos.loc-goaliePos.loc).dir().radian();
        rc.fin_pos.loc=goaliePos.loc;
        rc.fin_pos.dir=goaliePos.dir;
        wm->debug_pos.append(goaliePos.loc);
        rc.useNav=false;
        rc.maxSpeed=4;
    }

    //wm->debug_pos.append(Field::ourGoalCenter);
    //wm->debug_pos.append(Field::ourGoalPost_L);
    //wm->debug_pos.append(Field::ourGoalPost_R);
    rc.fin_pos.loc = Vector2D(1300,100);
    rc.maxSpeed = 2;
    rc.useNav = true;
>>>>>>> 4bde963eede2897a0748e0221474ee6c1450efde
    return rc;
    //baraye rahati dayere tarif mikonim.
}
