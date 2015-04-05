#ifndef TACTICDEFENDER_H
#define TACTICDEFENDER_H

#include "tactic.h"

class TacticDefender : public Tactic
{
    Q_OBJECT
public:
    explicit TacticDefender(WorldModel *worldmodel, QObject *parent = 0);
    virtual RobotCommand getCommand();
    void setIdlePosition(Position pos);
    void setIdlePosition(Vector2D pos);
    void resetBooleans();
    void setUseNav(bool input);

private:
    Position idlePosition;
    bool reach2Ball;
    bool useNav;
    int oppPassReciever;
};

#endif // TACTICDEFENDER_H
