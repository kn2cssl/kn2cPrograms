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

float Tactic::detectKickSpeed(kickType type , bool shoot_sensor)
{
    float kickSpeed;

    if(wm->isSim)
    {
        switch (type) {
        case kickType::Shoot:
            kickSpeed = 8;
            break;
        default:
            break;
        }
    }
    else
    {
        switch (type) {
        case kickType::Shoot:
            if( shoot_sensor )
                kickSpeed = 254;
            else
                kickSpeed = 255;
            break;
        case kickType::FreeKick1:
            if( shoot_sensor )
                kickSpeed = 30;
            else
                kickSpeed = 31;
            break;
        case kickType::FreeKick2:
            if( shoot_sensor )
                kickSpeed = 100;
            else
                kickSpeed = 101;
            break;
        case kickType::FreeKick3:
            if( shoot_sensor )
                kickSpeed = 100;
            else
                kickSpeed = 101;
            break;
        case kickType::FreeKick4:
            if( shoot_sensor )
                kickSpeed = 150;
            else
                kickSpeed = 151;
            break;
        case kickType::FreeKick5:
            if( shoot_sensor )
                kickSpeed = 100;
            else
                kickSpeed = 101;
            break;
        case kickType::FreeKick6:
            if( shoot_sensor )
                kickSpeed = 100;
            else
                kickSpeed = 101;
            break;
        case kickType::FreeKick7:
            if( shoot_sensor )
                kickSpeed = 100;
            else
                kickSpeed = 101;
            break;
        case kickType::FreeKick8:
            if( shoot_sensor )
                kickSpeed = 100;
            else
                kickSpeed = 101;
            break;
        case kickType::FreeKick9:
            if( shoot_sensor )
                kickSpeed = 100;
            else
                kickSpeed = 101;
            break;
        case kickType::FreeKick10:
            if( shoot_sensor )
                kickSpeed = 100;
            else
                kickSpeed = 101;
            break;
        case kickType::FreeKick11:
            if( shoot_sensor )
                kickSpeed = 100;
            else
                kickSpeed = 101;
            break;
        case kickType::FreeKick12:
            if( shoot_sensor )
                kickSpeed = 100;
            else
                kickSpeed = 101;
            break;
        case kickType::FreeKick47:
            if( shoot_sensor )
                kickSpeed = 100;
            else
                kickSpeed = 101;
            break;
        default:
            if( shoot_sensor )
                kickSpeed = 100;
            else
                kickSpeed = 101;
            break;
        }

    }

    return kickSpeed;
}

float Tactic::detectChipSpeed(bool shoot_sensor)
{
    if( shoot_sensor )
    {
        if( wm->isSim )
            return 3;
        else
            return 254;
    }

    return 0;
}

