#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "geom.h"

// global constants
#define PLAYERS_MAX_NUM 12
#define FIELD_MAX_X     4750
#define FIELD_MAX_Y     3250
#define BALL_RADIUS     22
#define ROBOT_RADIUS    90.0

#define PICOFCIR 500;
#define MARGINFROMGOALPOST 300;

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


// Timer speeds
#define TRANSMITTER_TIMER   15
#define AI_TIMER            16

namespace Field
{
const double MaxX = 4500;
const double MinX = -4500;
const double MaxY = 3000;
const double MinY = -3000;

const double GoalDeep = 180;

const Vector2D upperLeftCorner(MinX + 125, MaxY - 125);
const Vector2D upperRightCorner(MaxX - 125, MaxY - 125);
const Vector2D bottomLeftCorner(MinX + 125, MinY + 125);
const Vector2D bottomRightCorner(MaxX - 125, MinY + 125);

const Line2D leftLine(Vector2D(MinX,MinY), Vector2D(MinX, MaxY));
const Line2D midLine(Vector2D(0,MinY), Vector2D(0, MaxY));
const Line2D rightLine(Vector2D(MaxX, MinY), Vector2D(MaxX, MaxY));

const Line2D upLine(Vector2D(MinX, MaxY), Vector2D(MaxX, MaxY));
const Line2D bottomLine(Vector2D(MinX, MinY), Vector2D(MaxX, MinY));

const double centerCircle_R = 500;
const double goalCircle_R = 1000;
const double goalCircleEX_R = 600 + 3*ROBOT_RADIUS + 20;
const double goalCircleDEF_R = goalCircle_R + centerCircle_R/2 + 200;

// Ours.
const Vector2D ourGoalCenter(MinX, 0);
const Vector2D ourGoalPost_L(MinX, 500);
const Vector2D ourGoalPost_R(MinX, -500);
const double defenceLineLinear = 500;
const Vector2D defenceLineLinear_L(MinX, 250);
const Vector2D defenceLineLinear_R(MinX, -250);
const Vector2D ourPenaltySpot(MinX+1000,0);

const Vector2D ourDefPost_L(MinX, 1300);
const Vector2D ourDefPost_R(MinX, -1300);

const Circle2D ourDefenceCircle(ourGoalCenter,750+(ROBOT_RADIUS*3.25));

const double defenderPermittedRegion = 0.7*MaxX;

// Opps.
const Vector2D oppGoalCenter(MaxX, 0);
const Vector2D oppGoalPost_L(MaxX, 500);
const Vector2D oppGoalPost_R(MaxX, -500);
const Vector2D oppGoalCC_L(MaxX, 250);
const Vector2D oppGoalCC_R(MaxX, -250);
const Vector2D oppPenaltySpot(MaxX-1000,0);

const Vector2D ourPenaltyParallelLineCenter(oppPenaltySpot.x - 600, 0);
const Vector2D oppPenaltyParallelLineCenter(ourPenaltySpot.x + 600, 0);
//const Vector2D oppPenalty_Shoot = new Vector2D(3010, 500);

//const Vector2D MidField_R = new Vector2D((-ConstVars.ROBOT_RADIUS)*2.5, -1800);
//const Vector2D MidField_L = new Vector2D((-ConstVars.ROBOT_RADIUS)*2.5, 1800);

//const Vector2D P1(-2510, 175);
//const Vector2D P2(-2510, -175);

//public static double BALL_OBSTACLE = ROBOT_RADIUS * 2;
//public static double PASS_RADIUS = 2000;

//public static double MAX_KICKABLE_DISTANCE = ROBOT_RADIUS + 30;
//public static double MAX_KICKABLE_ANGLE = 20*System.Math.PI/180;

//public static double HEADING_ANGLE_TRESHOLD = System.Math.PI/3;
//public static double MAX_AHEAD_OPP_DISTANCE = 200;
}

#endif // CONSTANTS_H
