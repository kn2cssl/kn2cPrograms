#ifndef HILLCLIMBING_H
#define HILLCLIMBING_H

#include <QObject>
#include <QDebug>
#include"policy.h"

#define RAND_POLICY_NUMBER 3

class HillClimbing : public QObject
{
    Q_OBJECT
public:
    explicit HillClimbing(QObject *parent = 0);
    virtual void reward() = 0;

    void set_epsilon(double eps);
    void set_highestScore(int score);
    void reset_minFind();

    double get_highestScore();
    bool is_findMin();

    virtual void evaluate() = 0;

    void generate_newPolicies();
    int getNewPolicy();

    Policy* getPolicyAt(int index);

    Policy get_finalPolicy();

    void set_defaultPolicy(Policy policy);

protected:
    Policy defaultPolicy;
    Policy random_policies[RAND_POLICY_NUMBER];
    Policy finalPolicy;
    double epsilon;
    double highestScore;
    bool minFind;
};

#endif // HILLCLIMBING_H