OperatingPosition Tactic::BallControl(Vector2D Target, int Prob, int ID, double maxSpeed, int Task)
{
    /////////////////////////////////variables

    OperatingPosition OP;
    OP.useNav = true ;
    OP.ballIsObstacle = true;
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
    bool shutNonSensor=false;
    double LargeDisplacement = 40;                                        //Large displacement of ball witch will result in fault in restarts states
    double LargeSpeedChange = 0.4;
    double LongDribleDistance = 980;
    double attackAngel = AngleDeg ::deg2rad(160);
    double robotBallDist = (wm->ball.pos.loc - wm->ourRobot[ID].pos.loc).length();
    double robotBallAngele = fabs((wm->ball.pos.loc - wm->ourRobot[ID].pos.loc).dir().radian() - wm->ourRobot[ID].pos.dir);
    double possessionAngel = AngleDeg ::deg2rad(18);
    double chanceProbLimitForShoot=0.1     ;                            //percentage of probability decrese in which robot kicks the ball even if there is large err in aming ball
    double DirErr;
    double DistErr;
    double BallDir = wm->ball.vel.loc.dir().radian();                      //ball moving direction
    Vector2D BallLoc = wm->ball.pos.loc;
    double BallHS = .8;                                                     //ball speed limit for stoping it
    double FireBall = 2;                                                    //ball speed limit for sniping ;)


    double DAngel = AngleDeg ::deg2rad(100);                                 //Deviation angel witch when it is passed ,ball shuold be stoped
    Position RobotPos = wm->ourRobot[ID].pos;
    if(timer_reset==false)
    {
        f10s.restart();
        timer_reset=true;
    }

    //////////////////////////////////////////

    //////////////////////////////////////////Seize

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
        OP.useNav = false;
    }
    else if(wm->ball.vel.loc.length() < FireBall)                                                 //Seizing ball
    {
        //            double moveDir = (RobotPos.loc - BallPredict).dir().radian();
        //            DirErr = moveDir - TargetDir.dir().radian();
        //            if (DirErr > M_PI) DirErr -= 2 * M_PI;
        //            if (DirErr < -M_PI) DirErr += 2 * M_PI;
        //if(fabs(DirErr)>attackAngel)                                    //Seize and attack the ball
        //this stage has not been developed
        //        {
        //        }

        TargetDir.setLength( ROBOT_RADIUS + BALL_RADIUS*3);
        OP.pos.dir = TargetDir.dir().radian();
        OP.pos.loc = BallPredict - TargetDir;
        qDebug()<<"SeizingBall";
        //possession point check
        DirErr = AngleDeg::rad2deg(fabs(OP.pos.dir  - RobotPos.dir));
        if(DirErr > 360.0)  DirErr = 360.0 - DirErr ;

        DistErr = (OP.pos.loc - RobotPos.loc).length();
        if(DirErr < 10 && DistErr < BALL_RADIUS * 4 && wm->cmgs.gameOn()) kickPermission = true;
        if(DirErr < 9 && DistErr < BALL_RADIUS*2 ) kickPermission = true;

        if((robotBallDist>ROBOT_RADIUS + 5*BALL_RADIUS
            && robotBallAngele > possessionAngel ))
        {
            kickPermission = false;//reset
            sensorFault = 0;//reset
            startProbability = RESET;//reset
            ballDisplacement = {0,0} ;//reset
            qDebug()<<"kickperfalse";
        }
    }
    else
    {
        kickPermission = true;
        shutNonSensor = true;
        OP.useNav = false ;// OP.ballIsObstacle = false;
        OP.pos.dir = TargetDir.dir().radian();
        OP.pos.loc = BallPredict - TargetDir;
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
        {
            qDebug()<<"dribblingFault1000mm";
            dribblingFault1000mm = true;
            kickPermission=false;
        }
        if((ballDisplacement-BallLoc).length()>LargeDisplacement)
        {
            dribblingFault50mm = true;
            qDebug()<<"dribblingFault50mm";
            kickPermission=false;
        }

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

        if(wm->cmgs.gameOn())
            TargetDir.setLength( ROBOT_RADIUS- BALL_RADIUS);
        else
        {
            TargetDir.setLength( ROBOT_RADIUS- BALL_RADIUS/2);
            qDebug()<<"aiming";
        }

        OP.useNav = false ;
        OP.pos.dir = TargetDir.dir().radian();
        OP.pos.loc = BallPredict - TargetDir;

        DirErr = AngleDeg::rad2deg(fabs(OP.pos.dir  - RobotPos.dir));
        if(DirErr > 360.0)  DirErr = 360.0 - DirErr;

        DistErr = (OP.pos.loc - RobotPos.loc).length();


        if((DirErr < 4 && DistErr < 2 * ROBOT_RADIUS) || (shutNonSensor && DirErr < 9 && DistErr < 3 * ROBOT_RADIUS))
        {
            OP.readyToShoot = true ;
            shoot_sensor = true ;
            qDebug()<<"SensorShoot" ;
        }
        else
        {
            OP.readyToShoot = false;
        }


        if(DirErr < 4 && robotBallDist < ROBOT_RADIUS+BALL_RADIUS)//sensor fault checking
        {
            sensorFault++;
            qDebug()<<"ShootSensorFault:"<<ID<<"n:"<<sensorFault;
        }

        if((DirErr < 2 && robotBallDist < ROBOT_RADIUS)
                || ((sensorFault>4)
                    ||  probShoot && wm->cmgs.gameOn()
                    || (dribblingFault1000mm && wm->cmgs.gameOn())
                    || (dribblingFault50mm && !wm->cmgs.gameOn())
                    ) && DirErr < 7 && robotBallDist < ROBOT_RADIUS+BALL_RADIUS)
        {

            sensorFault=0;
            OP.readyToShoot = true;
            timer_reset=false ;
            shoot_sensor = false ;
            qDebug()<<"NONSensorShoot";

        }

        if(shutNonSensor)
        {
            OP.readyToShoot = true;
            shoot_sensor = true ;
            qDebug()<<"HellFire";
        }
    }
    else
        sensorFault=0;
    ////##kick Action

    ///////////////////////////////////////////////
    OP.shootSensor = shoot_sensor;

            //qDebug()<<"StBall!!!"<<(BallLoc - RobotPos.loc).dir().radian() <<wm->ourRobot[ID].pos.dir <<OP.pos.dir<<ID;
            qDebug()<<"StBall!!!"<<OP.useNav<<ID;

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
