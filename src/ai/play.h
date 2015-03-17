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
    void zonePositions(int leftID,int RightID,int MidID,Position& goalie,Position& left,Position& right);






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

    void Ref_2Deff_Player(Position p);
    void Ref_2Deff_Ball();
    void Ref_1Deff_Player(Position p,int Left_ID,int Right_ID,int Mid_ID);
    void Ref_1Deff_Ball(int Left_ID,int Right_ID,int Mid_ID);


    Segment2D Ball_2_Left_Goal,Ball_2_Right_Goal;
    Vector2D alaki1,alaki2,Intersect_Right,Intersect_Left;

    Position Player1;

    void Deffence_Geometry_making();
    Vector2D Right_loc,Left_loc,Deffence_center,Wall;
    double Wall_length,Dist_2_Deffence;

    Position Find_OppRobot_BallOwner();
    bool BallOwner_Finded;

};

#endif // PLAY_H
