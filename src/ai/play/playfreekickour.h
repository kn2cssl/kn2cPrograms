#ifndef PLAYFREEKICKOUR_H
#define PLAYFREEKICKOUR_H

#include "play.h"

class PlayFreeKickOur : public Play
{
    Q_OBJECT
public:
    explicit PlayFreeKickOur(WorldModel *worldmodel, QObject *parent = 0);
    virtual void execute();
    //virtual Tactic* getTactic(int id);
    virtual int enterCondition();
private:
    virtual void initRole();
    bool conditionChanged();
    void setTactics(int index);

private:
    int numberOfDef;
    int numberOfPlayer;
    bool firstTimeInit;
    bool freeKickStart;
    TacticGoalie*   tGolie;
    TacticDefender* tDefenderLeft;
    TacticDefender* tDefenderRight;
    TacticDefender* tDefenderMid;
    TacticAttacker* tAttackerMid;
    TacticAttacker* tAttackerLeft;
    TacticAttacker* tAttackerRight;
};

#endif // PLAYFREEKICKOUR_H
