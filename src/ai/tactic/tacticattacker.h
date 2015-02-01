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
    void setGameOnPositions(Position pos);
    void setGameOnPositions(Vector2D pos);
    void setIdlePosition(Position pos);
    void setIdlePosition(Vector2D pos);

    bool everyOneInTheirPos;

private:
    QTimer *waitTimer;
    Position idlePosition;

    bool pastMidPoint; // FreeKick

    bool isFree(int index);

private slots:
    void dontWait();
protected:
    bool canKick;
};

#endif // TACTICATTACKER_H
