#ifndef FREEKICK_BASE_H
#define FREEKICK_BASE_H

#include "tactics.h"
#include <QObject>
#include "worldmodel.h"

enum fkRegion
{
    LeftRegion,
    CenterRegion,
    RightRegion
};

class freeKick_base : public QObject
{
    Q_OBJECT
public:
    freeKick_base(WorldModel *worldmodel, QObject *parent = 0);

    virtual void execute() = 0;
    Tactic* getTactic(int id);
    virtual int enterCondition(Level level) = 0;
    void zonePositions(int leftID,int RightID,Position& goalie,Position& left,Position& right);
    void resetValues();

protected:
    void initRole();
    void setTactics(int index);

protected:
    WorldModel *wm;
    Tactic *tactics[PLAYERS_MAX_NUM];
    fkRegion freeKickRegion;
    Level oppLevel;

    bool rolesIsInit;

    bool freeKickStart;
    TacticGoalie*   tGolie;
    TacticDefender* tDefenderLeft;
    TacticDefender* tDefenderRight;
    TacticDefender* tDefenderMid;
    TacticAttacker* tAttackerMid;
    TacticAttacker* tAttackerLeft;
    TacticAttacker* tAttackerRight;
};

#endif // FREEKICK_BASE_H
