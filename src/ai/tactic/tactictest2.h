#ifndef TACTICTEST2_H
#define TACTICTEST2_H

#include "tactic.h"
#include "geom2/shape2d.h"

class TacticTest2: public Tactic
{
    Q_OBJECT
public:
    explicit TacticTest2(WorldModel *worldmodel, QObject *parent = 0);
    virtual RobotCommand getCommand();
    void findCriticalPlayer();
    void findInvalidRanges();
    void sortInvalidRanges();
    void findValidRanges();
    RobotCommand goBehindBall();
    double findBestPoint();

    bool go;
    int state;

private:
    QList<int> important_opp_agents;
    QList<int> important_our_agents;
    int numberOfInvalidRanges;
    int numberOfValidRanges;
    double angle[12][2];
    double valid_angle[12][2];
    double uGoal;
    double dGoal;
protected:
    bool canKick;
};
#endif // TACTICTEST2_H
