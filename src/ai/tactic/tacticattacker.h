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
    RobotCommand KickTheBallIndirect();
    RobotCommand KickTheBallDirect();
    RobotCommand StartTheGame();
    double findBestPoint();
    int findBestPlayerForPass();
    void isKicker();
    float detectKickSpeed(Vector2D dest = Vector2D(0,0) );

    void waitTimerStart();
    void setGameOnPositions(Position input);
    void setGameOnPositions(Vector2D input);

    bool everyOneInTheirPos;

private:
    QList<int> important_opp_agents;
    QList<int> important_our_agents;
    int numberOfInvalidRanges;
    int numberOfValidRanges;
    double angle[12][2];
    double valid_angle[12][2];
    double uGoal;
    double dGoal;
    QTimer *waitTimer;
    Position gameOnPosition;

    bool pastMidPoint; // FreeKick

    bool isFree(int index);

private slots:
    void dontWait();
protected:
    bool canKick;
};

#endif // TACTICATTACKER_H
