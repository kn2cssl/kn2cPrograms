#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "geom.h"
#include <QString>

// global constants
#define PLAYERS_MAX_NUM 12
#define FIELD_DOUBLE_MAX_X     4750
#define FIELD_DOUBLE_MAX_Y     3250
#define FIELD_SINGLE_MAX_X     3275
#define FIELD_SINGLE_MAX_Y     2275
#define BALL_RADIUS     22
#define ROBOT_RADIUS    90.0

#define PICOFCIR 500;
#define MARGINFROMGOALPOST 300;

#define PresenceCounter 1000

#define attackernoticeabledistance 200
#define desireddefenderdistance 300
#define desiredleftdefenderdistance 150
#define desiredrightdefenderdistance 150
#define middleAreaWidth 200
#define rightTirak -1
#define leftTirak 1

#define NUMOFDEFENDERS 2

#define DangerDist 300

#define our_speed 2

// rules constants
#define ALLOW_NEAR_BALL_RANGE 600

// Vision constants
#define CAMERA_NUM      4
#define VOBJ_MAX_NUM    5
#define MIN_CONF        0.1
#define VISION_TIMEDOUT 1000.0
#define MAX_RADIOUS     2000
#define MERGE_DISTANCE 90
#define MIN_CONFIDENCE 0.1


// Timer speeds
#define TRANSMITTER_TIMER   15
#define AI_TIMER            16

namespace Field
{
extern double MaxX;
extern double MinX;
extern double MaxY;
extern double MinY;

extern double GoalDeep;

extern Vector2D upperLeftCorner;
extern Vector2D upperRightCorner;
extern Vector2D bottomLeftCorner;
extern Vector2D bottomRightCorner;

extern Line2D leftLine, midLine, rightLine;

extern Line2D upLine, bottomLine;

extern double centerCircle_R, goalCircle_R, goalCircleEX_R, goalCircleDEF_R;

// Ours.
extern Vector2D ourGoalCenter, ourGoalPost_L, ourGoalPost_R;
extern double defenceLineLinear;
extern Vector2D defenceLineLinear_L, defenceLineLinear_R;
extern Vector2D ourPenaltySpot;

extern Vector2D ourDefPost_L, ourDefPost_R;

extern Circle2D ourDefenceCircle;

extern double defenderPermittedRegion;

// Opps.
extern Vector2D oppGoalCenter, oppGoalPost_L, oppGoalPost_R;
extern Vector2D oppGoalCC_L,oppGoalCC_R;
extern Vector2D oppPenaltySpot;

extern Vector2D ourPenaltyParallelLineCenter;
extern Vector2D oppPenaltyParallelLineCenter;

void setup_consts(QString field_size);
}

#endif // CONSTANTS_H
