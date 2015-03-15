#ifndef WORLDMODEL_H
#define WORLDMODEL_H

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

class WorldModel
{
public:
    explicit WorldModel(OutputBuffer *outputBuffer);
    double time;
    Ball ball;
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
    Level oppLevel;

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
};

#endif // WORLDMODEL_H
