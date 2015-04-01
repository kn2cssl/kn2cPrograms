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
    void zonePositions(int leftID,int RightID,int MidID,Position& goalie,Position& left, bool& leftNav,Position& right, bool& rightNav);

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

private:
    QString name;

    void Player_filter(Position Player);
    double last_dir;//,dir;

    void Ref_2Deff_Player(Position p);
    void Ref_2Deff_Ball();
    void Ref_2Deff_Player2(Position p,Vector2D &Left_2,Vector2D &Right_2,Vector2D &Deff_center);
    void Ref_2Deff_Moving_Ball();
    void Ref_1Deff_Player(Position p,int Left_ID,int Right_ID,int Mid_ID);
    void Ref_1Deff_Ball(int Left_ID,int Right_ID,int Mid_ID);
    void Ref_1Deff_Player2(Position p,int Left_ID,int Right_ID,int Mid_ID,Vector2D &Loc);
    void Ref_1Deff_Moving_Ball(int Left_ID,int Right_ID,int Mid_ID);
    void Ref_2Deff_Loc(Vector2D loc);
    void Ref_1Deff_Loc(Vector2D loc,int Left_ID,int Right_ID,int Mid_ID,Vector2D &Loc);
    bool Danger_Player_Direction(Position p , int thr);
    bool Ball_Toward_Goal();

    bool hasPositionForGoalie(Vector2D midOfDef);
    Position goaliePosition(Vector2D midOfDef);
    Position goalieInPenalty();

    Position Player1,Player2;


    Vector2D Right_loc,Left_loc,Goalie_loc,Deffence_center,Wall;
    double Wall_length,Dist_2_Deffence;
    bool Ball_IS_Toward_Goal;

    void Deffence_Geometry_making();
    bool Find_OppRobot_BallOwner();
    bool Find_Pass_Receiver(Position Player1);
    bool Find_AnyOther_Opp_Dangerous();
    Vector2D Find_MostDangerous_Goal_Point();


    int Find_Dyno_Deffence(int Left_ID,int Right_ID,Vector2D Deff_center);
    Vector2D Find_Deff_center(Vector2D loc);
    Vector2D Average_Positioning(Vector2D l1,Vector2D l2);


    bool BallOwner_Finded,Player2_Finded;

};

#endif // PLAY_H
