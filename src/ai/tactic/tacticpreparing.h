#ifndef TacticPreparing_H
#define TacticPreparing_H

#include "tactic.h"

class TacticPreparing : public Tactic
{
    Q_OBJECT
public:
    explicit TacticPreparing(WorldModel *worldmodel, QObject *parent = 0);
    virtual RobotCommand getCommand();

    Position queuePos;
    bool kickPermision;
    bool kickIt;

    SkillKick* sKick;
};

#endif // TacticPreparing_H
