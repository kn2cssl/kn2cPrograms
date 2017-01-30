#ifndef TACTICTEST2_H
#define TACTICTEST2_H

#include "tactic.h"
#include "geom2/shape2d.h"

class TacticTest2: public Tactic
{
    Q_OBJECT
public:
    explicit TacticTest2(WorldModel *worldmodel, QObject *parent = 0);
    virtual RobotCommand getCommand();

private:

};
#endif // TACTICTEST2_H
