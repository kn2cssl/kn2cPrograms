#ifndef TACTICTEST_H
#define TACTICTEST_H
#include "tactic.h"
#define DangerDist 300
class TacticTest : public Tactic
{
    Q_OBJECT
public:
    explicit TacticTest(WorldModel *worldmodel, QObject *parent = 0);
    virtual RobotCommand getCommand();

    void setpos ( Vector2D pos);

    void setidtest (int idt);

private:
    Vector2D fpos;

    int idtest;
};
#endif //

