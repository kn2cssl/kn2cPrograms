#include "tactickicklearning.h"

TacticKickLearning::TacticKickLearning(WorldModel *worldmodel, QObject *parent) :
    Tactic("Kick Learning", worldmodel, parent)
{
    qDebug() << "Kick Learning Intialization";
    kickIt = false;
    kickTarget = Field::oppGoalCenter;

    hillClimber = new Kick_Learning();
    hillClimber->set_worldModel(worldmodel);

    Policy default_policy;
    default_policy.set_numberOfParameters(1);
    default_policy.set_parameterAt(0,5);

    hillClimber->set_epsilon(3);
    hillClimber->set_kickTarget(Field::oppGoalCenter);

    hillClimber->set_defaultPolicy(default_policy);

    hillClimber->generate_newPolicies();
}

RobotCommand TacticKickLearning::getCommand()
{
    wm->ml_type = "Hill Climbing - Kick";

    RobotCommand rc;
    if(!wm->ourRobot[id].isValid) return rc;

    rc.maxSpeed = 1;

    rc.fin_pos.loc = Vector2D(0,0);
    rc.fin_pos.dir = 0;

    if( wm->climbing_start )
    {
        if( kickIt )
        {
            if( hillClimber->end_of_sampling() )
            {
                qDebug() << " Reward is : "<< hillClimber->get_highestScore();
                wm->climbing_status = "Reward Calc.";
                current_policy->add_reward(hillClimber->get_highestScore());
                kickIt = false;
            }
            else
            {
                wm->climbing_status = "Sampling";
                hillClimber->reward();
            }
        }
        else
        {
            rc.fin_pos.loc = Vector2D(0,0);

            int index = hillClimber->getNewPolicy();

            if( index == -1)
            {
                hillClimber->evaluate();
            }
            else
            {
                wm->climbing_status = "Kicking";
                current_policy = hillClimber-> getPolicyAt(index);
                wm->policy_index = index;
                wm->iteration_index = current_policy->get_iteration();
                if(wm->ball.pos.loc.x > 0 && wm->ball.pos.loc.x < Field::MaxX/2)
                {
                    tANDp target;
                    target.pos = kickTarget;
                    target.prob = 100;

                    OperatingPosition kick = kickForLearn(target.pos, target.prob, this->id, rc.maxSpeed,current_policy);
                    rc.fin_pos = kick.pos;
                    rc.useNav = kick.useNav;

                    if( kick.readyToShoot )
                    {
                        rc.kickspeedx = 255; //detectKickSpeed(kickType::Shoot, kick.shootSensor);
                        kickIt = true;
                    }
                }
            }
        }
    }
    rc.isBallObs = true;
    rc.isKickObs = true;

    return rc;
}

