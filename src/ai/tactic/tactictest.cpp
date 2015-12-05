#include "tactictest.h"
TacticTest::TacticTest(WorldModel *worldmodel, QObject *parent) :
    Tactic("TacticTest", worldmodel, parent)
{
    sTest = new SkillKick(wm);
}
RobotCommand TacticTest::getCommand()
{
    RobotCommand rc;
    if(!wm->ourRobot[id].isValid) return rc;

    sTest->execute(rc, this->id);



    return rc;
}
