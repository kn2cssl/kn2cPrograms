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
    static bool kicked;
    int flag=0;
    int flag1=0;
    int flag2=0;
    int flag3=0;
    explicit TacticTest(WorldModel *worldmodel, QObject *parent = 0);
    virtual RobotCommand getCommand();
};
#endif //

