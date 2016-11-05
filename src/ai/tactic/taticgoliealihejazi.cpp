#include "taticgoliealihejazi.h"

taticgoliealihejazi::taticgoliealihejazi(WorldModel *worldmodel, QObject *parent) :
    Tactic("TacticTest", worldmodel, parent)
{
}

RobotCommand taticgoliealihejazi::getCommand()
{
    RobotCommand rc;
    if(wm->ball.vel.loc.dist(*new Vector2D(0,0)) < 40){
        rc.fin_pos.loc = Vector2D(0,0);
    }
    return rc;
}

