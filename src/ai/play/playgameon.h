#ifndef PLAYGAMEON_H
#define PLAYGAMEON_H

#include "play.h"
#include "QDebug"
#include "man2man.h"

class PlayGameOn : public Play
{
    Q_OBJECT
public:
    explicit PlayGameOn(WorldModel *worldmodel, QObject *parent = 0);
    virtual void execute();
    //virtual Tactic* getTactic(int id);
    virtual int enterCondition();
    void setTactics(int index);
    void pressing(int ballOwner);
    int findBallOwner();
    void setPlayer2Keep(int ourR,int oppR);
    QList<AgentRegion> freeRegions();

private:
    TacticGoalie*   tGolie;
    TacticDefender* tDefenderLeft;
    TacticDefender* tDefenderRight;
    TacticDefender* tDefenderMid;
    TacticAttacker* tAttackerLeft;
    TacticAttacker* tAttackerRight;
    TacticAttacker* tAttackerMid;

    virtual void initRole();
    void coach();
    void setGameOnPos(int ourR,Vector2D oppR);
};

#endif // PLAYGAMEON_H
