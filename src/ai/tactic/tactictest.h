#ifndef TACTICTEST_H
#define TACTICTEST_H
#include "tactic.h"
#define DangerDist 300
class TacticTest : public Tactic
{
private:
    Vector2D* finalPos;
    Q_OBJECT
public:
    int max = -10;
    int min = 10;
    int flag=0;
    static bool kicked;
    explicit TacticTest(WorldModel *worldmodel, QObject *parent = 0);
    virtual RobotCommand getCommand();
};
#endif // TACTICTEST_H

