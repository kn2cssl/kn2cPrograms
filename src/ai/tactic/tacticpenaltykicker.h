#ifndef TACTICPENALTYKICKER_H
#define TACTICPENALTYKICKER_H

#include "tacticattacker.h"

class TacticPenaltyKicker:public TacticAttacker
{
    Q_OBJECT
public:
    explicit TacticPenaltyKicker(WorldModel *worldmodel, QObject *parent = 0);
    virtual RobotCommand getCommand();
    void resetEverything();
private:
    bool targetSelected;
    Vector2D target;
    SkillKick* sKick;
};

#endif // TACTICPENALTYKICKER_H
