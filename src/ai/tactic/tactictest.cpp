#include "tactictest.h"
TacticTest::TacticTest(WorldModel *worldmodel, QObject *parent) :
    Tactic("TacticTest", worldmodel, parent)
{

}

RobotCommand TacticTest::getCommand()
{
    RobotCommand rc;

    if(!wm->ourRobot[id].isValid) return rc;
    if(id==4){ //3
        flag2++;
        QList <Vector2D> points;
        Vector2D v1(-1700,-2000);  // -2250 - -2000
        Vector2D v2(-1700,2000);

        qDebug()<<"wtf!";
        if(flag==0){

            rc.fin_pos.loc=v1;
            rc.maxSpeed=4;
            rc.useNav=true;
            rc.isBallObs=true;
            //Vector2D d(0,0);
            rc.fin_pos.dir=(v1-v2).dir().radian();
            if(wm->ourRobot[id].pos.loc.dist(v1)<150){
                flag=1;
            }
        }

        else if(flag==1){

            rc.fin_pos.loc=v2;
            rc.maxSpeed=4;
            rc.useNav=true;
            //Vector2D d(0,0);
            rc.fin_pos.dir=(v1-v2).dir().radian();
            if(wm->ourRobot[id].pos.loc.dist(v2)<150){
                flag=0;
                points.clear();
                wm->debug_pos.clear();
            }
        }
        //if(flag2%10==0){
        //    points.push_back(wm->ourRobot[3].pos.loc);
        //}
        //wm->debug_type=2;
        //for(int i=0;i<points.length();i++){
        //    wm->debug_pos.append(points);
        //}
        return rc;


    }

    else if(id==5){

//        Vector2D v1(-1700,-2000);  // -2250 - -2000
//        Vector2D v2(-1700,2000);
        Vector2D v1(-3900,1000);
        Vector2D v2(-800,1000);
        wm->debug_pos.append(v1);
        wm->debug_pos.append(v2);
        if(flag1==0){

            rc.fin_pos.loc=v1;
            rc.maxSpeed=2;
            rc.useNav=false;
            if(wm->ourRobot[5].pos.loc.dist(v1)<100){
                flag1=1;
            }
        }
        else if(flag1==1){

            rc.fin_pos.loc=v2;
            rc.maxSpeed=2;
            rc.useNav=false;
            if(wm->ourRobot[5].pos.loc.dist(v2)<100){
                flag1=0;
            }
        }
        return rc;

    }

    else if(id==1){ // 7 for real

        if(flag2==0){
            Vector2D v1(-500,1000);
            rc.fin_pos.loc=v1;
            rc.maxSpeed=2;
            rc.useNav=false;
            if(wm->ourRobot[1].pos.loc.dist(v1)<100){   // 7 for real
                flag2=1;
            }
        }
        else if(flag2==1){
            Vector2D v2(-500,-1000);
            rc.fin_pos.loc=v2;
            rc.maxSpeed=2;
            rc.useNav=false;
            if(wm->ourRobot[1].pos.loc.dist(v2)<100){ // 7 for real
                flag2=0;
            }
        }
        return rc;

    }

    else{
        rc.maxSpeed=0;
        return rc;
    }
=======
=======
>>>>>>> 5aee4ed9254def077fb748ede91039b2d492a21c
=======
>>>>>>> 5aee4ed9254def077fb748ede91039b2d492a21c
    /*
    rc.fin_pos.loc = Vector2D(1300,100);
    rc.maxSpeed = 2;
    rc.useNav = true;
    */

    /*
    if ( id == 3 )
    {
        Vector2D di = wm->ball.pos.loc - wm->ourRobot[3].pos.loc;
        double diss = sqrt( di.x * di.x + di.y * di.y );
        rc.fin_pos.loc = wm->ourRobot[3].pos.loc + (di  / diss) * (diss - 500);
    }

    if ( id == 4 )
    {
        Vector2D di = wm->ball.pos.loc - wm->ourRobot[4].pos.loc;
        double diss = sqrt( di.x * di.x + di.y * di.y );
        rc.fin_pos.loc = wm->ourRobot[4].pos.loc + (di  / diss) * (diss - 500);
    }

    if ( id == 5 )
    {
        Vector2D di = wm->ball.pos.loc - wm->ourRobot[5].pos.loc;
        double diss = sqrt( di.x * di.x + di.y * di.y );
        rc.fin_pos.loc = wm->ourRobot[5].pos.loc + (di  / diss) * (diss - 500);
    }
    */

    /*
    rc.fin_pos.loc = fpos;
    rc.maxSpeed = 2;
    rc.useNav = true;
    */

    /*
    Segment2D line (Field::ourGoalCenter, wm->oppRobot[idtest].pos.loc);
    Circle2D cir (wm->oppRobot[idtest].pos.loc, 500);
    Vector2D first, second;
    cir.intersection(line, &first, &second);
    fpos = first;
    rc.fin_pos.loc = fpos;
    rc.maxSpeed = 2;
    rc.useNav = true;
    */
<<<<<<< HEAD
<<<<<<< HEAD

    /*
    rc.fin_pos.loc = fpos;
    rc.maxSpeed = 2;
    rc.useNav = true;
    */

    /*
    if (idtest == 0)
    {
        rc.fin_pos.loc = fpos;
        rc.maxSpeed = 2;
        rc.useNav = true;
=======
=======
>>>>>>> 5aee4ed9254def077fb748ede91039b2d492a21c

    /*
    rc.fin_pos.loc = fpos;
    rc.maxSpeed = 2;
    rc.useNav = true;
    */

    /*
    if (idtest == 0)
    {
        rc.fin_pos.loc = fpos;
        rc.maxSpeed = 2;
        rc.useNav = true;

        double t = atan( (wm->ball.pos.loc.y - wm->ourRobot[id].pos.loc.y) / (wm->ball.pos.loc.x - wm->ourRobot[id].pos.loc.x) );
        if (wm->ball.pos.loc.x - wm->ourRobot[id].pos.loc.x < 0)
            if (wm->ball.pos.loc.y - wm->ourRobot[id].pos.loc.y > 0)
                t += 3.1415;
            else
                t -= 3.1415;
        rc.fin_pos.dir = t;
    }

    if (idtest == 1)
    {
        Line2D line (wm->ball.pos.loc, fpos);
        Circle2D cir (wm->ball.pos.loc, ROBOT_RADIUS + 5);
        Vector2D first, second, dot;
        cir.intersection(line, &first, &second);
        if ((first - fpos).length() < (second - fpos).length())
            dot = second;
        else
            dot = first;

        double t = atan( (fpos.y - wm->ball.pos.loc.y) / (fpos.x - wm->ball.pos.loc.x) );
        if (fpos.x - wm->ball.pos.loc.x < 0)
            if (fpos.y - wm->ball.pos.loc.y > 0)
                t += 3.1415;
            else
                t -= 3.1415;

        rc.fin_pos.loc = dot;
        rc.maxSpeed = 2;
        rc.useNav = true;
        rc.fin_pos.dir = t;

        if (abs(wm->ourRobot[id].pos.dir - t) < 0.2)
            rc.kickspeedx = 4;

        //std::cout << wm->ourRobot[id].pos.dir << ":::" << t << std::endl;
    }
    */
<<<<<<< HEAD

    //.................................

    //Vector2D v(-1000,0);
    rc.fin_pos.loc = fpos;
    //rc.fin_pos.dir = (wm->ball.pos.loc - fpos).dir().radian();
    rc.maxSpeed = 2;
    rc.useNav = true;
=======
>>>>>>> 5aee4ed9254def077fb748ede91039b2d492a21c

    //.................................

<<<<<<< HEAD
=======
    //Vector2D v(-1000,0);
    rc.fin_pos.loc = fpos;
    //rc.fin_pos.dir = (wm->ball.pos.loc - fpos).dir().radian();
    rc.maxSpeed = 2;
    rc.useNav = true;


>>>>>>> 5aee4ed9254def077fb748ede91039b2d492a21c
    /*
    if (wm->gs == STATE_Stop)
    {
        Segment2D line (Field::ourGoalCenter, wm->ball.pos.loc);
        Circle2D cir (wm->ball.pos.loc, 500);
        Vector2D first, second;
        cir.intersection(line, &first, &second);
        fpos = first;
        rc.fin_pos.loc = fpos;
        rc.maxSpeed = 2;
        rc.useNav = true;
    }
<<<<<<< HEAD
=======

    if (wm->cmgs.theirFreeKick())
    {
        qDebug()<<"oppFreeKick";
        rc.fin_pos.loc = Field::ourGoalCenter;
        rc.maxSpeed = 2;
        rc.useNav = true;
    }

    if (wm->gs == STATE_Halt)
    {
        rc.fin_pos.loc = wm->ourRobot[id].pos.loc;
        rc.maxSpeed = 2;
        rc.useNav = true;
    }

    if (wm->cmgs.ourFreeKick())
    {
        qDebug()<<"ourFreeKick";
        Vector2D fposTest = Field::oppGoalCenter;
        Line2D line (wm->ball.pos.loc, fposTest);
        Circle2D cir (wm->ball.pos.loc, ROBOT_RADIUS + 5);
        Vector2D first, second, dot;
        cir.intersection(line, &first, &second);
        if ((first - fposTest).length() < (second - fposTest).length())
            dot = second;
        else
            dot = first;

        double t = atan( (fposTest.y - wm->ball.pos.loc.y) / (fposTest.x - wm->ball.pos.loc.x) );
        if (fposTest.x - wm->ball.pos.loc.x < 0)
            if (fposTest.y - wm->ball.pos.loc.y > 0)
                t += 3.1415;
            else
                t -= 3.1415;

        rc.fin_pos.loc = dot;
        rc.maxSpeed = 2;
        rc.useNav = true;
        rc.fin_pos.dir = t;

        if (abs(wm->ourRobot[id].pos.dir - t) < 0.2)
            rc.kickspeedx = 4;

    }
    */
>>>>>>> 5aee4ed9254def077fb748ede91039b2d492a21c

    if (wm->cmgs.theirFreeKick())
    {
        qDebug()<<"oppFreeKick";
        rc.fin_pos.loc = Field::ourGoalCenter;
        rc.maxSpeed = 2;
        rc.useNav = true;
    }

    if (wm->gs == STATE_Halt)
    {
        rc.fin_pos.loc = wm->ourRobot[id].pos.loc;
        rc.maxSpeed = 2;
        rc.useNav = true;
    }

    if (wm->cmgs.ourFreeKick())
    {
        qDebug()<<"ourFreeKick";
        Vector2D fposTest = Field::oppGoalCenter;
        Line2D line (wm->ball.pos.loc, fposTest);
        Circle2D cir (wm->ball.pos.loc, ROBOT_RADIUS + 5);
        Vector2D first, second, dot;
        cir.intersection(line, &first, &second);
        if ((first - fposTest).length() < (second - fposTest).length())
            dot = second;
        else
            dot = first;

        double t = atan( (fposTest.y - wm->ball.pos.loc.y) / (fposTest.x - wm->ball.pos.loc.x) );
        if (fposTest.x - wm->ball.pos.loc.x < 0)
            if (fposTest.y - wm->ball.pos.loc.y > 0)
                t += 3.1415;
            else
                t -= 3.1415;

        rc.fin_pos.loc = dot;
        rc.maxSpeed = 2;
        rc.useNav = true;
        rc.fin_pos.dir = t;

        if (abs(wm->ourRobot[id].pos.dir - t) < 0.2)
            rc.kickspeedx = 4;

    }
    */
>>>>>>> 5aee4ed9254def077fb748ede91039b2d492a21c

        double t = atan( (wm->ball.pos.loc.y - wm->ourRobot[id].pos.loc.y) / (wm->ball.pos.loc.x - wm->ourRobot[id].pos.loc.x) );
        if (wm->ball.pos.loc.x - wm->ourRobot[id].pos.loc.x < 0)
            if (wm->ball.pos.loc.y - wm->ourRobot[id].pos.loc.y > 0)
                t += 3.1415;
            else
                t -= 3.1415;
        rc.fin_pos.dir = t;
    }

    if (idtest == 1)
    {
        Line2D line (wm->ball.pos.loc, fpos);
        Circle2D cir (wm->ball.pos.loc, ROBOT_RADIUS + 5);
        Vector2D first, second, dot;
        cir.intersection(line, &first, &second);
        if ((first - fpos).length() < (second - fpos).length())
            dot = second;
        else
            dot = first;

        double t = atan( (fpos.y - wm->ball.pos.loc.y) / (fpos.x - wm->ball.pos.loc.x) );
        if (fpos.x - wm->ball.pos.loc.x < 0)
            if (fpos.y - wm->ball.pos.loc.y > 0)
                t += 3.1415;
            else
                t -= 3.1415;

        rc.fin_pos.loc = dot;
        rc.maxSpeed = 2;
        rc.useNav = true;
        rc.fin_pos.dir = t;

        if (abs(wm->ourRobot[id].pos.dir - t) < 0.2)
            rc.kickspeedx = 4;

        //std::cout << wm->ourRobot[id].pos.dir << ":::" << t << std::endl;
    }
    */

    //.................................

    //Vector2D v(-1000,0);
    rc.fin_pos.loc = fpos;
    //rc.fin_pos.dir = (wm->ball.pos.loc - fpos).dir().radian();
    rc.maxSpeed = 2;
    rc.useNav = true;


    /*
    if (wm->gs == STATE_Stop)
    {
        Segment2D line (Field::ourGoalCenter, wm->ball.pos.loc);
        Circle2D cir (wm->ball.pos.loc, 500);
        Vector2D first, second;
        cir.intersection(line, &first, &second);
        fpos = first;
        rc.fin_pos.loc = fpos;
        rc.maxSpeed = 2;
        rc.useNav = true;
    }

    if (wm->cmgs.theirFreeKick())
    {
        qDebug()<<"oppFreeKick";
        rc.fin_pos.loc = Field::ourGoalCenter;
        rc.maxSpeed = 2;
        rc.useNav = true;
    }

    if (wm->gs == STATE_Halt)
    {
        rc.fin_pos.loc = wm->ourRobot[id].pos.loc;
        rc.maxSpeed = 2;
        rc.useNav = true;
    }

    if (wm->cmgs.ourFreeKick())
    {
        qDebug()<<"ourFreeKick";
        Vector2D fposTest = Field::oppGoalCenter;
        Line2D line (wm->ball.pos.loc, fposTest);
        Circle2D cir (wm->ball.pos.loc, ROBOT_RADIUS + 5);
        Vector2D first, second, dot;
        cir.intersection(line, &first, &second);
        if ((first - fposTest).length() < (second - fposTest).length())
            dot = second;
        else
            dot = first;

        double t = atan( (fposTest.y - wm->ball.pos.loc.y) / (fposTest.x - wm->ball.pos.loc.x) );
        if (fposTest.x - wm->ball.pos.loc.x < 0)
            if (fposTest.y - wm->ball.pos.loc.y > 0)
                t += 3.1415;
            else
                t -= 3.1415;

        rc.fin_pos.loc = dot;
        rc.maxSpeed = 2;
        rc.useNav = true;
        rc.fin_pos.dir = t;

        if (abs(wm->ourRobot[id].pos.dir - t) < 0.2)
            rc.kickspeedx = 4;

    }
    */
>>>>>>> 5aee4ed9254def077fb748ede91039b2d492a21c

}

void TacticTest::setpos(Vector2D pos)
{
    fpos = pos;
}

void TacticTest::setidtest(int idt)
{
    idtest = idt;
}

void TacticTest::setpos(Vector2D pos)
{
    fpos = pos;
}

void TacticTest::setidtest(int idt)
{
    idtest = idt;
}

void TacticTest::setpos(Vector2D pos)
{
    fpos = pos;
}

void TacticTest::setidtest(int idt)
{
    idtest = idt;
}
