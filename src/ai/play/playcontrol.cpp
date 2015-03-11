
#include "playcontrol.h"
playControl::playControl(WorldModel *worldmodel, QObject *parent) :
    Play("playcontrol", worldmodel, parent)
{

    anghezy=new tacticControl(wm);

}

int playControl::enterCondition()
{
    return 20000;
}

void playControl::initRole()
{
}

void playControl::execute()
{
    tactics[4] = anghezy ;
        tactics[3] = anghezy ;
}

