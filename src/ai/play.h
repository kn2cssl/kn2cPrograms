#ifndef PLAY_H
#define PLAY_H

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
    void zonePositions(int leftID,int RightID,Position& goalie,Position& left,Position& right);


    Position Ref_1Deff_Player(Position);
    void Deffence_Geometry_making();
    Segment2D Ball_2_Left_Goal,Ball_2_Right_Goal;
    Vector2D alaki1,alaki2,Intersect_Right,Intersect_Left,Right_loc,Left_loc;
    Position Find_OppRobot_BallOwner();
    bool BallOwner_Finded;



protected:
    WorldModel *wm;
    QString param;
    Tactic *tactics[PLAYERS_MAX_NUM];
    virtual void initRole() = 0;

    int numberOfDef;
    int numberOfPlayers;
    bool rolesIsInit;

private:
    QString name;

};

#endif // PLAY_H
