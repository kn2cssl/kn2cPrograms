#include "tactictest.h"
#include <iostream>
TacticTest::TacticTest(WorldModel *worldmodel, QObject *parent) :
    Tactic("TacticTest", worldmodel, parent)
{
}
bool TacticTest::kicked = false;
//namespace {
//bool firstPos1 = false;
//bool active = false;
//bool firstPos2 = false;
//RobotCommand rc0;
//RobotCommand rc1;
//}

RobotCommand TacticTest::getCommand()
{
    RobotCommand rc;
    if(!wm->ourRobot[id].isValid)
        return rc;
    rc.fin_pos.loc.x = -3000;
    rc.fin_pos.loc.y = 0;
    rc.useNav = true;
    rc.maxSpeed = 3;
    qDebug() << wm->ourRobot[2].pos.loc.x <<" - " << wm->ourRobot[2].pos.loc.y;
    return rc;
//    /*
// * TAMARIN GHABL


//    rc0.maxSpeed = 3;
//    rc0.useNav = true;
//    rc1.maxSpeed = 3;
//    rc1.useNav = true;

//    if((id == 0)&&(firstPos1 == false)){
//        rc0.fin_pos.loc = Vector2D(-2000,1000);
//            firstPos1 = true;
//    }
//    else if((id == 1)&&(firstPos2 == false)){
//        rc1.fin_pos.loc = Vector2D(-2000,-1000);
//            firstPos2 = true;
//    }
//    else if((id == 0)&&(firstPos1 == true)&&(active == true)&&(firstPos2 == true)){
//        rc0.fin_pos.loc.x = wm->ourRobot[1].pos.loc.x;
//        if(std::abs(wm->ourRobot[0].pos.loc.x - wm->ourRobot[0].pos.loc.x) < 20){
//            active = false;
//        }
//    }
//    else if((id == 1)&&(firstPos2 == true)&&(active == false)&&(firstPos1 == true)){
//        rc1.fin_pos.loc = Vector2D(-wm->ourRobot[0].pos.loc.x,-1000);
//        if(std::abs(wm->ourRobot[1].pos.loc.x - (-wm->ourRobot[0].pos.loc.x)) < 20){
//            active = true;
//        }
//    }
//    if(id == 0)
//        return rc0;
//    if(id == 1)
//        return rc1;

//        */
//    //Step1
//    qDebug() << "fskdfj";

//    if(!wm->ourRobot[id].isValid) return rc;
////    //    wm->debug_pos.clear();
////    //    wm->debug_pos.append(wm->ourRobot[1].pos.loc);
////    //    wm->debug_pos.append(wm->ourRobot[0].pos.loc);
////    //    Vector2D p2 = Field::ourGoalCenter;
////    //    Vector2D p1 = wm->ball.pos.loc;
////    //    Segment2D ballViewMidSeg(p2,p1);
////    static double rad = 90;
////    double khata = 0.2;
////    if((id == 0) && (kicked == false)){
////        Ray2D ray(wm->ourRobot[1].pos.loc,wm->ball.pos.loc);
////        Circle2D cir(wm->ball.pos.loc,rad);
////        Vector2D* v1 = new Vector2D();
////        Vector2D* v2 = new Vector2D();
////        cir.intersection(ray,v1,v2);
////        if(v1->dist(wm->ourRobot[1].pos.loc) > v2->dist(wm->ourRobot[1].pos.loc)){
////            rc.fin_pos.loc = *v1;
////            rc.useNav = true;
////            rc.maxSpeed = 3;
////            Ray2D rayInvert(wm->ball.pos.loc,wm->ourRobot[1].pos.loc);
////            rc.fin_pos.dir = rayInvert.dir().radian();
////            rc.isBallObs = true;
////            if(wm->ourRobot[0].pos.loc.dist(*v1) < 150){
////                rc.maxSpeed = 3;
////                rc.isBallObs = false;
////                if(((std::abs(wm->ourRobot[0].pos.dir - rayInvert.dir().radian()) < khata) ||
////                        (((M_PI*2) - std::abs(wm->ourRobot[0].pos.dir - rayInvert.dir().radian())) < khata)) && (wm->ourRobot[0].pos.loc.dist(wm->ball.pos.loc) < 110)){
////                    rc.kickspeedx = 4;
////                    rc.kickspeedz = 1;
////                    kicked = true;
////                }
////            }
////        }
////        else{
////            rc.fin_pos.loc = *v2;
////            rc.useNav = true;
////            rc.maxSpeed = 3;
////            rc.isBallObs = true;
////            if(wm->ourRobot[0].pos.loc.dist(*v2) < 150){
////                rc.maxSpeed = 3;
////                rc.isBallObs = false;
////                Ray2D rayInvert(wm->ball.pos.loc,wm->ourRobot[1].pos.loc);
////                rc.fin_pos.dir = rayInvert.dir().radian();
////                double rand = ((double) std::rand() / (RAND_MAX));
////                std::cout << (wm->ourRobot[0].pos.loc.dir() - rayInvert.dir()).radian() << std::endl;
////                if(((std::abs(wm->ourRobot[0].pos.dir - rayInvert.dir().radian()) < khata) ||
////                        (((M_PI*2) - std::abs(wm->ourRobot[0].pos.dir - rayInvert.dir().radian())) < khata)) && (wm->ourRobot[0].pos.loc.dist(wm->ball.pos.loc) < 110)){
////                    rc.kickspeedx = 4;
////                    rc.kickspeedz = 1;
////                    kicked = true;
////                }
////            }
////        }
////    }
////    if((id == 1) && (kicked == true)){
////        AngleDeg angSefr(0);
////        Line2D ray(wm->ourRobot[1].pos.loc,angSefr);
////        Vector2D jabejaSorat(wm->ball.vel.loc.x - wm->ball.pos.loc.x,wm->ball.vel.loc.y - wm->ball.pos.loc.y);
////        Line2D ray2(wm->ball.pos.loc,jabejaSorat);
////        Vector2D javab = ray.intersection(ray2);
////        rc.fin_pos.loc.x = javab.x;
////        rc.fin_pos.loc.y = javab.y;
////        rc.fin_pos.dir = (*(new Ray2D(wm->oppRobot[1].pos.loc,Field::ourGoalCenter))).dir().radian();
////        rc.maxSpeed = 6;
////        rc.useNav = true;
////        if(wm->ourRobot[1].pos.loc.dist(wm->ball.pos.loc) < 700)
////            kicked = false;
////    }
////    if((id == 1) && (kicked == false)){
////        rc.fin_pos.loc.x = wm->ourRobot[1].pos.loc.x;
////        rc.fin_pos.loc.y = wm->ourRobot[1].pos.loc.y;
////    }
////    if((id == 0) && (kicked == true)){
////        rc.fin_pos.loc.x = wm->ourRobot[0].pos.loc.x;
////        rc.fin_pos.loc.y = wm->ourRobot[0].pos.loc.y;
////    }
//    rc.fin_pos.loc.x = -2800;
//    rc.fin_pos.loc.y = 0;
//    rc.useNav = true;
//    rc.maxSpeed = 2;
//    qDebug()<<"i am here";
//    return rc;
}
