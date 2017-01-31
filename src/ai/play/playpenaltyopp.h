#ifndef PLAYPENALTYOPP_H
#define PLAYPENALTYOPP_H

#include "play.h"

class PlayPenaltyOpp : public Play
{
    Q_OBJECT
public:
    explicit PlayPenaltyOpp(WorldModel *worldmodel, QObject *parent = 0);
    virtual void execute();
    //virtual Tactic* getTactic(int id);
    virtual int enterCondition();

private:
    void setTactics(int index);
    void setPositions();

private:
    TacticDefender* tDefenderLeft;
    TacticDefender* tDefenderRight;
    TacticDefender* tDefenderMid;
    TacticGoalie* tGoalie;
    TacticAttacker* tAttackerMid;
    TacticAttacker* tAttackerRight;
    TacticAttacker* tAttackerLeft;

    virtual void initRole();

};

#endif // PLAYPENALTYOPP_H
