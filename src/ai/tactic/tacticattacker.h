#ifndef TACTICATTACKER_H
#define TACTICATTACKER_H

#include "tactic.h"
#include "geom2/shape2d.h"

class TacticAttacker : public Tactic
{
    Q_OBJECT
public:
    explicit TacticAttacker(WorldModel *worldmodel, QObject *parent = 0);
    virtual RobotCommand getCommand();
    void findCriticalPlayer();
    void findInvalidRanges();
    void sortInvalidRanges();
    void findValidRanges();
    RobotCommand goBehindBall();
    RobotCommand goForKicking();
    double findBestPoint();
    int findBestPlayerForPass();
    void isKicker();

    bool kickedSucceccfully;

private:
    bool kicker_firstKick;
    QTimer *kicker_timer;
    QList<int> important_opp_agents;
    QList<int> important_our_agents;
    int numberOfInvalidRanges;
    int numberOfValidRanges;
    double angle[12][2];
    double valid_angle[12][2];
    double uGoal;
    double dGoal;

    bool isFree(int index);
protected:
    bool canKick;

private slots:
    void timerEvent();
};

#endif // TACTICATTACKER_H
