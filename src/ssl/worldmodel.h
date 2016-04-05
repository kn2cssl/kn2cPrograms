#ifndef WORLDMODEL_H
#define WORLDMODEL_H

#define NUMBEROFFREEKICKS 13
#include <QList>
#include <QDebug>
#include "constants.h"
#include "base.h"
#include "ball.h"
#include "robot.h"
#include "agent.h"
#include "geom.h"
#include "game_state.h"
#include "ref_protocol.h"
#include "knowledge.h"

struct tANDp
{
    Vector2D pos;
    int prob;
};

enum Level
{
    Beginner,
    Amatuer,
    Profesional
};

enum kickType
{
    Shoot,
    FreeKick1,
    FreeKick2,
    FreeKick3,
    FreeKick4,
    FreeKick5,
    FreeKick6,
    FreeKick7,
    FreeKick8,
    FreeKick9,
    FreeKick10,
    FreeKick11,
    FreeKick12,
    FreeKick47
};

class WorldModel
{
public:
    explicit WorldModel(OutputBuffer *outputBuffer);
    double time;
    Ball ball;
    TeamColorType ourColor;
    Agent ourRobot[PLAYERS_MAX_NUM];
    Robot oppRobot[PLAYERS_MAX_NUM];
    GameStateType gs;
    GameStateType gs_last;
    GameState cmgs; //referee
    int ref_goalie_our;
    int ref_goalie_opp;
    bool isSim;
    Knowledge *kn;

    //----Input Data----------
    Level oppLevel_fk;
    double opp_vel;
    bool select_fk[NUMBEROFFREEKICKS];
    int freeKickerID;
    bool useShootSensor;
    bool defenceMode;
    bool useVoronoi;
    bool use4Player4Marking;

    //----Graphical Debug-----
    QList<Vector2D> navigation_pos;
    QList<Vector2D> navigation_result;

    bool showAstarOut;
    int indexOfAstarRobot;

    QList<Marking_Struct> marking;
    bool showMarking;

    QList<Segment2D> voronoi;
    bool showVoronoi;
    QList<Vector2D> selected;

    QList<tANDp> TANDPis;
    tANDp max_TANDPis;
    bool showChances;

    bool showDebug;
    QList<Vector2D> debug_pos;
    int debug_type;

    bool showPasses;
    QList<Vector2D> passPoints;

    bool showDefenderDebug;

    //---UDP 2 Matlab
    bool sendUDP;
    int indexOfUDP;
    QString whichUDP;

    static double var[10];
    // 0: kick activation dist
    // 1: kick activation angle
    // 2: kick precision angle
    // 3: prediction sliding factor

    double pos_coef[6];
    double mark_coef[6];

    //Machine Learning Parameters
    QString ml_type;
    //Hill Climbing
    QString climbing_status;
    int policy_index;
    int iteration_index;
    bool climbing_start;
    bool save_policies;
    bool load_policies;
    QString addressOfPolicyFile;
};

#endif // WORLDMODEL_H
