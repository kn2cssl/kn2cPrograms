#include "kick_learning.h"

Kick_Learning::Kick_Learning(QObject *parent) :
    HillClimbing(parent)
{
    this->totalSamples = TOTAL_SAMPLE_TIME / AI_TIMER;
    numberOfSamples = 0;
    templateScore = 200000000;
    highestScore = 0;
}

void Kick_Learning::set_kickTarget(Vector2D target)
{
    this->kickTarget = target;
}

void Kick_Learning::reward()
{
    double tmp = 20000000;

    if( wm->ball.isValid )  tmp = ( kickTarget - wm->ball.pos.loc).length();

    numberOfSamples ++;

    if( tmp < templateScore )
        templateScore = tmp;
}

bool Kick_Learning::end_of_sampling()
{
    if( numberOfSamples > totalSamples )
    {
        numberOfSamples = 0;
        highestScore = templateScore;
        templateScore = 20000000;
        return true;
    }

    return false;
}

void Kick_Learning::set_worldModel(WorldModel *wm)
{
    this->wm = wm;
}

void Kick_Learning::evaluate()
{
    finalPolicy = random_policies[0];

    for( int i = 0; i < RAND_POLICY_NUMBER; i++ )
    {
        qDebug() << "Hill "<<i<<" 's reward is : "<<random_policies[i].get_finalReward();
        if( random_policies[i].get_finalReward() < finalPolicy.get_finalReward() )
        {
            finalPolicy = random_policies[i];
        }
    }

    wm->climbing_status = "Finished";
    qDebug() << "Best Hill is : "<< finalPolicy.get_parameterAt(0);
}
