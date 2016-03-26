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
    void zonePositions(int leftID, int RightID, int MidID, Position &goalie, Position &left, bool& leftNav, Position &right, bool& rightNav);
    virtual void resetValues() = 0;

    bool haltedRobotIsInField(int robotID);

protected:
    void initRole();
    void setTactics(int index);

protected:
    WorldModel *wm;
    Tactic *tactics[PLAYERS_MAX_NUM];
    fkRegion freeKickRegion;
    Level oppLevel;

    int leftChecker;
    int rightChecker;
    int previousLeftID;
    int previousRightID;

    bool rolesIsInit;

    bool defenderflag;
    bool defendersflag;
    bool goalkeepermovmentflag;
    bool defendermovmentflag;
    bool angelflag;
    bool angelflags;


//    Vector2D goalkeeperlastpos;
//    Vector2D defenderlastpos;
    Vector2D balllastpos;
//    double goalkeeperlastdir;
//    double defenderlastdir;

    Vector2D leftDefenderLastpos;
    Vector2D rightDefenderLastpos;

    int defenderlasttirak;
    int goalkeeperlasttirak;

    bool freeKickStart;
    TacticGoalie*   tGolie;
    TacticDefender* tDefenderLeft;
    TacticDefender* tDefenderRight;
    TacticAttacker* tAttackerMid;
    TacticAttacker* tAttackerLeft;
    TacticAttacker* tAttackerRight;

private:
};

#endif // FREEKICK_BASE_H
