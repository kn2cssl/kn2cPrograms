#include "playtest.h"
PlayTest::PlayTest(WorldModel *worldmodel, QObject *parent) :
    Play("PlayTest", worldmodel, parent)
{

}

int PlayTest::enterCondition()
{
    return 0;
}

void PlayTest::initRole()
{
}

void PlayTest::execute()
{
}
