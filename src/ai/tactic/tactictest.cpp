#include "tactictest.h"
TacticTest::TacticTest(WorldModel *worldmodel, QObject *parent) :
    Tactic("TacticTest", worldmodel, parent)
{
}

RobotCommand TacticTest::getCommand()
{
    RobotCommand rc;

    if(!wm->ourRobot[id].isValid) return rc;

    if(id==4){ //3
        flag2++;
        QList <Vector2D> points;
        Vector2D v1(-1700,-2000);  // -2250 - -2000
        Vector2D v2(-1700,2000);

        qDebug()<<"wtf!";
        if(flag==0){

            rc.fin_pos.loc=v1;
            rc.maxSpeed=4;
            rc.useNav=true;
            rc.isBallObs=true;
            //Vector2D d(0,0);
            rc.fin_pos.dir=(v1-v2).dir().radian();
            if(wm->ourRobot[id].pos.loc.dist(v1)<150){
                flag=1;
            }
        }

        else if(flag==1){

            rc.fin_pos.loc=v2;
            rc.maxSpeed=4;
            rc.useNav=true;
            //Vector2D d(0,0);
            rc.fin_pos.dir=(v1-v2).dir().radian();
            if(wm->ourRobot[id].pos.loc.dist(v2)<150){
                flag=0;
                points.clear();
                wm->debug_pos.clear();
            }
        }
        //if(flag2%10==0){
        //    points.push_back(wm->ourRobot[3].pos.loc);
        //}
        //wm->debug_type=2;
        //for(int i=0;i<points.length();i++){
        //    wm->debug_pos.append(points);
        //}
        return rc;


    }

    else if(id==5){

//        Vector2D v1(-1700,-2000);  // -2250 - -2000
//        Vector2D v2(-1700,2000);
        Vector2D v1(-3900,1000);
        Vector2D v2(-800,1000);
        wm->debug_pos.append(v1);
        wm->debug_pos.append(v2);
        if(flag1==0){

            rc.fin_pos.loc=v1;
            rc.maxSpeed=2;
            rc.useNav=false;
            if(wm->ourRobot[5].pos.loc.dist(v1)<100){
                flag1=1;
            }
        }
        else if(flag1==1){

            rc.fin_pos.loc=v2;
            rc.maxSpeed=2;
            rc.useNav=false;
            if(wm->ourRobot[5].pos.loc.dist(v2)<100){
                flag1=0;
            }
        }
        return rc;

    }

    else if(id==1){ // 7 for real

        if(flag2==0){
            Vector2D v1(-500,1000);
            rc.fin_pos.loc=v1;
            rc.maxSpeed=2;
            rc.useNav=false;
            if(wm->ourRobot[1].pos.loc.dist(v1)<100){   // 7 for real
                flag2=1;
            }
        }
        else if(flag2==1){
            Vector2D v2(-500,-1000);
            rc.fin_pos.loc=v2;
            rc.maxSpeed=2;
            rc.useNav=false;
            if(wm->ourRobot[1].pos.loc.dist(v2)<100){ // 7 for real
                flag2=0;
            }
        }
        return rc;

    }

    else{
        rc.maxSpeed=0;
        return rc;
    }

}
