#ifndef TACTICTEST_H
#define TACTICTEST_H
#include "tactic.h"
#define DangerDist 300
class TacticTest : public Tactic
{
    Q_OBJECT
public:
    int flag=0;
    int flag1=0;
    int flag2=0;
    int flag3=0;
    explicit TacticTest(WorldModel *worldmodel, QObject *parent = 0);
    virtual RobotCommand getCommand();
<<<<<<< HEAD
=======

    void setpos ( Vector2D pos);

    void setidtest (int idt);

    void setpos ( Vector2D pos);

    void setidtest (int idt);

private:
    Vector2D fpos;

    int idtest;
<<<<<<< HEAD
>>>>>>> 5aee4ed9254def077fb748ede91039b2d492a21c
=======
>>>>>>> 5aee4ed9254def077fb748ede91039b2d492a21c
};
#endif //

