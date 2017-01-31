#include "constants.h"

namespace Field
{
double MaxX;
double MinX;
double MaxY;
double MinY;

double GoalDeep;

Vector2D upperLeftCorner;
Vector2D upperRightCorner;
Vector2D bottomLeftCorner;
Vector2D bottomRightCorner;

Line2D leftLine(Vector2D(0,0), Vector2D(0, 0));
Line2D midLine(Vector2D(0,0), Vector2D(0, 0));
Line2D rightLine(Vector2D(0,0), Vector2D(0, 0));

Line2D upLine(Vector2D(0,0), Vector2D(0, 0));
Line2D bottomLine(Vector2D(0,0), Vector2D(0, 0));

double centerCircle_R, goalCircle_R, goalCircleEX_R, goalCircleDEF_R;

// Ours.
Vector2D ourGoalCenter, ourGoalPost_L, ourGoalPost_R;
double defenceLineLinear;
Vector2D defenceLineLinear_L, defenceLineLinear_R;
Vector2D ourPenaltySpot;

Vector2D ourDefPost_L, ourDefPost_R;

Circle2D ourDefenceCircle;

double defenderPermittedRegion;

// Opps.
Vector2D oppGoalCenter, oppGoalPost_L, oppGoalPost_R;
Vector2D oppGoalCC_L,oppGoalCC_R;
Vector2D oppPenaltySpot;

Vector2D ourPenaltyParallelLineCenter;
Vector2D oppPenaltyParallelLineCenter;
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

void setup_consts(QString field_size)
{
    if( field_size == "Double")
    {
        MaxX = 4500;
        MinX = -4500;
        MaxY = 3000;
        MinY = -3000;

        GoalDeep = 180;

        upperLeftCorner = Vector2D(MinX + 125, MaxY - 125);
        upperRightCorner = Vector2D(MaxX - 125, MaxY - 125);
        bottomLeftCorner = Vector2D(MinX + 125, MinY + 125);
        bottomRightCorner = Vector2D(MaxX - 125, MinY + 125);

        leftLine = Line2D(Vector2D(MinX,MinY), Vector2D(MinX, MaxY));
        midLine = Line2D(Vector2D(0,MinY), Vector2D(0, MaxY));
        rightLine = Line2D(Vector2D(MaxX, MinY), Vector2D(MaxX, MaxY));

        upLine = Line2D(Vector2D(MinX, MaxY), Vector2D(MaxX, MaxY));
        bottomLine = Line2D(Vector2D(MinX, MinY), Vector2D(MaxX, MinY));

        centerCircle_R = 500;
        goalCircle_R = 1000;
        goalCircleEX_R = 600 + 3*ROBOT_RADIUS + 20;
        goalCircleDEF_R = goalCircle_R + centerCircle_R/2 + 200;

        // Ours.
        //armin sadreddin
        ourGoalCenter = Vector2D(MinX, 0);
        ourGoalPost_L = Vector2D(MinX, 500);
        ourGoalPost_R = Vector2D(MinX, -500);
        defenceLineLinear = 500;
        defenceLineLinear_L = Vector2D(MinX, 250);
        defenceLineLinear_R = Vector2D(MinX, -250);
        ourPenaltySpot = Vector2D(MinX+1000,0);

        ourDefPost_L = Vector2D(MinX, 1300);
        ourDefPost_R = Vector2D(MinX, -1300);

        ourDefenceCircle = Circle2D(ourGoalCenter,750+(ROBOT_RADIUS*3.25));

        defenderPermittedRegion = 0.7*MaxX;

        // Opps.
        oppGoalCenter = Vector2D(MaxX, 0);
        oppGoalPost_L = Vector2D(MaxX, 500);
        oppGoalPost_R = Vector2D(MaxX, -500);
        oppGoalCC_L = Vector2D(MaxX, 250);
        oppGoalCC_R = Vector2D(MaxX, -250);
        oppPenaltySpot = Vector2D(MaxX-1000,0);

        ourPenaltyParallelLineCenter = Vector2D(oppPenaltySpot.x - 600, 0);
        oppPenaltyParallelLineCenter = Vector2D(ourPenaltySpot.x + 600, 0);
    }
    else
    {
        MaxX = 3025;
        MinX = -3025;
        MaxY = 2025;
        MinY = -2025;

        GoalDeep = 180;

        upperLeftCorner = Vector2D(MinX + 125, MaxY - 125);
        upperRightCorner = Vector2D(MaxX - 125, MaxY - 125);
        bottomLeftCorner = Vector2D(MinX + 125, MinY + 125);
        bottomRightCorner = Vector2D(MaxX - 125, MinY + 125);

        leftLine = Line2D(Vector2D(MinX,MinY), Vector2D(MinX, MaxY));
        midLine = Line2D(Vector2D(0,MinY), Vector2D(0, MaxY));
        rightLine = Line2D(Vector2D(MaxX, MinY), Vector2D(MaxX, MaxY));

        upLine = Line2D(Vector2D(MinX, MaxY), Vector2D(MaxX, MaxY));
        bottomLine = Line2D(Vector2D(MinX, MinY), Vector2D(MaxX, MinY));

        centerCircle_R = 500;
        goalCircle_R = 800;
        goalCircleEX_R = 600 + 3*ROBOT_RADIUS + 20;
        goalCircleDEF_R = goalCircleEX_R + 400;

        // Ours.
        ourGoalCenter = Vector2D(MinX, 0);
        ourGoalPost_L = Vector2D(MinX, 350);
        ourGoalPost_R = Vector2D(MinX, -350);
        defenceLineLinear = 350;
        defenceLineLinear_L = Vector2D(MinX, 175);
        defenceLineLinear_R = Vector2D(MinX, -175);
        ourPenaltySpot = Vector2D(MinX+750,0);

        ourDefPost_L = Vector2D(MinX, 975);
        ourDefPost_R = Vector2D(MinX, -975);

        ourDefenceCircle = Circle2D(ourGoalCenter,750+(ROBOT_RADIUS*3.25));

        defenderPermittedRegion = 0.7*MaxX;

        // Opps.
        oppGoalCenter = Vector2D(MaxX, 0);
        oppGoalPost_L = Vector2D(MaxX, 350);
        oppGoalPost_R = Vector2D(MaxX, -350);
        oppGoalCC_L = Vector2D(MaxX, 175);
        oppGoalCC_R = Vector2D(MaxX, -175);
        oppPenaltySpot = Vector2D(MaxX-750,0);

        ourPenaltyParallelLineCenter = Vector2D(oppPenaltySpot.x-500,0);
        oppPenaltyParallelLineCenter = Vector2D(ourGoalCenter.x+750+600,0);
    }
}
}
