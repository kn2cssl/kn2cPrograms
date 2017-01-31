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
    int flag=0;
    int flag1=0;
    QList <Vector2D> way;
    explicit TacticTest2(WorldModel *worldmodel, QObject *parent = 0);
    virtual RobotCommand getCommand();
<<<<<<< HEAD
<<<<<<< HEAD
    Vector2D* getFinalPos();
    void setFinalPos(Vector2D value);
    int getBallVelocity() const;
    void setBallVelocity(int value);
=======
>>>>>>> d766c95da96dc8ee70e0992aefe4e0a62d783e28
=======

private:
>>>>>>> 4bde963eede2897a0748e0221474ee6c1450efde
};
#endif // TACTICTEST2_H
