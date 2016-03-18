#include "tactictest2.h"
TacticTest2::TacticTest2(WorldModel *worldmodel, QObject *parent) :
    Tactic("TacticTest2", worldmodel, parent)
{
}
RobotCommand TacticTest2::getCommand()
{
    RobotCommand rc;
    if(!wm->ourRobot[id].isValid) return rc;

    return rc;
}
