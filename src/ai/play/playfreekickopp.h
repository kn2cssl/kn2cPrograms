#ifndef PLAYFREEKICKOPP_H
#define PLAYFREEKICKOPP_H

#include "play.h"

class PlayFreeKickOpp : public Play
{
    Q_OBJECT
public:
    explicit PlayFreeKickOpp(WorldModel *worldmodel, QObject *parent = 0);
    virtual void execute();
    //virtual Tactic* getTactic(int id);
    virtual int enterCondition();

private:
    bool pressingIsInit;
    bool go2ThePositions;

    TacticGoalie*   tGolie;
    TacticDefender* tDefenderLeft;
    TacticDefender* tDefenderRight;
    TacticDefender* tDefenderMid;
    TacticAttacker* tAttackerMid;
    TacticAttacker* tAttackerLeft;
    TacticAttacker* tAttackerRight;

    QTimer *waitTimer;

private slots:
    void waitTimer_timout();

protected:
    virtual void initRole();
    void initPressing();
private:
    void setTactics(int index);
    void setPositions(int index);
};

#endif // PLAYFREEKICKOPP_H
