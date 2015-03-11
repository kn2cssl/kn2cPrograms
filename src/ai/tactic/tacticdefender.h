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

private:
    Position idlePosition;
};

#endif // TACTICDEFENDER_H
