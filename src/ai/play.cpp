#include "play.h"

Play::Play(QString name, WorldModel *worldmodel, QObject *parent) :
    QObject(parent),
    name(name)
{
    wm = worldmodel;
    for(int i=0; i<PLAYERS_MAX_NUM; i++)
        tactics[i] = NULL;

    numberOfDef = NUMOFDEFENDERS;

    rolesIsInit = false;
}

QString Play::getName()
{
    if(param.size() > 0)
        return name + " => " + param;
    else
        return name;
}

Tactic* Play::getTactic(int id)
{
    if(id >= PLAYERS_MAX_NUM || id < 0) return NULL;
    return tactics[id];
}

bool Play::conditionChanged()
{
    bool out;
    QList<int> activeAgents=wm->kn->ActiveAgents();
    if(activeAgents.size() != numberOfPlayers)
    {
        numberOfPlayers = activeAgents.size();
        out = false;
    }
    return out;
}

void Play::zonePositions(int leftID, int RightID, Position &goalie, Position &left, Position &right)
{
    goalie.loc = Vector2D(Field::MinX,0);

    if( wm->cmgs.theirPenaltyKick() )
    {
        //        center.loc = Field::oppPenaltyParallelLineCenter;

        right.loc = Field::oppPenaltyParallelLineCenter;
        right.loc.y = Field::oppPenaltyParallelLineCenter.y - (Field::MaxY*0.5);

        left.loc.x = Field::oppPenaltyParallelLineCenter.x;
        left.loc.y = Field::oppPenaltyParallelLineCenter.y + (Field::MaxY*0.5);
    }
    else if( wm->kn->IsInsideGolieArea(wm->ball.pos.loc) && (!wm->cmgs.canKickBall()) )
    {
        right.loc.x = Field::ourGoalCenter.x + 800;
        right.loc.y = Field::ourGoalCenter.y - 350;

        left.loc.x = Field::ourGoalCenter.x + 800;
        left.loc.y = Field::ourGoalCenter.y + 350;
    }
    else
    {
        double ballDeg,beta,teta,alpha=356,gama;
        double dtgc;//distanceToGoldanCenter
        double dtgc2;
        double ballDistance;//ballDistanceToGoalCenter

        //Geometric calculations
        ballDeg = (wm->ball.pos.loc - Field::ourGoalCenter).dir().radian();

        if(ballDeg>75.0*3.14/180)
        {
            ballDeg=75.0*3.14/180;
        }

        if(ballDeg<-75.0*3.14/180)
        {
            ballDeg=-75.0*3.14/180;
        }

        gama=AngleDeg::PI/2.0-abs(ballDeg);
        beta=asin((float)(Field::defenceLineLinear)*sin(gama)/(2.0*(Field::goalCircle_R+ROBOT_RADIUS)));
        alpha=atan((float)(Field::defenceLineLinear/2)/(Field::goalCircle_R+ROBOT_RADIUS));
        dtgc=(float)(Field::goalCircleEX_R)*sin(AngleDeg::PI-gama-beta)/sin(gama);
        dtgc2=sqrt(dtgc*dtgc+(float)(2*ROBOT_RADIUS+10)*(float)(2*ROBOT_RADIUS+10));
        teta=atan((float)(2*ROBOT_RADIUS+10)/dtgc);
        ballDistance=pow((pow(wm->ball.pos.loc.x+(float)(Field::MaxX),2)+pow(wm->ball.pos.loc.y,2)),0.5);

        //        if(abs(ballDeg)<alpha)
        //        {
        //            Center.dir=ballDeg;
        //            Center.loc=Vector2D(-(float)(Field::MaxX)+Field::goalCircle_R+ROBOT_RADIUS,0.0+tan(ballDeg)*(Field::goalCircle_R+ROBOT_RADIUS));
        //        }

        //        else
        //        {
        //            Center.dir=ballDeg;
        //            Center.loc={-(float)(Field::MaxX)+cos(ballDeg)*dtgc,0.0+sin(ballDeg)*dtgc};
        //        }

        left.dir=ballDeg;
        left.loc={-(float)(Field::MaxX)+cos(ballDeg+teta)*dtgc2,0.0+sin(ballDeg+teta)*dtgc2};
        if(dtgc+2*ROBOT_RADIUS<ballDistance && ballDistance<dtgc+4*ROBOT_RADIUS && wm->ball.pos.loc.y>0)
        {
            if(!wm->kn->ReachedToPos(wm->ourRobot[leftID].pos, left, 30, 180))
            {
                left.loc= {wm->ball.pos.loc.x-110*cos(ballDeg),wm->ball.pos.loc.y-110*sin(ballDeg)};
                left.dir=ballDeg;
            }

            if(wm->kn->ReachedToPos(wm->ourRobot[leftID].pos, left, 20, 4))
            {

                if(!wm->kn->ReachedToPos(wm->ourRobot[leftID].pos, left, 20, 2))
                {
                    left.dir=ballDeg;
                }
                left.loc= {wm->ball.pos.loc.x-100*cos(ballDeg),wm->ball.pos.loc.y-100*sin(ballDeg)};
            }

        }

        right.dir=ballDeg;
        right.loc={-(float)(Field::MaxX)+cos(ballDeg-teta)*dtgc2,0.0+sin(ballDeg-teta)*dtgc2};
        if(dtgc+2*ROBOT_RADIUS<ballDistance && ballDistance<dtgc+4*ROBOT_RADIUS && wm->ball.pos.loc.y<0)
        {
            if(!wm->kn->ReachedToPos(wm->ourRobot[RightID].pos, right, 30, 180))
            {
                right.loc= {wm->ball.pos.loc.x-110*cos(ballDeg),wm->ball.pos.loc.y-110*sin(ballDeg)};
                right.dir=ballDeg;
            }

            if(wm->kn->ReachedToPos(wm->ourRobot[RightID].pos, right, 20, 4))
            {

                if(!wm->kn->ReachedToPos(wm->ourRobot[RightID].pos, right, 20, 2))
                {
                    right.dir=ballDeg;
                }
                right.loc= {wm->ball.pos.loc.x-100*cos(ballDeg),wm->ball.pos.loc.y-100*sin(ballDeg)};
            }
        }

    }
}
