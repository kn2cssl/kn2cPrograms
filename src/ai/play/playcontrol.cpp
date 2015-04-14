
#include "playcontrol.h"
playControl::playControl(WorldModel *worldmodel, QObject *parent) :
    Play("playcontrol", worldmodel, parent)
{

    anghezy=new tacticControl(wm);

}

int playControl::enterCondition()
{
    return 0;
}

void playControl::initRole()
{
}

void playControl::execute()
{
    tactics[7] = anghezy ;
    tactics[3] = anghezy ;
}

