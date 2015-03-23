#include "tactic.h"

Tactic::Tactic(QString name, WorldModel *worldmodel, QObject *parent) :
    QObject(parent),
    name(name)
{
    wm = worldmodel;
    id = -1;
    kickPermission=false;
}

QString Tactic::getName()
{
    if(param.size() > 0)
        return name + " => " + param;
    else
        return name;
}

float Tactic::detectKickSpeed( Vector2D dest )
{
    float kickSpeed;

    Segment2D goalLine(Field::oppGoalPost_L,Field::oppGoalPost_R);

    if(wm->isSim)
    {
        if( goalLine.contains(dest) )
            kickSpeed = 8; //Should Changed
        else
            kickSpeed = 4;//Should Changed
    }
    else
    {
        if( goalLine.contains(dest) )
            kickSpeed = 255; //Should Changed
        else
            kickSpeed = 101;//Should Changed
    }

    return kickSpeed;
}

OperatingPosition Tactic::BallControl(Vector2D Target, int Prob, int ID, double maxSpeed, int Task)
{
    /////////////////////////////////variables

    OperatingPosition OP;
    OP.useNav = true ;
    OP.kickSpeed = 0;
    OP.readyToShoot = false;

    Vector2D BallPredict = wm->kn->PredictDestination(wm->ourRobot[ID].pos.loc,
                                              wm->ball.pos.loc,maxSpeed,wm->ball.vel.loc);
    if(wm->ball.vel.loc.length()<.1) BallPredict = wm->ball.pos.loc;

    Vector2D  TargetDir= (Target - BallPredict);
    Vector2D ball_vel_diff;
    bool dribblingFault1000mm = false;
    bool dribblingFault50mm = false;
    bool shoot_sensor = true;
    bool probShoot=false;
    double LargeDisplacement = 40;                                        //Large displacement of ball witch will result in fault in restarts states
    double LargeSpeedChange = 0.04;
    double LongDribleDistance = 980;
    double attackAngel = AngleDeg ::deg2rad(160);
    double robotBallDist = (wm->ball.pos.loc - wm->ourRobot[ID].pos.loc).length();
    double robotBallAngele = fabs((wm->ball.pos.loc - wm->ourRobot[ID].pos.loc).dir().radian());
    double possessionAngel = AngleDeg ::deg2rad(15);
    double chanceProbLimitForShoot=0.1     ;                            //percentage of probability decrese in which robot kicks the ball even if there is large err in aming ball
    double DirErr;
    double DistErr;
    double BallDir = wm->ball.vel.loc.dir().radian();                      //ball moving direction
    Vector2D BallLoc = wm->ball.pos.loc;
    double BallHS = .2;                                                     //ball speed limit for stoping it
    double DAngel = AngleDeg ::deg2rad(80);                                 //Deviation angel witch when it is passed ,ball shuold be stoped
    Position RobotPos = wm->ourRobot[ID].pos;
    if(timer_reset==false)
    {
        f10s.restart();
        timer_reset=true;
    }

    //////////////////////////////////////////

    //////////////////////////////////////////Seize
    int SeizeMode=0;

    if(wm->ball.vel.loc.length()>BallHS
            && (TargetDir.dir().radian()-DAngel)<BallDir
            && (-TargetDir.dir().radian()+DAngel)>BallDir
            && wm->cmgs.gameOn())                       //stop the  ball
    {
        OP.pos.dir = (BallLoc - RobotPos.loc).dir().radian();//(BallDir)-M_PI;//
        if (OP.pos.dir > M_PI) OP.pos.dir -= 2 * M_PI;
        if (OP.pos.dir < -M_PI) OP.pos.dir += 2 * M_PI;
        qDebug()<<"StopingBall";
        OP.pos.loc = BallPredict ;
        SeizeMode=1;
    }
    else                                                 //Seizing ball
    {
        //            double moveDir = (RobotPos.loc - BallPredict).dir().radian();
        //            DirErr = moveDir - TargetDir.dir().radian();
        //            if (DirErr > M_PI) DirErr -= 2 * M_PI;
        //            if (DirErr < -M_PI) DirErr += 2 * M_PI;
        //if(fabs(DirErr)>attackAngel)                                    //Seize and attack the ball
        //this stage has not been developed
        //        {
        //        }
        //possession point >>navigation : ON
        TargetDir.setLength( ROBOT_RADIUS + BALL_RADIUS*2);

        OP.pos.dir = TargetDir.dir().radian();
        OP.pos.loc = BallPredict - TargetDir;

        //possession point check
        DirErr = AngleDeg::rad2deg(fabs(OP.pos.dir  - RobotPos.dir));
        if(DirErr > 360.0)  DirErr = 360.0 - DirErr ;

        DistErr = (OP.pos.loc - RobotPos.loc).length();
        if(DirErr < 10 && DistErr < BALL_RADIUS*2 && wm->cmgs.gameOn()) kickPermission = true;
        if(DirErr < 10 && DistErr < BALL_RADIUS ) kickPermission = true;

        if(DirErr > 19 && DistErr > BALL_RADIUS*3
                && (robotBallDist>ROBOT_RADIUS+BALL_RADIUS
                    && robotBallAngele>possessionAngel ))
        {
            kickPermission = false;//reset
            sensorFault = 0;//reset
            startProbability = RESET;//reset
            ballDisplacement = {0,0} ;//reset
        }


        // qDebug()<<robotBallDist<<ROBOT_RADIUS+BALL_RADIUS<<robotBallAngele<<possessionAngel;

    }
    ///////////////////////////////////////////////

    /////////////////////////////////////////Action

    ////#kick Action
    if(kickPermission)
    {
        ////////////////////////////////////////////////////////////
        if(ballDisplacement==Vector2D(0,0))
        {
            ballDisplacement=BallLoc;
        }
        if((ballDisplacement-BallLoc).length()>LongDribleDistance)
            dribblingFault1000mm = true;
        if((ballDisplacement-BallLoc).length()>LargeDisplacement)
            dribblingFault50mm = true;
        ////////////////////////////////////////////////////////////
        if(startProbability<Prob)
        {
            startProbability=Prob;
        }


        if(startProbability-Prob>startProbability*chanceProbLimitForShoot)
        {
            probShoot = true;
            qDebug()<<"ProbabilityShoot";
        }

        ////////////////////////////////////////////////////////////
        ball_vel_diff =wm->ball.vel.loc - last_ball_vell;
        last_ball_vell = wm->ball.vel.loc ;
        //qDebug()<<f10s.elapsed();

        //control point >>navigation : OFF

        if(wm->cmgs.gameOn() || Task == SHOOT)
            TargetDir.setLength( ROBOT_RADIUS- BALL_RADIUS);
        else if(Task == AIM)
            TargetDir.setLength( ROBOT_RADIUS+ BALL_RADIUS*2);
        OP.useNav = false ;
        OP.pos.dir = TargetDir.dir().radian();
        OP.pos.loc = BallPredict - TargetDir;

        DirErr = AngleDeg::rad2deg(fabs(OP.pos.dir  - RobotPos.dir));
        if(DirErr > 360.0)  DirErr = 360.0 - DirErr ;

        DistErr = (OP.pos.loc - RobotPos.loc).length();


        if(DirErr < 3 && DistErr < 2*ROBOT_RADIUS)
        {
            OP.readyToShoot = true;
            shoot_sensor = true;
            qDebug()<<"SensorShoot";
        }
        else
        {
            OP.readyToShoot = false;
        }


        if(DirErr < 4 && robotBallDist < ROBOT_RADIUS+BALL_RADIUS)//sensor fault checking
        {
            sensorFault++;
            qDebug()<<"ShootSensorFault:"<<ID;
        }

        if((DirErr < 1 && robotBallDist < ROBOT_RADIUS)
                || sensorFault>4
                || (probShoot && wm->cmgs.gameOn() && DirErr < 15 && robotBallDist < 1.2*ROBOT_RADIUS)
                || (dribblingFault1000mm && wm->cmgs.gameOn())
                || (dribblingFault50mm && !wm->cmgs.gameOn())
                )
        {
            sensorFault=0;
            OP.readyToShoot = true;
            timer_reset=false;
            shoot_sensor = false;
            qDebug()<<"NONSensorShoot";
        }
    }
    else
        sensorFault=0;
    ////##kick Action

    ///////////////////////////////////////////////

    if(shoot_sensor)//shooting with sensor or without it
    {
        OP.kickSpeed=256;
    }
    else
    {
        OP.kickSpeed=255;
    }

    if(!wm->ball.isValid)
        OP.kickSpeed=0;



    return OP;
}

