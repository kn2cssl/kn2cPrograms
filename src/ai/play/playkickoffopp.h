#ifndef PLAYKICKOFFOPP_H
#define PLAYKICKOFFOPP_H

#include "play.h"

class PlayKickoffOpp : public Play
{
    Q_OBJECT
public:
    explicit PlayKickoffOpp(WorldModel *worldmodel, QObject *parent = 0);
    virtual void execute();
    //virtual Tactic* getTactic(int id);
    virtual int enterCondition();
    void Positioning(int RobotID);

private:
    TacticGoalie*   tGolie;
    TacticAttacker* tAttackerMid;
    TacticAttacker* tAttackerLeft;
    TacticAttacker* tAttackerRight;
    TacticDefender* tDefenderLeft;
    TacticDefender* tDefenderRight;
    int kickerId;
    virtual void initRole();
    void setTactics(int index);
    int maximumGoalChanceID(QList<int> oppPlayer);
    bool isInsideTriangle(Vector2D pos,Vector2D vertex1);
    Position KickerPositioning(Vector2D oppKicker);
    void findOppKickerId();
};

#endif // PLAYKICKOFFOPP_H
