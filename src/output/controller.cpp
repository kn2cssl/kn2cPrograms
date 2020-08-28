﻿#include "controller.h"
#include "constants.h"
#include "math.h"

#define ROBOTRADIUS 0.090
#define SpeedToRPMR 5000
#define SpeedToRPM 1375.14
Controller::Controller(QObject *parent) :
    QObject(parent)
  ,out("/home/kn2c/Desktop/Untitled Folder/Data.txt")
{

    qDebug() << "Controller Initialization...";

    timer.start();

    err0 = {0,0};
    err1 = {0,0};
    u1 = {0,0};
    derived0 = {0,0};
    derived1 = {0,0};
    integral = {0,0};

    wu1 = 0;
    wu1_last = 0;
    wintegral = 0;
    werr0 = 0;
    werr1 = 0;
    wderived0 = 0;
    wderived1 = 0;

    stateCTRL = 0;

    LinearSpeed = {0,0};
    LinearSpeed_past = {0,0};

}

ControllerResult Controller::calc(ControllerInput &ci)
{
    ControllerResult ctrlresult;
    double time = timer.elapsed();
    timer.restart();
    ctrlresult.rs = calcRobotSpeed_main(ci);
    //ctrlresult.rs = calcRobotSpeed_adjt(ci);
    //ctrlresult.rs = calcRobotSpeed_test(ci);
    //qDebug() << "id" << ci.id << "timer" << time;

   // ctrlresult.msR = calcReal(ctrlresult.rs);
    ctrlresult.msS = calcSimul(ctrlresult.rs,ci);
    return ctrlresult;
}

RobotSpeed Controller::calcRobotSpeed_main(ControllerInput &ci)
{
    RobotSpeed setpoint;
    Vector2D speed_sp;

    double werr;
    Vector2D err;


//    //! Test
//    if(fabs(Vector2D(ci.cur_pos.loc-Vector2D( 2400,-2000)).r()) < 1000 )
//    //if(ci.cur_pos.loc.x > -1000)
//    wu1=0;
//    if(fabs(Vector2D(ci.cur_pos.loc-Vector2D( 2400, 2000)).r()) < 1000 )
//    //if(ci.cur_pos.loc.x < -3800)
//    wu1=1;


//    ci.mid_pos.loc.x = 2400;
//    ci.mid_pos.dir = M_PI;


//    if(wu1==0)
//              ci.mid_pos.loc.y =  2860;
//            //setpoint.VX =  -2;
//        else
//            //setpoint.VX =  2;
//              ci.mid_pos.loc.y =  -2860;
//    //! test



    err = (ci.mid_pos.loc - ci.cur_pos.loc);
    if(fabs(err.r()) < 5 ) err = {0,0};
    if(fabs(err.r()) < 500 ) ci.fin_pos.dir = (ci.mid_pos.loc - ci.cur_pos.loc).dir().radian() + M_PI_2;

    werr = (ci.mid_pos.dir - ci.cur_pos.dir);
    if(fabs(werr) > M_PI) werr = werr - sign(werr)*M_2PI;
    if(fabs(werr) < 0.07 ) werr = 0;



    /**
     * @brief PID controller based on pure err of distance
     */
        /////////////////////////////////////////////////////////////////////////////////

        double wkp=1.9,wki_pos=0.18,wki_neg=.2,wkd = 0.1,wki=.01;
        double wa_max = 2;
        //* finding useful vector of previous setpoint
/*        if ( wi * werr < 0)
//        {
//            wi = 0;
//        }
//        //#

//        if((pow(ci.cur_vel.dir,2)/2/wa_max > fabs(werr) )&& (wi * werr > 0 ))
//        {

//            wi= wi - wki_neg*sign(werr);
//            if(fabs(wi) < 0 ) wi=0;

//        }
//        else
//        {
//            wi = wi + wki_pos*sign(werr);
//            int wmaxSpeed = 20;
//            if(fabs(wi) > wmaxSpeed ) wi = fabs(wi)/wi*20;

//        }

//        wd = (ci.cur_vel.dir - ci.last_vel.dir - wd) *.1 + wd ;
//        float wi_err = wi - ci.cur_vel.dir ;
//        wkp = 1.2;
//        wp = wi_err * wkp;
*/
        wp = werr * wkp;
        if (fabs(wp) > 10) wp = sign(wp) * 10;
        qDebug() <<wp;

//        wi = werr * wki + wi;
//        if (fabs(wi) > 1) wi = sign(wi) * 1;
//        wd = (ci.cur_vel.dir - ci.last_vel.dir - wd) *.1 + wd ;
//        if (fabs(wd) > 3) wd = sign(wd) * 3;

        setpoint.VW =  wp  + wi  - wd * wkd ;
////qDebug() <<setpoint.VW*1000<<ci.cur_vel.dir<<wi<<wp<<wi_err;

/////////   linear potion profile
       double kp=0.000,ki_pos=0.03,ki_neg=0.06,kd = 0.01;
       double a_max = 0.002; double a_max_c = 0.001;
       if(fabs(err.r()) < 700 ) ki_pos=0.2;
       double ki = 0.0001;
       //* finding useful vector of previous setpoint
       double err_angel = atan2(err.y,err.x);
       double i_angel =atan2(i.y,i.x);
       double diff = cos(err_angel - i_angel);
       if ( diff > 0)
       {
           i.setLength(i.length() * diff );
           i.setDir(atan2(err.y,err.x)*180/M_PI );
       }
       else
       {
           i = i.setLength(0);
       }
       //#

       //* it keeps setpoint small till robot can't compensate its err
//       if( 2 < (i-ci.cur_vel.loc).length())
//       {
//           fault_counter ++ ;
//           if(fault_counter > 20)
//           {
//               fault_counter = 0 ;
//               i.setLength(2);
//               qDebug() <<"aaa";
//           }

//       }
       //#
       err_angel = atan2(err.y,err.x);
       i_angel =atan2(ci.cur_vel.loc.y,ci.cur_vel.loc.x);
       diff = cos(err_angel - i_angel);
       if( ( fabs( ci.cur_vel.loc.r2()/2/a_max )> fabs(err.r()) ) && (diff > 0))
       {
           i= i - err.setLength(ki_neg);
           if(fabs(i.length()) < 0 ) i=i.setLength(0);

       }
       else
       {
//           ci.maxSpeed = 4 ;
           if( fabs( i.r2()/2/a_max_c )< fabs(err.r()) )
           i = i + err.setLength(ki_pos);
           if(fabs(i.length()) > ci.maxSpeed ) i=i.setLength(ci.maxSpeed);

       }


       Vector2D i_err = i - ci.cur_vel.loc ;

       p = i_err * kp;
       i_near = i_near +  i_err * ki;

        err_angel = atan2(i.y,i.x);
        i_angel =atan2(i_near.y,i_near.x);
        diff = cos(err_angel - i_angel);
       if ( diff > 0)
       {
           i_near.setLength(i_near.length() * diff );
           i_near.setDir(atan2(i.y,i.x)*180/M_PI );
       }
       else
       {
           i_near = i_near.setLength(0);
       }


       speed_sp = p + i_near +i+ d * kd;

//       if(ci.id==7)
//           qDebug() <<"aaaaaaaaaaaaaaa"<<i.r()<<ci.cur_vel.loc.r();

       setpoint.VX =  speed_sp.x;
       setpoint.VY =  speed_sp.y;




       ci.last_vel = ci.cur_vel;
//    setpoint.VX=0;
//    setpoint.VY=0;
//    setpoint.VW=0;
    return setpoint;
}



