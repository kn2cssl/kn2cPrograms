#include "tacticteststandingforwardenemy.h"


int TacticTestStandingForwardEnemy::getDistance() const
{
    return distance;
}

void TacticTestStandingForwardEnemy::setDistance(int value)
{
    distance = value;
}

int TacticTestStandingForwardEnemy::getOppRobotIndex() const
{
    return OppRobotIndex;
}

void TacticTestStandingForwardEnemy::setOppRobotIndex(int value)
{
    OppRobotIndex = value;
}
TacticTestStandingForwardEnemy::TacticTestStandingForwardEnemy(WorldModel *worldmodel, QObject *parent) :
    Tactic("TacticTest", worldmodel, parent)
{
}

RobotCommand TacticTestStandingForwardEnemy::getCommand(){
    RobotCommand rc;
    if(!wm->ourRobot[id].isValid)
        return rc;
    rcsc::Segment2D line(wm->oppRobot[OppRobotIndex].pos.loc,Field::ourGoalCenter);
    rcsc::Circle2D circle(wm->oppRobot[OppRobotIndex].pos.loc,distance);
    Vector2D* v1 = new Vector2D();
    Vector2D* v2 = new Vector2D();
    circle.intersection(line,v1,v2);
    if((v1->x != 0) && (v1->y != 0)){
        rc.fin_pos.loc.x = v1->x;
        rc.fin_pos.loc.y = v1->y;
    }
    if((v2->x != 0) && (v2->y != 0)){
        rc.fin_pos.loc.x = v2->x;
        rc.fin_pos.loc.y = v2->y;
    }
    rc.useNav = true;
    rc.maxSpeed = 3;
    return rc;
}