void Tactic::setID(int id)
{
    this->id = id;
}

int Tactic::getID()
{
    return this->id;
}

tANDp Tactic::findTarget()
{
    tANDp out;
    out.prob = 0;
    if (!wm->ball.isValid) return out;
    wm->TANDPis.clear();


    int dist_Clearance = 00 ; // 3 cm for opp Robot Reaction displacement
    for(int jj=-10;jj<11;jj++)
    {
        int prob=100;
        Vector2D Point;
        Point.x = Field::oppGoalCenter.x;
        Point.y = Field::oppGoalCenter.y + jj*(Field::oppGoalPost_L.y/10);
        tANDp tp;
        tp.pos=Point;
        int min_prob = 100;
        for(int ii=0;ii<12;ii++)
        {
            if(wm->oppRobot[ii].isValid)
            {
                if(wm->oppRobot[ii].pos.loc.x > wm->ball.pos.loc.x-500)
                {
                    Segment2D ball2Point(wm->ball.pos.loc,Point);
                    double dist2R = ball2Point.dist(wm->oppRobot[ii].pos.loc);
                    if (dist2R < (ROBOT_RADIUS + BALL_RADIUS + dist_Clearance) ) prob=0;
                    else if (dist2R < 1000 ) prob = dist2R/10;
                    else prob = 100;
                    if(prob < min_prob) min_prob = prob;
                }
            }

            min_prob=min_prob-abs(jj);
            if(min_prob < 0) min_prob=0;
            if(min_prob == 0) break;
        }
        tp.prob=min_prob;
        wm->TANDPis.push_back(tp);
    }

    out = wm->TANDPis.at(0);
    for(int i=1;i<wm->TANDPis.size();i++)
    {
        if( out.prob < wm->TANDPis.at(i).prob)
            out = wm->TANDPis.at(i);
    }
    wm->max_TANDPis = out;
    return out;
}

void Tactic::setPlayerToKeep(int index)
{
    this->playerToKeep = index;
}
