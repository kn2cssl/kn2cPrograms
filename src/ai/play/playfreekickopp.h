#ifndef PLAYFREEKICKOPP_H
#define PLAYFREEKICKOPP_H

#include "play.h"
#include "man2man.h"

class PlayFreeKickOpp : public Play
{
    Q_OBJECT
public:
    explicit PlayFreeKickOpp(WorldModel *worldmodel, QObject *parent = 0);
    virtual void execute();
    //virtual Tactic* getTactic(int id);
    virtual int enterCondition();

private:
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

private:
    void pressing();
    void setTactics(int index);
    void setPositions();
    void setPlayer2Keep(int ourR,int oppR);
};

#endif // PLAYFREEKICKOPP_H