OperatingPosition TacticKickLearning::kickForLearn(Vector2D Target, int Prob, int ID, double maxSpeed, Policy* policy, int Task)
{
    /////////////////////////////////variables

    OperatingPosition OP;
    OP.useNav = true ;
    OP.ballIsObstacle = true;
    OP.readyToShoot = false;

    Vector2D BallPredict = wm->kn->PredictDestination(wm->ourRobot[ID].pos.loc,
                                                      wm->ball.pos.loc,maxSpeed,wm->ball.vel.loc);
    if(wm->ball.vel.loc.length()<.1) BallPredict = wm->ball.pos.loc;

    Vector2D  TargetDir = (Target - BallPredict);
    Vector2D ball_vel_diff;
    bool dribblingFault1000mm = false;
    bool dribblingFault50mm = false;
    bool shoot_sensor = true;
    bool probShoot=false;
    bool shutNonSensor=false;
    double LargeDisplacement = 20;                                        //Large displacement of ball witch will result in fault in restarts states
    double LargeSpeedChange = 0.4;
    double LongDribleDistance = 980;
    double attackAngel = AngleDeg ::deg2rad(160);
    double robotBallDist = (wm->ball.pos.loc - wm->ourRobot[ID].pos.loc).length();
    double robotBallAngele = fabs((wm->ball.pos.loc - wm->ourRobot[ID].pos.loc).dir().radian() - wm->ourRobot[ID].pos.dir);
    double possessionAngel = AngleDeg ::deg2rad(20);//day2
    double chanceProbLimitForShoot=0.1     ;                            //percentage of probability decrese in which robot kicks the ball even if there is large err in aming ball
    double DirErr;
    double DistErr;
    double BallDir = wm->ball.vel.loc.dir().radian();                      //ball moving direction
    Vector2D BallLoc = wm->ball.pos.loc;
    double BallHS = .8;                                                     //ball speed limit for stoping it
    double FireBall = 2;                                                    //ball speed limit for sniping ;)
    double RobotSight = (wm->ball.pos.loc - wm->ourRobot[ID].pos.loc).dir().radian();
    if (RobotSight > M_PI) RobotSight -= 2 * M_PI;
    if (RobotSight < -M_PI) RobotSight += 2 * M_PI;

    double DAngel = AngleDeg ::deg2rad(100);                                 //Deviation angel witch when it is passed ,ball shuold be stoped
    Position RobotPos = wm->ourRobot[ID].pos;
    if(timer_reset==false)
    {
        f10s.restart();
        timer_reset=true;
    }

    //////////////////////////////////////////

    //////////////////////////////////////////Seize



    //    TargetDir.setLength( ROBOT_RADIUS + BALL_RADIUS*4);
    //    OP.pos.dir = TargetDir.dir().radian();//RobotSight;//
    //    OP.pos.loc = BallPredict - TargetDir;
    //    //qDebug()<<"SeizingBall";
    //    //possession point check
    //    DirErr = AngleDeg::rad2deg(fabs(OP.pos.dir  - RobotPos.dir));
    //    if(DirErr > 360.0)  DirErr = 360.0 - DirErr ;

    //    DistErr = (OP.pos.loc - RobotPos.loc).length();
    //    if(DirErr < 8 && DistErr < BALL_RADIUS * 5 /*&& wm->cmgs.gameOn()*/) kickPermission = true;
    //    //if(DirErr < 7 && DistErr < BALL_RADIUS*4 ) kickPermission = true;

    //    if((robotBallAngele > possessionAngel ||robotBallDist>ROBOT_RADIUS + 5*BALL_RADIUS))//day2
    //    {
    //        kickPermission = false;//reset
    //        sensorFault = 0;//reset
    //        startProbability = RESET;//reset
    //        ballDisplacement = {0,0} ;//reset
    //        qDebug()<<"kickperfalse";
    //    }


    TargetDir.setLength( ROBOT_RADIUS + BALL_RADIUS*3);
    OP.pos.dir = TargetDir.dir().radian();//RobotSight;//
    OP.pos.loc = BallPredict - TargetDir;
    //qDebug()<<"SeizingBall";
    //possession point check
    DirErr = AngleDeg::rad2deg(fabs(OP.pos.dir  - RobotPos.dir));
    if(DirErr > 360.0)  DirErr = 360.0 - DirErr ;

    DistErr = (OP.pos.loc - RobotPos.loc).length();
    //    if(DirErr < 8 && DistErr < BALL_RADIUS * 5 && wm->cmgs.gameOn()) kickPermission = true;
    if(DirErr < 7 && DistErr < BALL_RADIUS*1 ) kickPermission = true;

    if((robotBallAngele > possessionAngel ||robotBallDist>ROBOT_RADIUS + 5*BALL_RADIUS))//day2
    {
        kickPermission = false;//reset
        sensorFault = 0;//reset
        startProbability = RESET;//reset
        ballDisplacement = {0,0} ;//reset
        //        qDebug()<<"kickperfalse";
    }


    ///////////////////////////////////////////////

    /////////////////////////////////////////Action

    ////#kick Action
    if(kickPermission)
    {

        ////////////////////////////////////////////////////////////
        //            if(ballDisplacement==Vector2D(0,0))
        //            {
        //                ballDisplacement=BallLoc;
        //            }
        //            if((ballDisplacement-BallLoc).length()>LongDribleDistance)
        //            {
        //                qDebug()<<"dribblingFault1000mm";
        //                dribblingFault1000mm = true;
        //                kickPermission=false;
        //            }
        //            if(((ballDisplacement-BallLoc).length()>LargeDisplacement && !wm->cmgs.gameOn()) || Task== CHIP)
        //            {
        //                dribblingFault50mm = true;
        //                qDebug()<<"dribblingFault50mm";
        //                kickPermission=false;
        //            }

        //            ////////////////////////////////////////////////////////////
        //            if(startProbability<Prob)
        //            {
        //                startProbability=Prob;
        //            }


        //            if(startProbability-Prob>startProbability*chanceProbLimitForShoot)
        //            {
        //                probShoot = true;
        //                qDebug()<<"ProbabilityShoot";
        //            }

        ////////////////////////////////////////////////////////////
        ball_vel_diff =wm->ball.vel.loc - last_ball_vell;
        last_ball_vell = wm->ball.vel.loc ;
        //qDebug()<<f10s.elapsed();

        //control point >>navigation : OFF

        //            if(wm->cmgs.gameOn() || Task == CHIP)
        TargetDir.setLength( ROBOT_RADIUS- BALL_RADIUS*1.5);
        //            else
        //            {
        //                TargetDir.setLength( ROBOT_RADIUS- BALL_RADIUS/2);
        //                qDebug()<<"aiming";
        //            }

        OP.useNav = false ;
        OP.pos.dir = TargetDir.dir().radian();
        OP.pos.loc = BallPredict - TargetDir;

        DirErr = AngleDeg::rad2deg(fabs(OP.pos.dir  - RobotPos.dir));
        if(DirErr > 360.0)  DirErr = 360.0 - DirErr;

        DistErr = (OP.pos.loc - RobotPos.loc).length();


        //        if((DirErr < 4 && DistErr < 2 * ROBOT_RADIUS) || (shutNonSensor && DirErr < 9 && DistErr < 3 * ROBOT_RADIUS))
        //        {
        //            OP.readyToShoot = true ;
        //            shoot_sensor = true ;
        //            qDebug()<<"SensorShoot" ;
        //        }
        //        else
        //        {
        //            OP.readyToShoot = false;
        //        }


        //            if(DirErr < 5 && robotBallDist < ROBOT_RADIUS+BALL_RADIUS*2)//sensor fault checking
        //            {
        //                sensorFault++;
        //                qDebug()<<"ShootSensorFault:"<<ID<<"n:"<<sensorFault;
        //            }

        qDebug()<<"------------------------------";
        qDebug()<<"DirErr when ready for kick : "<<DirErr;
        qDebug()<<"DistErr when ready for kick : "<<DistErr;

        if(/*(DirErr < 2 && robotBallDist < ROBOT_RADIUS)
                                                   /* || (((sensorFault>8)//day2//(sensorFault>10)
                                                        ||  (probShoot && wm->cmgs.gameOn())
                                                        || (dribblingFault1000mm && wm->cmgs.gameOn())
                                                        || (dribblingFault50mm && !wm->cmgs.gameOn())
                                                        ) && */DirErr < current_policy->get_parameterAt(0) && robotBallDist < ROBOT_RADIUS+BALL_RADIUS)//)
        {

            sensorFault=0;
            OP.readyToShoot = true;
            timer_reset=false ;
            shoot_sensor = false ;
            qDebug()<<"Kick It";

        }

    }
    else
        sensorFault=0;
    ////##kick Action

    ///////////////////////////////////////////////
    OP.shootSensor = shoot_sensor;

    //qDebug()<<"StBall!!!"<<(BallLoc - RobotPos.loc).dir().radian() <<wm->ourRobot[ID].pos.dir <<OP.pos.dir<<ID;
    //qDebug()<<"StBall!!!"<<OP.useNav<<ID;

    return OP;
}
