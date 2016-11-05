#ifndef TACTICTEST2_H
#define TACTICTEST2_H

#include "tactic.h"
#include "geom2/shape2d.h"

class TacticTest2: public Tactic
{
private:
    Vector2D finalPos;
    int ballVelocity;
    Q_OBJECT
public:
    explicit TacticTest2(WorldModel *worldmodel, QObject *parent = 0);
    virtual RobotCommand getCommand();
    Vector2D* getFinalPos();
    void setFinalPos(Vector2D value);
    int getBallVelocity() const;
    void setBallVelocity(int value);
};
#endif // TACTICTEST2_H
