#ifndef TACTICGOALIE_H
#define TACTICGOALIE_H

#include "tactic.h"

class TacticGoalie : public Tactic
{
    Q_OBJECT
public:
    explicit TacticGoalie(WorldModel *worldmodel, QObject *parent = 0);
    virtual RobotCommand getCommand();
    void setIdlePosition(Position pos);
    void setIdlePosition(Vector2D pos);

private:
    Position idlePosistion;
    bool reach2Ball;

};

#endif // TACTICGOALIE_H
