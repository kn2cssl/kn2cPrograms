#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "controller_struct.h"
#include <fstream>
#include "QDebug"
#include <QTimer>

using namespace std;

class Controller : public QObject
{
    Q_OBJECT

public:
    explicit Controller(QObject *parent = 0);
    ControllerResult calc(ControllerInput &ci);

private:
    QTime timer;

    RobotSpeed calcRobotSpeed_main(ControllerInput &ci);
    RobotSpeed calcRobotSpeed_adjt(ControllerInput &ci);
    RobotSpeed calcRobotSpeed_test(ControllerInput &ci);

    MotorSpeed calcReal(RobotSpeed rs);
    MotorSpeed calcSimul(RobotSpeed rs);

private:

    Vector2D err0,err1;
    Vector2D u1;
    Vector2D derived0,derived1;
    Vector2D integral;
    Vector2D last_setpoint ;
    //kamin
    Vector2D LinearSpeed;
    Vector2D LinearSpeed_past;



    //kamout

//      shahin
//    float t,ts,t1,tss;
//    float a=0.05;
//    QTimer* sh_timer;
//    char flag;

    //float distanse,aR;

    //float flag=1;

    //float a=0.05,t,t1,t2,t3,tt,delta1,delta2,delta3,deltat,flag=0,flags=0;
    QTimer* sh_timer;

    float a1=0.1;
    float a2=0.05;


    double wu1,wu1_last,wintegral,werr0,werr1;
    double wderived0,wderived1;

    int stateCTRL;

    ofstream out;


private slots:
    void timer_timout();


};

#endif // CONTROLLER_H
