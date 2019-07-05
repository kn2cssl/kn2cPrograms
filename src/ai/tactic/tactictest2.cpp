#include "tactictest2.h"
TacticTest2::TacticTest2(WorldModel *worldmodel, QObject *parent) :
    Tactic("TacticTest2", worldmodel, parent)
{
}
RobotCommand TacticTest2::getCommand()
{
    RobotCommand rc;
    if(!wm->ourRobot[id].isValid) return rc;

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
    return rc;
}
