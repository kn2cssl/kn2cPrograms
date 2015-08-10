#include "policy.h"

Policy::Policy()
{
    reset_finalReward();
}

void Policy::add_reward(double reward)
{
    rewards.append(reward);
    if( rewards.size() > TOTAL_ITERATIONS )
    {
        double tmp = 0;
        for( int i = 0; i < rewards.size(); i++ )
        {
            tmp += rewards.at(i);
        }
        this->finalReward = tmp / rewards.size();
        this->finalReward_calculated = true;
        rewards.clear();
    }
}

void Policy::set_parameterAt(int index, double param)
{
    parameters[index] = param;
}

double Policy::get_parameterAt(int index)
{
    return parameters[index];
}

void Policy::set_numberOfParameters(int num)
{
    this->numberOfParameters = num;
}

int Policy::get_numberOfParameters()
{
    return this->numberOfParameters;
}

void Policy::reset_finalReward()
{
    this->finalReward_calculated = false;
}

bool Policy::is_finalReward_calculated()
{
    return this->finalReward_calculated;
}

double Policy::get_finalReward()
{
    return this->finalReward;
}

int Policy::get_iteration()
{
    return this->rewards.size();
}
