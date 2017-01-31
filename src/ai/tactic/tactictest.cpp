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
    if(min > wm->ourRobot[5].vel.dir)
        min = wm->ourRobot[5].vel.dir;
    if(max < wm->ourRobot[5].vel.dir)
        max = wm->ourRobot[5].vel.dir;
    qDebug() << "robot" << "max" << max << "min" <<min;
    return rc;
}
