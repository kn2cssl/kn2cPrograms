#include "hillclimbing.h"

HillClimbing::HillClimbing(QObject *parent) :
    QObject(parent)
{
}

void HillClimbing::set_epsilon(double eps)
{
    this->epsilon = eps;
}

void HillClimbing::set_highestScore(int score)
{
    this->highestScore = score;
}

void HillClimbing::reset_minFind()
{
    this->minFind = false;
}

double HillClimbing::get_highestScore()
{
    return this->highestScore;
}

bool HillClimbing::is_findMin()
{
    return minFind;
}

void HillClimbing::generate_newPolicies()
{
    for(int i=0;i<RAND_POLICY_NUMBER;i++)
    {
        Policy tmp;

        for(int j=0;j<defaultPolicy.get_numberOfParameters();j++)
        {
            srand(time(NULL)+i);

            /* generate secret number between -epsilon and epsilon: */
            double random = ((double)rand() / (double)(RAND_MAX));
            double random_epsilon = (random * (2*epsilon)) - epsilon;

            tmp.set_parameterAt(j, defaultPolicy.get_parameterAt(j) + random_epsilon);
        }

        random_policies[i] = tmp;
    }
}

int HillClimbing::getNewPolicy()
{
    for( int i=0; i < RAND_POLICY_NUMBER; i++ )
    {
        if( !random_policies[i].is_finalReward_calculated() )
        {
            qDebug() << "i : "<<i<<" is selected";
            return i;
        }
    }

    return -1;
}

Policy *HillClimbing::getPolicyAt(int index)
{
    return &random_policies[index];
}

Policy HillClimbing::get_finalPolicy()
{
    return this->finalPolicy;
}

void HillClimbing::set_defaultPolicy(Policy policy)
{
    this->defaultPolicy = policy;
}
