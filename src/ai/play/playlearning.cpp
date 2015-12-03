#include "playlearning.h"

PlayLearning::PlayLearning(WorldModel *worldmodel, QObject *parent) :
    Play("PlayLearning", worldmodel, parent)
{
    tKickLearner = new TacticKickLearning(worldmodel);
}

int PlayLearning::enterCondition()
{
    return 0;
}

void PlayLearning::initRole()
{
}

void PlayLearning::execute()
{
    tactics[2] = tKickLearner;
}
