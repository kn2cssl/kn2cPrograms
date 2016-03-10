#ifndef PLAY_H
#define PLAY_H

#define attackernoticeabledistance 200
#define desireddefenderdistance 300
#define desiredleftdefenderdistance 150
#define desiredrightdefenderdistance 150
#define middleAreaWidth 200
#define rightTirak -1
#define leftTirak 1


#include <QObject>
#include "worldmodel.h"
#include "tactics.h"

class Play : public QObject
{
    Q_OBJECT
public:
    explicit Play(QString name, WorldModel *worldmodel, QObject *parent = 0);
    QString getName();
    virtual void execute() = 0;
    virtual Tactic* getTactic(int id);
    virtual int enterCondition() = 0;
    bool conditionChanged();
    void zonePositions(int leftID,int RightID,int MidID,Position& goalie,Position& left, bool& leftNav,Position& right, bool& rightNav);
    bool haltedRobotIsInField(int robotID);

protected:
    WorldModel *wm;
    QString param;
    Tactic *tactics[PLAYERS_MAX_NUM];
    virtual void initRole() = 0;

    int numberOfDef;
    int numberOfPlayers;
    bool rolesIsInit;

    int leftChecker;
    int rightChecker;
    int previousLeftID;
    int previousRightID;

private:
    bool hasPositionForGoalie(Vector2D midOfDef);
    Position goalieInPenalty();

    QString name;

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
};

#endif // PLAY_H
