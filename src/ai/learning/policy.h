#ifndef POLICY_H
#define POLICY_H

#define TOTAL_ITERATIONS 2

#include <QList>

class Policy
{

public:
    explicit Policy();
    void add_reward(double reward);

    void set_parameterAt(int index, double param);
    double get_parameterAt(int index);

    void set_numberOfParameters(int num);
    int get_numberOfParameters();

    void reset_finalReward();
    bool is_finalReward_calculated();


    double get_finalReward();

    int get_iteration();

private:
    QList<double> rewards;
    double parameters[100];
    double finalReward;
    bool finalReward_calculated;
    int numberOfParameters;
};

#endif // POLICY_H
