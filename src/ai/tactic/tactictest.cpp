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

        Vector2D v1(-1700,-2000);
        Vector2D v2(-1700,2000);
        if(flag==0){
            rc.fin_pos.loc=v1;
            rc.maxSpeed=4;
            rc.useNav=true;
            if(wm->ourRobot[id].pos.loc.dist(v1)<150){
                flag=1;
            }
        }
        else if(flag==1){
            rc.fin_pos.loc=v2;
            rc.maxSpeed=4;
            rc.useNav=true;
            if(wm->ourRobot[id].pos.loc.dist(v2)<150){
                flag=0;
                wm->debug_pos.clear();
            }
        }
    return rc;
}