MotorSpeed Controller::calcSimul(RobotSpeed rs, ControllerInput &ci)
{
    double motor[4][1],rotate[4][3],speed[3][1];

    Vector2D RotLinearSpeed;
    RotLinearSpeed.x = rs.VX * cos(ci.cur_pos.dir) + rs.VY * sin(ci.cur_pos.dir);
    RotLinearSpeed.y = -rs.VX * sin(ci.cur_pos.dir) + rs.VY * cos(ci.cur_pos.dir);

    speed[0][0] = RotLinearSpeed.x/10;
    speed[1][0] = RotLinearSpeed.y/10;
    speed[2][0] = rs.VW/10;

    rotate[0][0] = sin(M_PI / 3);//-sin(rangle - M_PI / 3);
    rotate[1][0] = sin(3 * M_PI / 4);//-sin(rangle + M_PI / 3);
    rotate[2][0] = sin(5 * M_PI / 4);//-sin(rangle + M_PI);
    rotate[3][0] = sin(5 * M_PI / 3);//-sin(rangle + M_PI);
    rotate[0][1] = -cos(M_PI / 3);//cos(rangle - M_PI / 3);
    rotate[1][1] = -cos(3 * M_PI / 4);//cos(rangle + M_PI / 3);
    rotate[2][1] = -cos(5 * M_PI / 4);//cos(rangle + M_PI);
    rotate[3][1] = -cos(5 * M_PI / 3);//cos(rangle + M_PI);
    rotate[0][2] = -ROBOTRADIUS;
    rotate[1][2] = -ROBOTRADIUS;
    rotate[2][2] = -ROBOTRADIUS;
    rotate[3][2] = -ROBOTRADIUS;

    motor[0][0] = (rotate[0][0] * speed[0][0] + rotate[0][1] * speed[1][0] + rotate[0][2] * speed[2][0])*100;
    motor[1][0] = (rotate[1][0] * speed[0][0] + rotate[1][1] * speed[1][0] + rotate[1][2] * speed[2][0])*100;
    motor[2][0] = (rotate[2][0] * speed[0][0] + rotate[2][1] * speed[1][0] + rotate[2][2] * speed[2][0])*100;
    motor[3][0] = (rotate[3][0] * speed[0][0] + rotate[3][1] * speed[1][0] + rotate[3][2] * speed[2][0])*100;

    //qDebug()<<"M0:"<<motor[0][0]<<"M1:"<<motor[1][0]<<"M2:"<<motor[2][0]<<"M3:"<<motor[3][0];
    //qDebug()<<err1.y;
    //out << err1.y <<" "<< endl;
    MotorSpeed result;

    result.M0 = -motor[0][0]/100;//*SpeedToRPM;//
    result.M1 = -motor[1][0]/100;//*SpeedToRPM;//
    result.M2 = -motor[2][0]/100;//*SpeedToRPM;//
    result.M3 = -motor[3][0]/100;//*SpeedToRPM;//

    return result;
}
