#ifndef TACTICTEST2_H
#define TACTICTEST2_H

#include "tactic.h"
#include "geom2/shape2d.h"

class TacticTest2: public Tactic
{
    Q_OBJECT
public:
    int flag=0;
    int flag1=0;
    QList <Vector2D> way;
    explicit TacticTest2(WorldModel *worldmodel, QObject *parent = 0);
    virtual RobotCommand getCommand();
<<<<<<< HEAD
=======

private:

<<<<<<< HEAD
>>>>>>> 5aee4ed9254def077fb748ede91039b2d492a21c
=======
>>>>>>> 5aee4ed9254def077fb748ede91039b2d492a21c
};
#endif // TACTICTEST2_H
