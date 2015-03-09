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
    void isKicker(int recieverID);
    void isKicker(Vector2D pos);
    void waitTimerStart(bool onMyCommand);
    void setGameOnPositions(Position pos);
    void setGameOnPositions(Vector2D pos);
    void setIdlePosition(Position pos);
    void setIdlePosition(Vector2D pos);

    void youHavePermissionForKick();

    bool everyOneInTheirPos;

private:
    bool isFree(int index);

    Vector2D receiverPos;
    bool findReciever;
    QTimer *waitTimer;
    Position idlePosition;
    bool pastMidPoint; // FreeKick

private slots:
    void dontWait();

protected:
    bool canKick;
};

#endif // TACTICATTACKER_H
