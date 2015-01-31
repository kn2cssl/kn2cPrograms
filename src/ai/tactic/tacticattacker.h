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
    RobotCommand goBehindBall();
    RobotCommand KickTheBallIndirect();
    RobotCommand KickTheBallDirect();
    RobotCommand StartTheGame();
    int findBestPlayerForPass();
    void isKicker();


    void waitTimerStart();
    void setGameOnPositions(Position input);
    void setGameOnPositions(Vector2D input);

    bool everyOneInTheirPos;

private:
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
