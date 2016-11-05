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
    return rc;
    //baraye rahati dayere tarif mikonim.
}
