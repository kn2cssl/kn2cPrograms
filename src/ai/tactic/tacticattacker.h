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
    double findBestPoint();
    int findBestPlayerForPass();

    bool go;
    int state;

private:
    bool kicker_canKick;
    bool kicker_firstKick;
    bool kicker_kicked;
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
