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

    bool rolesIsInit;

    bool freeKickStart;
    TacticGoalie*   tGolie;
    TacticDefender* tDefenderLeft;
    TacticDefender* tDefenderRight;
    TacticAttacker* tAttackerMid;
    TacticAttacker* tAttackerLeft;
    TacticAttacker* tAttackerRight;

private:
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

#endif // FREEKICK_BASE_H
