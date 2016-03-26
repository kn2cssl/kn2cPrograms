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

    bool isVeryCloseToGoal(Vector2D ballPoint);

private:
    Position idlePosistion;
    bool reach2Ball;
    SkillKick* sKick;

};

#endif // TACTICGOALIE_H
