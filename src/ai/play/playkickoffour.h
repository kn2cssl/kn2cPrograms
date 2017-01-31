#ifndef PLAYKICKOFFOUR_H
#define PLAYKICKOFFOUR_H

#include "play.h"

class PlayKickoffOur : public Play
{
    Q_OBJECT
public:
    explicit PlayKickoffOur(WorldModel *worldmodel, QObject *parent = 0);
    virtual void execute();
    //virtual Tactic* getTactic(int id);
    virtual int enterCondition();

private:
    TacticGoalie*   tGolie;
    TacticAttacker* tAttackerMid;
    TacticAttacker* tAttackerLeft;
    TacticAttacker* tAttackerRight;
    TacticDefender* tDefenderLeft;
    TacticDefender* tDefenderRight;

    virtual void initRole();
    void setTactics(int index);
    void setPositions();
};
#endif // PLAYKICKOFFOUR_H
