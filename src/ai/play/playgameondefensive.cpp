#include "playgameondefensive.h"

PlayGameOnDefensive::PlayGameOnDefensive(WorldModel *worldmodel, QObject *parent) :
    Play("PlayGameOnDefensive", worldmodel, parent)
{
}

int PlayGameOnDefensive::enterCondition()
{
    if( false )
        return 100;
    else
        return 0;

    return 0;
}

void PlayGameOnDefensive::initRole()
{

}

void PlayGameOnDefensive::execute()
{
}
