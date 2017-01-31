#include "playtest.h"
PlayTest::PlayTest(WorldModel *worldmodel, QObject *parent) :
    Play("PlayTest", worldmodel, parent)
{
    tTest1 = new TacticTest(wm);
    tTest2 = new TacticTest(wm);
    tTest3 = new TacticTest(wm);
    tTest4 = new TacticTest(wm);
    tTest5 = new TacticTest(wm);
    tTest6 = new TacticTest(wm);

    tGoalie = new TacticGoalie(wm);
    tDefenderLeft = new TacticDefender(wm);
    tDefenderRight = new TacticDefender(wm);
    tStopMid = new TacticStop(wm);
    tStopLeft = new TacticStop(wm);
    tStopRight = new TacticStop(wm);
    tAttackerLeft = new TacticAttacker(wm);
    tAttackerRight = new TacticAttacker(wm);
}

int PlayTest::enterCondition()
{
    //return 20000;
    return 0;
}

void PlayTest::initRole()
{
}

void PlayTest::execute()
{
    //tactics[2] = tTest;

    /*
    tactics[3] = tTest;
    tactics[4] = tTest;
    tactics[5] = tTest;
    */

    /*
    tTest1->setpos( Vector2D(1000,1000) );
    tactics[1] = tTest1;
    tTest2->setpos( Vector2D(1500,1000) );
    tactics[2] = tTest2;
    tTest3->setpos( Vector2D(2000,1000) );
    tactics[3] = tTest3;
    */

    /*
    Segment2D line (Field::ourGoalCenter , wm->ball.pos.loc);
    Circle2D cir (wm->ball.pos.loc , 500);
    Vector2D first, second;
    cir.intersection(line, &first, &second);

    tTest1->setpos(first);
    tactics[1] = tTest1;
    */

    /*
    Segment2D line (Field::ourGoalCenter , wm->oppRobot[1].pos.loc);
    Circle2D cir (wm->oppRobot[1].pos.loc , 500);
    Vector2D first, second;
    cir.intersection(line, &first, &second);

    tTest1->setpos(first);
    tactics[1] = tTest1;
    */

    /*
    double minDTB = 50000;
    int minDTBid;
    for (int i = 0; i < 5; i++)
    {
        Segment2D dToBall (wm->oppRobot[i+1].pos.loc, wm->ball.pos.loc);
        if (dToBall.length() < minDTB)
        {
            minDTB = dToBall.length();
            minDTBid = i+1;
        }
    }
    double minD = 50000;
    int minDid;
    for (int i = 0; i < 3; i++)
    {
        Segment2D dToLoc (wm->ourRobot[i+1].pos.loc, wm->oppRobot[minDTBid].pos.loc);
        if (dToLoc.length() < minD)
        {
            minD = dToLoc.length();
            minDid = i+1;
        }
    }

    tTest1->setidtest(minDTBid);
    tactics[minDid] = tTest1;

    double dOpp[5][5];
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
        {
            Segment2D seg (wm->oppRobot[i+1].pos.loc, wm->oppRobot[j+1].pos.loc);
            dOpp[i][j] = seg.length();
        }
    int n[2][2] = {0, 0, 0, 0};
    double minDis = 50000;
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            if ( i+1 != minDTBid && j+1 !=minDTBid && i != j )
                if (dOpp[i][j] < minDis)
                {
                    minDis = dOpp[i][j];
                    n[0][0] = i + 1;
                    n[0][1] = j + 1;
                }
    for (int i = 1; i <= 5; i++)
        if (i != minDTBid && i != n[0][0] && i != n[0][1])
            n[1][0] = i;
    n[1][1] = 15 - (minDTBid + n[0][0] + n[0][1] + n[1][0]);

    std::cout << minDTBid << std::endl;
    std::cout << n[0][0] << "::" << n[0][1] << std::endl
              << n[1][0] << "::" << n[1][1] << std::endl;

    int a[2];
    for (int i = 0; i < 2; i++)
    {
        Segment2D seg0 (Field::ourGoalCenter, wm->oppRobot[ n[i][0] ].pos.loc);
        Segment2D seg1 (Field::ourGoalCenter, wm->oppRobot[ n[i][1] ].pos.loc);
        if (seg0.length() < seg1.length())
            a[i] = n[i][0];
        else
            a[i] = n[i][1];
    }

    int b[2];
    for (int i = 1; i <= 3; i++)
        if (i != minDid)
            b[0] = i;
    b[1] = 6 - (minDid + b[0]);

    Segment2D seg2 (wm->ourRobot[ b[0] ].pos.loc, wm->oppRobot[ a[0] ].pos.loc);
    Segment2D seg3 (wm->ourRobot[ b[1] ].pos.loc, wm->oppRobot[ a[0] ].pos.loc);
    if (seg2.length() < seg3.length())
    {
        tTest2->setidtest(a[0]);
        tactics[b[0]] = tTest2;
        tTest3->setidtest(a[1]);
        tactics[b[1]] = tTest3;
    }
    else
    {
        tTest2->setidtest(a[0]);
        tactics[b[1]] = tTest2;
        tTest3->setidtest(a[1]);
        tactics[b[0]] = tTest3;
    }

    */

    /*
    //Project 1

    Vector2D dot;
    Segment2D seg(wm->ball.pos.loc, wm->ball.pos_predicted.loc);
    //std::cout << seg.length() << std::endl;

    Line2D line1(wm->ball.pos.loc, wm->ball.pos_predicted.loc);
    Line2D line2(Field::ourGoalCenter, Field::ourGoalPost_R);
    dot = line1.intersection(line2);

    if ( seg.length() < 5 || abs(dot.y - Field::ourGoalCenter.y) > abs(Field::ourGoalPost_L.y - Field::ourGoalCenter.y) )
    {
        dot = Field::ourGoalCenter;
    }

    tTest1->setpos(dot);
    tactics[0] = tTest1;

    //Step2

    double slope1[2], slope2[2];
    Vector2D dot1 = Field::ourGoalCenter, dot2 = Field::ourGoalCenter;
    dot1.y += ROBOT_RADIUS;
    slope1[0] = (wm->ball.pos.loc.y - dot1.y) / (wm->ball.pos.loc.x - dot1.x);
    slope2[0] = (wm->ball.pos.loc.y - Field::ourGoalPost_L.y) / (wm->ball.pos.loc.x - Field::ourGoalPost_L.x);
    dot2.y -= ROBOT_RADIUS;
    slope1[1] = (wm->ball.pos.loc.y - Field::ourGoalPost_R.y) / (wm->ball.pos.loc.x - Field::ourGoalPost_R.x);
    slope2[1] = (wm->ball.pos.loc.y - dot2.y) / (wm->ball.pos.loc.x - dot2.x);

    for (int i = 0; i < 2; i++)
    {


        //AngleDeg deg1, deg2;
        //deg1.atan_deg(slope1);
        //deg2.atan_deg(slope2);

        double degree1 = atan(slope1[i]);
        double degree2 = atan(slope2[i]);
        AngleDeg deg1(degree1), deg2(degree2);

        AngleDeg bis, delta;
        //bis.bisect(deg1, deg2); //??
        bis = operator +(deg1, deg2);
        bis.operator /=(2);
        delta = operator -(deg1, deg2);
        delta.operator /=(2);
        //delta = bis.operator -=(deg2); //??

        Line2D linebis(wm->ball.pos.loc, bis.degree() * 57.32);
        //linebis = angle_bisector(wm->ball.pos.loc, deg1, deg2); //??
        Vector2D IS = linebis.intersection(line2);
        Segment2D seg1(wm->ball.pos.loc, IS);

        std::cout << deg1.degree() * 57.32 << ":::::" << deg2.degree() * 57.32 << ":::::"
                  << delta.degree() * 57.32 << ":::::" << bis.degree() * 57.32 << std::endl;

        //double d = ROBOT_RADIUS / abs( delta.sin() ); //??
        double d = ROBOT_RADIUS / sin(delta.degree());
        Circle2D cir1 (wm->ball.pos.loc, d);
        Vector2D fdot, sdot;
        cir1.intersection(seg1, &fdot, &sdot);

        Circle2D ourDCircle (Field::ourGoalCenter, 1300);
        if (wm->kn->IsInsideGolieArea(wm->ball.pos.loc))
            fdot = {Field::ourGoalCenter.x + 1200, pow(-1, i) * 90};
        else if ( (fdot.x == NULL && fdot.y == NULL) || (wm->kn->IsInsideGolieArea(fdot)) )
            ourDCircle.intersection(seg1, &fdot, &sdot);

        std::cout << fdot.x << "::" << fdot.y << std::endl;

        if (i == 0)
        {
            tTest2->setpos(fdot);
            tactics[1] = tTest2;
        }
        if (i == 1)
        {
            tTest3->setpos(fdot);
            tactics[2] = tTest3;
        }    
    }


    //step 3

    Segment2D segtest (wm->ourRobot[1].pos.loc, wm->ourRobot[2].pos.loc);
    Vector2D dottest = segtest.intersection(line1);

    if ( (seg.length() > 5) && (dottest.x != NULL && dottest.y != NULL) )
    {
        tTest2->setpos(dottest);
        tactics[1] = tTest2;
        tTest3->setpos(dottest);
        tactics[2] = tTest3;
    }
    */

    //Project 2

    //tTest1->setidtest(5);
    //tTest1->setpos(wm->ourRobot[5].pos.loc);
    //tactics[4] = tTest1;


    /*
    if ( (wm->ball.pos.loc - wm->ourRobot[5].pos.loc).length() < 1500 )
    {
        tTest1->setidtest(1);
        tTest1->setpos(Field::oppGoalCenter);
        tactics[5] = tTest1;
        tTest2->setidtest(0);
        tTest2->setpos({0,0});
        tactics[4] = tTest2;
    }
    else
    {
        tTest2->setidtest(1);
        tTest2->setpos(wm->ourRobot[5].pos.loc);
        tactics[4] = tTest2;


        double a = atan(wm->ball.vel.loc.y /wm->ball.vel.loc.x);
        Line2D line1(wm->ball.pos.loc, a);
        Line2D line2(wm->ourRobot[5].pos.loc, {0,wm->ourRobot[5].pos.loc.y});

        Vector2D dot;

        if ( abs(wm->ball.vel.loc.y) > 0.5 )
        {
            dot = line1.intersection(line2);
            tTest1->setidtest(0);
            tTest1->setpos(dot);
            tactics[5] = tTest1;
        }
        std::cout << abs(wm->ball.vel.loc.y) << std::endl;

    }
    */


    /*
    //if ( (wm->ball.pos.loc - wm->ourRobot[5].pos.loc).length() < 2000 )
    if (wm->ball.pos.loc.x > 700)
    {
        tTest1->setidtest(1);
        tTest1->setpos(wm->ourRobot[4].pos.loc);
        tactics[5] = tTest1;
        //tTest2->setidtest(0);
        //tTest2->setpos({-2000,0});
        //tactics[4] = tTest2;
    }
    else if (wm->ball.vel.loc.x < -0.5)
    {
        tTest1->setidtest(0);
        tTest1->setpos({2000,0});
        tactics[5] = tTest1;
    }
    else if (wm->ball.vel.loc.x > 0.5)
    {
        Vector2D dot;
        Segment2D seg(wm->ball.pos.loc, wm->ball.pos_predicted.loc);

        Line2D line1(wm->ball.pos.loc, wm->ball.pos_predicted.loc);
        Line2D line2({2000,-100}, {2000,100});
        dot = line1.intersection(line2);

        if ( seg.length() < 5 )
        {
            dot = {2000,0};
        }

        tTest1->setidtest(0);
        tTest1->setpos(dot);
        tactics[5] = tTest1;
    }
    //else
    //if ( (wm->ball.pos.loc - wm->ourRobot[4].pos.loc).length() < 2000 )
    if (wm->ball.pos.loc.x < -700)
    {
        //tTest1->setidtest(0);
        //tTest1->setpos({2000,0});
        //tactics[5] = tTest1;
        tTest2->setidtest(1);
        tTest2->setpos(wm->ourRobot[5].pos.loc);
        tactics[4] = tTest2;
    }
    else if (wm->ball.vel.loc.x > 0.5)
    {
        tTest2->setidtest(0);
        tTest2->setpos({-2000,0});
        tactics[4] = tTest2;
    }
    else if (wm->ball.vel.loc.x < -0.5)
    {
        Vector2D dot;
        Segment2D seg(wm->ball.pos.loc, wm->ball.pos_predicted.loc);

        Line2D line1(wm->ball.pos.loc, wm->ball.pos_predicted.loc);
        Line2D line2({-2000,-100}, {-2000,100});
        dot = line1.intersection(line2);

        if ( seg.length() < 5 )
        {
            dot = {-2000,0};
        }

        tTest2->setidtest(0);
        tTest2->setpos(dot);
        tactics[4] = tTest2;
    }

    std::cout << wm->ball.vel.loc.x << std::endl;

    */

    //...................................................................................
/*
    QList <int> actives = wm->kn->ActiveAgents();
    actives.removeOne(wm->ref_goalie_our);
    wm->ourRobot[wm->ref_goalie_our].Role = AgentRole::Golie;
    switch (actives.length()) {
    case 1:
        wm->ourRobot[actives.takeFirst()].Role = AgentRole::DefenderLeft;
        break;
    case 2:
        wm->ourRobot[actives.takeFirst()].Role = AgentRole::DefenderLeft;
        wm->ourRobot[actives.takeFirst()].Role = AgentRole::DefenderRight;
        break;
    case 3:
        wm->ourRobot[actives.takeFirst()].Role = AgentRole::DefenderLeft;
        wm->ourRobot[actives.takeFirst()].Role = AgentRole::DefenderRight;
        wm->ourRobot[actives.takeFirst()].Role = AgentRole::AttackerMid;
        break;
    case 4:
        wm->ourRobot[actives.takeFirst()].Role = AgentRole::DefenderLeft;
        wm->ourRobot[actives.takeFirst()].Role = AgentRole::DefenderRight;
        wm->ourRobot[actives.takeFirst()].Role = AgentRole::AttackerMid;
        wm->ourRobot[actives.takeFirst()].Role = AgentRole::AttackerLeft;
        break;
    case 5:
        wm->ourRobot[actives.takeFirst()].Role = AgentRole::DefenderLeft;
        wm->ourRobot[actives.takeFirst()].Role = AgentRole::DefenderRight;
        wm->ourRobot[actives.takeFirst()].Role = AgentRole::AttackerMid;
        wm->ourRobot[actives.takeFirst()].Role = AgentRole::AttackerLeft;
        wm->ourRobot[actives.takeFirst()].Role = AgentRole::AttackerRight;
        break;
    default:
        break;
    }

    Vector2D dot;
    Segment2D seg(wm->ball.pos.loc, wm->ball.pos_predicted.loc);

    Line2D line1(wm->ball.pos.loc, wm->ball.pos_predicted.loc);
    Line2D line2(Field::ourGoalCenter, Field::ourGoalPost_R);
    dot = line1.intersection(line2);

    if ( seg.length() < 5 || abs(dot.y - Field::ourGoalCenter.y) > abs(Field::ourGoalPost_L.y - Field::ourGoalCenter.y) )
    {
        dot = Field::ourGoalCenter;
    }

    double slope1[2], slope2[2];
    Vector2D dot1 = Field::ourGoalCenter, dot2 = Field::ourGoalCenter;
    dot1.y += ROBOT_RADIUS;
    slope1[0] = (wm->ball.pos.loc.y - dot1.y) / (wm->ball.pos.loc.x - dot1.x);
    slope2[0] = (wm->ball.pos.loc.y - Field::ourGoalPost_L.y) / (wm->ball.pos.loc.x - Field::ourGoalPost_L.x);
    dot2.y -= ROBOT_RADIUS;
    slope1[1] = (wm->ball.pos.loc.y - Field::ourGoalPost_R.y) / (wm->ball.pos.loc.x - Field::ourGoalPost_R.x);
    slope2[1] = (wm->ball.pos.loc.y - dot2.y) / (wm->ball.pos.loc.x - dot2.x);

    Vector2D fdotDefLeft, fdotDefRight;
    for (int i = 0; i < 2; i++)
    {
        double degree1 = atan(slope1[i]);
        double degree2 = atan(slope2[i]);
        AngleDeg deg1(degree1), deg2(degree2);

        AngleDeg bis, delta;
        bis = operator +(deg1, deg2);
        bis.operator /=(2);
        delta = operator -(deg1, deg2);
        delta.operator /=(2);

        Line2D linebis(wm->ball.pos.loc, bis.degree() * 57.32);
        Vector2D IS = linebis.intersection(line2);
        Segment2D seg1(wm->ball.pos.loc, IS);

        double d = ROBOT_RADIUS / sin(delta.degree());
        Circle2D cir1 (wm->ball.pos.loc, d);
        Vector2D fdot, sdot;
        cir1.intersection(seg1, &fdot, &sdot);

        Circle2D ourDCircle (Field::ourGoalCenter, 1300);
        if (wm->kn->IsInsideGolieArea(wm->ball.pos.loc))
            fdot = {Field::ourGoalCenter.x + 1200, pow(-1, i) * 90};
        else if ( (fdot.x == NULL && fdot.y == NULL) || (wm->kn->IsInsideGolieArea(fdot)) )
            ourDCircle.intersection(seg1, &fdot, &sdot);

        if (i == 0)
        {
            //tTest2->setpos(fdot);
            //tactics[1] = tTest2;
            fdotDefLeft = fdot;
        }
        if (i == 1)
        {
            //tTest3->setpos(fdot);
            //tactics[2] = tTest3;
            fdotDefRight = fdot;
        }
    }

    Vector2D fdotAttMid, fdotAttLeft, fdotAttRight;
    Vector2D se;
    Circle2D cir (wm->ball.pos.loc, 500);
    Segment2D segA1 (Field::ourGoalCenter, wm->ball.pos.loc);
    Segment2D segA2 (Field::ourGoalPost_L, wm->ball.pos.loc);
    Segment2D segA3 (Field::ourGoalPost_R, wm->ball.pos.loc);
    cir.intersection(segA1, &fdotAttMid, &se);
    cir.intersection(segA2, &fdotAttLeft, &se);
    cir.intersection(segA3, &fdotAttRight, &se);

    QList <int> activeRobots = wm->kn->ActiveAgents();
    for (int i = 0; i < wm->kn->ActiveAgents().length(); i++)
    {
        if (wm->ourRobot[activeRobots.at(i)].Role == AgentRole::Golie)
        {
            tTest1->setpos(dot);
            tactics[activeRobots.at(i)] = tTest1;
        }
        if (wm->ourRobot[activeRobots.at(i)].Role == AgentRole::DefenderLeft)
        {
            tTest2->setpos(fdotDefLeft);
            tactics[activeRobots.at(i)] = tTest2;
        }
        if (wm->ourRobot[activeRobots.at(i)].Role == AgentRole::DefenderRight)
        {
            tTest3->setpos(fdotDefRight);
            tactics[activeRobots.at(i)] = tTest3;
        }
        if (wm->ourRobot[activeRobots.at(i)].Role == AgentRole::AttackerMid)
        {
            tTest4->setpos(fdotAttMid);
            tactics[activeRobots.at(i)] = tTest4;
        }
        if (wm->ourRobot[activeRobots.at(i)].Role == AgentRole::AttackerLeft)
        {
            tTest5->setpos(fdotAttLeft);
            tactics[activeRobots.at(i)] = tTest5;
        }
        if (wm->ourRobot[activeRobots.at(i)].Role == AgentRole::AttackerRight)
        {
            tTest6->setpos(fdotAttRight);
            tactics[activeRobots.at(i)] = tTest6;
        }
    }

    //tactics[wm->ref_goalie_our] = tTest1;
    //qDebug() << "Hello world";
*/

    //--------------------------------------------------------------------------------------------------------------------
    //play Stop version 1
/*
    QList <int> actives = wm->kn->ActiveAgents();
    actives.removeOne(wm->ref_goalie_our);
    wm->ourRobot[wm->ref_goalie_our].Role = AgentRole::Golie;
    switch (actives.length()) {
    case 1:
        wm->ourRobot[actives.takeFirst()].Role = AgentRole::DefenderLeft;
        break;
    case 2:
        wm->ourRobot[actives.takeFirst()].Role = AgentRole::DefenderLeft;
        wm->ourRobot[actives.takeFirst()].Role = AgentRole::DefenderRight;
        break;
    case 3:
        wm->ourRobot[actives.takeFirst()].Role = AgentRole::DefenderLeft;
        wm->ourRobot[actives.takeFirst()].Role = AgentRole::DefenderRight;
        wm->ourRobot[actives.takeFirst()].Role = AgentRole::AttackerMid;
        break;
    case 4:
        wm->ourRobot[actives.takeFirst()].Role = AgentRole::DefenderLeft;
        wm->ourRobot[actives.takeFirst()].Role = AgentRole::DefenderRight;
        wm->ourRobot[actives.takeFirst()].Role = AgentRole::AttackerMid;
        wm->ourRobot[actives.takeFirst()].Role = AgentRole::AttackerLeft;
        break;
    case 5:
        wm->ourRobot[actives.takeFirst()].Role = AgentRole::DefenderLeft;
        wm->ourRobot[actives.takeFirst()].Role = AgentRole::DefenderRight;
        wm->ourRobot[actives.takeFirst()].Role = AgentRole::AttackerMid;
        wm->ourRobot[actives.takeFirst()].Role = AgentRole::AttackerLeft;
        wm->ourRobot[actives.takeFirst()].Role = AgentRole::AttackerRight;
        break;
    default:
        break;
    }

    Vector2D dot;
    Segment2D seg(wm->ball.pos.loc, wm->ball.pos_predicted.loc);

    Line2D line1(wm->ball.pos.loc, wm->ball.pos_predicted.loc);
    Line2D line2(Field::ourGoalCenter, Field::ourGoalPost_R);
    dot = line1.intersection(line2);

    if ( seg.length() < 5 || abs(dot.y - Field::ourGoalCenter.y) > abs(Field::ourGoalPost_L.y - Field::ourGoalCenter.y) )
    {
        dot = Field::ourGoalCenter;
    }

    Vector2D fPosAttLeft, fPosAttRight, sec;
    Vector2D fPosAttMid, fPosDefLeft, fPosDefRight;

    if ( wm->kn->IsInsideGolieArea(wm->ball.pos.loc) )
    {
        fPosAttLeft = {Field::ourGoalCenter.x + 2800, 1000};
        fPosAttRight = {Field::ourGoalCenter.x + 2800, -1000};

        Line2D midAttLine (Field::ourGoalCenter, AngleDeg(0));
        Line2D leftDefLine (Field::ourGoalCenter, AngleDeg(45));
        Line2D rightDefLine (Field::ourGoalCenter, AngleDeg(-45));
        Circle2D cir1 (Field::ourGoalCenter, 1300);
        cir1.intersection(midAttLine, &fPosAttMid, &sec);
        if (sec.x > fPosAttMid.x)
            fPosAttMid = sec;
        cir1.intersection(leftDefLine, &fPosDefLeft, &sec);
        if (sec.x > fPosDefLeft.x)
            fPosDefLeft = sec;
        cir1.intersection(rightDefLine, &fPosDefRight, &sec);
        if (sec.x > fPosDefRight.x)
            fPosDefRight = sec;
    }
    else if (wm->ball.pos.loc.x > Field::ourGoalCenter.x + 1300)
    {
        double slope, degree, deltaa;
        slope = (wm->ball.pos.loc.y - Field::ourGoalCenter.y) / (wm->ball.pos.loc.x - Field::ourGoalCenter.x);
        degree = atan(slope);
        deltaa = asin( ROBOT_RADIUS / (500 + ROBOT_RADIUS) );
        AngleDeg deg(degree * 57.32), delta(deltaa * 57.32);
        AngleDeg leftAttDeg, rightAttDeg;
        leftAttDeg = operator -(deg, delta);
        rightAttDeg = operator +(deg, delta);
        Line2D leftAttLine(wm->ball.pos.loc, leftAttDeg.degree() - 1.5);
        Line2D rightAttLine(wm->ball.pos.loc, rightAttDeg.degree() + 1.5);
        Circle2D cir(wm->ball.pos.loc, 500);
        cir.intersection(leftAttLine, &fPosAttLeft, &sec);
        if (sec.x < fPosAttLeft.x)
            fPosAttLeft = sec;
        cir.intersection(rightAttLine, &fPosAttRight, &sec);
        if (sec.x < fPosAttRight.x)
            fPosAttRight = sec;

        Line2D midAttLine (Field::ourGoalCenter, AngleDeg(0));
        Line2D leftDefLine (Field::ourGoalCenter, AngleDeg(45));
        Line2D rightDefLine (Field::ourGoalCenter, AngleDeg(-45));
        Circle2D cir1 (Field::ourGoalCenter, 1300);
        cir1.intersection(midAttLine, &fPosAttMid, &sec);
        if (sec.x > fPosAttMid.x)
            fPosAttMid = sec;
        cir1.intersection(leftDefLine, &fPosDefLeft, &sec);
        if (sec.x > fPosDefLeft.x)
            fPosDefLeft = sec;
        cir1.intersection(rightDefLine, &fPosDefRight, &sec);
        if (sec.x > fPosDefRight.x)
            fPosDefRight = sec;

    }
    else
    {
        if (wm->ball.pos.loc.y > 0)
        {
            double slope, degree, deltaa;
            slope = (wm->ball.pos.loc.y - Field::ourGoalCenter.y) / (wm->ball.pos.loc.x - Field::ourGoalCenter.x);
            degree = atan(slope);
            deltaa = asin( ROBOT_RADIUS / (500 + ROBOT_RADIUS) );
            AngleDeg deg(degree * 57.32), delta(deltaa * 57.32);
            AngleDeg leftAttDeg, rightAttDeg;
            leftAttDeg = operator +(deg, delta);
            rightAttDeg = operator +(deg, delta);
            Line2D leftAttLine(wm->ball.pos.loc, deg.degree());
            Circle2D cir(wm->ball.pos.loc, 500);
            cir.intersection(leftAttLine, &fPosAttLeft, &sec);
            if (sec.y < fPosAttLeft.y)
                fPosAttLeft = sec;

            Line2D rightAttLine(Field::ourGoalCenter, AngleDeg(18));
            Line2D midAttLine (Field::ourGoalCenter, AngleDeg(-18));
            Line2D leftDefLine (Field::ourGoalCenter, AngleDeg(54));
            Line2D rightDefLine (Field::ourGoalCenter, AngleDeg(-54));
            Circle2D cir1 (Field::ourGoalCenter, 1300);
            cir1.intersection(rightAttLine, &fPosAttRight, &sec);
            if (sec.x > fPosAttRight.x)
                fPosAttRight = sec;
            cir1.intersection(midAttLine, &fPosAttMid, &sec);
            if (sec.x > fPosAttMid.x)
                fPosAttMid = sec;
            cir1.intersection(leftDefLine, &fPosDefLeft, &sec);
            if (sec.x > fPosDefLeft.x)
                fPosDefLeft = sec;
            cir1.intersection(rightDefLine, &fPosDefRight, &sec);
            if (sec.x > fPosDefRight.x)
                fPosDefRight = sec;
        }
        else
        {
        double slope, degree, deltaa;
        slope = (wm->ball.pos.loc.y - Field::ourGoalCenter.y) / (wm->ball.pos.loc.x - Field::ourGoalCenter.x);
        degree = atan(slope);
        deltaa = asin( ROBOT_RADIUS / (500 + ROBOT_RADIUS) );
        AngleDeg deg(degree * 57.32), delta(deltaa * 57.32);
        AngleDeg leftAttDeg, rightAttDeg;
        leftAttDeg = operator -(deg, delta);
        rightAttDeg = operator -(deg, delta);
        Line2D rightAttLine(wm->ball.pos.loc, deg.degree());
        Circle2D cir(wm->ball.pos.loc, 500);
        cir.intersection(rightAttLine, &fPosAttRight, &sec);
        if (sec.y > fPosAttRight.y)
            fPosAttRight = sec;

        Line2D leftAttLine(Field::ourGoalCenter, AngleDeg(-18));
        Line2D midAttLine (Field::ourGoalCenter, AngleDeg(18));
        Line2D leftDefLine (Field::ourGoalCenter, AngleDeg(54));
        Line2D rightDefLine (Field::ourGoalCenter, AngleDeg(-54));
        Circle2D cir1 (Field::ourGoalCenter, 1300);
        cir1.intersection(leftAttLine, &fPosAttLeft, &sec);
        if (sec.x > fPosAttLeft.x)
            fPosAttLeft = sec;
        cir1.intersection(midAttLine, &fPosAttMid, &sec);
        if (sec.x > fPosAttMid.x)
            fPosAttMid = sec;
        cir1.intersection(leftDefLine, &fPosDefLeft, &sec);
        if (sec.x > fPosDefLeft.x)
            fPosDefLeft = sec;
        cir1.intersection(rightDefLine, &fPosDefRight, &sec);
        if (sec.x > fPosDefRight.x)
            fPosDefRight = sec;
        }
    }


    QList <int> activeRobots = wm->kn->ActiveAgents();
    for (int i = 0; i < wm->kn->ActiveAgents().length(); i++)
    {
        if (wm->ourRobot[activeRobots.at(i)].Role == AgentRole::Golie)
        {
            tTest1->setpos(dot);
            tactics[activeRobots.at(i)] = tTest1;
        }
        if (wm->ourRobot[activeRobots.at(i)].Role == AgentRole::DefenderLeft)
        {
            tTest2->setpos(fPosDefLeft);
            tactics[activeRobots.at(i)] = tTest2;
        }
        if (wm->ourRobot[activeRobots.at(i)].Role == AgentRole::DefenderRight)
        {
            tTest3->setpos(fPosDefRight);
            tactics[activeRobots.at(i)] = tTest3;
        }
        if (wm->ourRobot[activeRobots.at(i)].Role == AgentRole::AttackerMid)
        {
            tTest4->setpos(fPosAttMid);
            tactics[activeRobots.at(i)] = tTest4;
        }
        if (wm->ourRobot[activeRobots.at(i)].Role == AgentRole::AttackerLeft)
        {
            tTest5->setpos(fPosAttLeft);
            tactics[activeRobots.at(i)] = tTest5;
        }
        if (wm->ourRobot[activeRobots.at(i)].Role == AgentRole::AttackerRight)
        {
            tTest6->setpos(fPosAttRight);
            tactics[activeRobots.at(i)] = tTest6;
        }
    }
*/
    //--------------------------------------------------------------------------------------------------------------------
    //play Stop version 2
/*
    QList <int> actives = wm->kn->ActiveAgents();
    actives.removeOne(wm->ref_goalie_our);
    wm->ourRobot[wm->ref_goalie_our].Role = AgentRole::Golie;
    switch (actives.length()) {
    case 1:
        wm->ourRobot[actives.takeFirst()].Role = AgentRole::DefenderLeft;
        break;
    case 2:
        wm->ourRobot[actives.takeFirst()].Role = AgentRole::DefenderLeft;
        wm->ourRobot[actives.takeFirst()].Role = AgentRole::DefenderRight;
        break;
    case 3:
        wm->ourRobot[actives.takeFirst()].Role = AgentRole::DefenderLeft;
        wm->ourRobot[actives.takeFirst()].Role = AgentRole::DefenderRight;
        wm->ourRobot[actives.takeFirst()].Role = AgentRole::AttackerMid;
        break;
    case 4:
        wm->ourRobot[actives.takeFirst()].Role = AgentRole::DefenderLeft;
        wm->ourRobot[actives.takeFirst()].Role = AgentRole::DefenderRight;
        wm->ourRobot[actives.takeFirst()].Role = AgentRole::AttackerMid;
        wm->ourRobot[actives.takeFirst()].Role = AgentRole::AttackerLeft;
        break;
    case 5:
        wm->ourRobot[actives.takeFirst()].Role = AgentRole::DefenderLeft;
        wm->ourRobot[actives.takeFirst()].Role = AgentRole::DefenderRight;
        wm->ourRobot[actives.takeFirst()].Role = AgentRole::AttackerMid;
        wm->ourRobot[actives.takeFirst()].Role = AgentRole::AttackerLeft;
        wm->ourRobot[actives.takeFirst()].Role = AgentRole::AttackerRight;
        break;
    default:
        break;
    }

    QList <int> activeRobots = wm->kn->ActiveAgents();

    for (int i = 0; i < activeRobots.size(); i++)
        wm->ourRobot[activeRobots.at(i)].Status = AgentStatus::Idle;

    for (int i = 0; i < activeRobots.size(); i++)
    {
        int index = activeRobots.at(i);

        switch (wm->ourRobot[index].Role) {
        case AgentRole::Golie:
            tactics[index] = tGoalie;
            break;
        case AgentRole::DefenderLeft:
            tactics[index] = tDefenderLeft;
            tDefenderLeft->resetBooleans(); //??
            break;
        case AgentRole::DefenderRight:
            tactics[index] = tDefenderRight;
            tDefenderRight->resetBooleans(); //??
            break;
        case AgentRole::AttackerMid:
            tactics[index] = tStopMid;
            break;
        case AgentRole::AttackerLeft:
            tactics[index] = tStopLeft;
            break;
        case AgentRole::AttackerRight:
            tactics[index] = tStopRight;
            break;
        default:
            break;
        }
    }

    Position leftDefPos,rightDefPos,goaliePos;
    int leftID = -1, rightID = -1 , midID = -1;
    bool leftNav, rightNav;

    if( wm->ourRobot[previousLeftID].Role != AgentRole::DefenderLeft )
        previousLeftID = -1;

    if( wm->ourRobot[previousRightID].Role != AgentRole::DefenderRight )
        previousRightID = -1;

    if( (wm->ourRobot[tDefenderLeft->getID()].Role == AgentRole::DefenderLeft) && (leftChecker < PresenceCounter) )
    {
        leftID = tDefenderLeft->getID();
        this->previousLeftID = tDefenderLeft->getID();;
    }

    if( wm->ourRobot[tDefenderRight->getID()].Role == AgentRole::DefenderRight && (rightChecker < PresenceCounter) )
    {
        rightID = tDefenderRight->getID();
        this->previousRightID = tDefenderRight->getID();;
    }

    if( leftChecker > PresenceCounter || leftID == -1 )
        midID = rightID;

    if( rightChecker > PresenceCounter  || rightID == -1)
        midID = leftID;

    zonePositions(leftID,rightID,midID,goaliePos,leftDefPos,leftNav,rightDefPos,rightNav);

    tDefenderLeft->setIdlePosition(leftDefPos);
    tDefenderLeft->setUseNav(leftNav);
    tDefenderRight->setIdlePosition(rightDefPos);
    tDefenderRight->setUseNav(rightNav);

    if( leftID != -1)
    {
        if( (wm->ourRobot[leftID].Status != AgentStatus::FollowingBall ) && (wm->ourRobot[leftID].pos.loc - leftDefPos.loc).length() > 250 )
            leftChecker++;
        else
            leftChecker = 0;
    }
    else
    {
        if( !haltedRobotIsInField(previousLeftID) )
            leftChecker = 0;
    }

    if( rightID != -1)
    {
        if( (wm->ourRobot[rightID].Status != AgentStatus::FollowingBall ) && (wm->ourRobot[rightID].pos.loc - rightDefPos.loc).length() > 250 )
            rightChecker++;
        else
            rightChecker = 0;
    }
    else
    {
        if( !haltedRobotIsInField(previousRightID) )
            rightChecker = 0;
    }

    tGoalie->setIdlePosition(goaliePos);

    if (wm->kn->IsInsideGolieArea(wm->ball.pos.loc))
    {
        tStopMid->setStopPosition({Field::ourGoalCenter.x + 2250, 0});
        tStopLeft->setStopPosition({Field::ourGoalCenter.x + 2250, 1250});
        tStopRight->setStopPosition({Field::ourGoalCenter.x + 2250, -1250});
    }
    else if (wm->ball.pos.loc.x < Field::ourGoalCenter.x + (Field::MaxX * 2) / 3)
    {
        Segment2D seg(Field::ourGoalCenter, wm->ball.pos.loc);
        Circle2D ballcir(wm->ball.pos.loc, ALLOW_NEAR_BALL_RANGE);
        Vector2D fdot, sdot;
        ballcir.intersection(seg, &fdot, &sdot);

        Circle2D goalieCir (Field::ourGoalCenter, 1300);
        Line2D linetest (Field::ourGoalCenter, wm->ball.pos.loc);
        if (wm->kn->IsInsideGolieArea(fdot))
        {
            goalieCir.intersection(linetest, &fdot, &sdot);
            if (fdot.x < sdot.x)
                fdot = sdot;
        }

        tStopMid->setStopPosition(fdot);

        tactics[tStopLeft->getID()] = tAttackerLeft;
        tactics[tStopRight->getID()] = tAttackerRight;

        Marking def;
        def.setWorldModel(wm); //??
        bool isMatched;
        QList <int> opp = wm->kn->ActiveOppAgents();
        QList <int> our;
        our.append(tAttackerLeft->getID());
        our.append(tAttackerRight->getID());
        QList <Marking_Struct> m2m = def.findMarking(our , opp, isMatched);
        if (isMatched)
        {
            for (int i = 0; i < m2m.size(); i++)
            {
                wm->ourRobot[m2m.at(i).ourI].Status = AgentStatus::BlockingRobot;

                switch (wm->ourRobot[m2m.at(i).ourI].Role) {
                case AgentRole::DefenderLeft:
                    tDefenderLeft->setPlayerToKeep(m2m.at(i).oppI);
                    break;
                case AgentRole::DefenderRight:
                    tDefenderRight->setPlayerToKeep(m2m.at(i).oppI);
                    break;
                case AgentRole::AttackerLeft:
                    tAttackerLeft->setPlayerToKeep(m2m.at(i).oppI);
                    break;
                case AgentRole::AttackerRight:
                    tAttackerRight->setPlayerToKeep(m2m.at(i).oppI);
                    break;
                default:
                    break;
                }
            }
        }
    }
    else if (wm->ball.pos.loc.x < Field::ourGoalCenter.x + (Field::MaxX * 2)* 2 / 3)
    {
        Vector2D fPosAttMid, fPosAttLeft, fPosAttRight, sec;
        double slope, degree, deltaa;
        slope = (wm->ball.pos.loc.y - Field::ourGoalCenter.y) / (wm->ball.pos.loc.x - Field::ourGoalCenter.x);
        degree = atan(slope);
        deltaa = 2 * asin( ROBOT_RADIUS / ALLOW_NEAR_BALL_RANGE );
        AngleDeg deg(degree * 57.32), delta(deltaa * 57.32);
        AngleDeg leftAttDeg, rightAttDeg;
        leftAttDeg = operator -(deg, delta);
        rightAttDeg = operator +(deg, delta);
        Line2D leftAttLine(wm->ball.pos.loc, leftAttDeg.degree() - 1.5);
        Line2D rightAttLine(wm->ball.pos.loc, rightAttDeg.degree() + 1.5);
        Circle2D cir(wm->ball.pos.loc, ALLOW_NEAR_BALL_RANGE);
        cir.intersection(leftAttLine, &fPosAttLeft, &sec);
        if (sec.x < fPosAttLeft.x)
            fPosAttLeft = sec;
        cir.intersection(rightAttLine, &fPosAttRight, &sec);
        if (sec.x < fPosAttRight.x)
            fPosAttRight = sec;

        tStopLeft->setStopPosition(fPosAttLeft);
        tStopRight->setStopPosition(fPosAttRight);

        Segment2D seg(Field::ourGoalCenter, wm->ball.pos.loc);
        Circle2D ballcir(wm->ball.pos.loc, ALLOW_NEAR_BALL_RANGE);
        Vector2D fdot, sdot;
        ballcir.intersection(seg, &fdot, &sdot);
        tStopMid->setStopPosition(fdot);
    }
    else if (Field::ourGoalCenter.x + (Field::MaxX * 2)* 2 / 3 < wm->ball.pos.loc.x)
    {
        Segment2D seg(Field::ourGoalCenter, wm->ball.pos.loc);
        Circle2D ballcir(wm->ball.pos.loc, ALLOW_NEAR_BALL_RANGE);
        Vector2D fdot, sdot;
        ballcir.intersection(seg, &fdot, &sdot);
        tStopMid->setStopPosition(fdot);

        tStopLeft->setStopPosition({wm->ball.pos.loc.x - 2250, 1250});
        tStopRight->setStopPosition({wm->ball.pos.loc.x - 2250, -1250});
    }
*/

    /*if (c == -1)
    {
        tTest1->setpos( Vector2D(-1500, 250) );
        tactics[2] = tTest1;
        tTest2->setpos( Vector2D(-1750, 250) );
        tactics[3] = tTest2;
        tTest3->setpos( Vector2D(-2000, 250) );
        tactics[4] = tTest3;
//        tTest4->setpos( Vector2D(-1250, 250) );
//        tactics[3] = tTest4;
    }
    if ( (wm->ourRobot[2].pos.loc - Vector2D(-1500, 250)).length() < 80
           && (wm->ourRobot[3].pos.loc - Vector2D(-1750, 250)).length() < 80
           && (wm->ourRobot[4].pos.loc - Vector2D(-2000, 250)).length() < 80
           //&& (wm->ourRobot[3].pos.loc - Vector2D(-1250, 250)).length() < 80
         )
    {
        c = 0;
        cout << "bbbbb";
    }

    if (c == 0 && t == 0)
    {
        tTest1->setpos( Vector2D(-1250, 250) );
        tactics[2] = tTest1;
    }
    if (  (wm->ourRobot[2].pos.loc - Vector2D(-1250, 250)).length() < 80 && t == 0)
        c = 1;

    if (c == 1 && t == 0)
    {
        tTest1->setpos( Vector2D(-1250, 1750) );
        tactics[2] = tTest1;
    }
    if ( (wm->ourRobot[2].pos.loc - Vector2D(-1250, 1750)).length() < 80 && t == 0)
        c = 2;

    if (c == 2 && t == 0)
    {
        tTest1->setpos( Vector2D(-3250, 1750) );
        tactics[2] = tTest1;
    }
    if ( (wm->ourRobot[2].pos.loc - Vector2D(-3250, 1750)).length() < 80 && t == 0)
        c = 3;

    if (c == 3 && t == 0)
    {
        tTest1->setpos( Vector2D(-3250, 1750) );
        tactics[2] = tTest1;
    }
    if ( (wm->ourRobot[2].pos.loc - Vector2D(-3250, 1750)).length() < 80 && t == 0)
        c = 4;

    if (c == 4 && t == 0)
    {
        tTest1->setpos( Vector2D(-3250, -1750) );
        tactics[2] = tTest1;
    }
    if ( (wm->ourRobot[2].pos.loc - Vector2D(-3250, -1750)).length() < 80 && t == 0)
        c = 5;

    if (c == 5 && t == 0)
    {
        tTest1->setpos( Vector2D(-1250, -1750) );
        tactics[2] = tTest1;
    }
    if ( (wm->ourRobot[2].pos.loc - Vector2D(-1250, -1750)).length() < 80 && t == 0)
        c = 6;

    if (c == 6 && t == 0)
    {
        tTest1->setpos( Vector2D(-1250, -250) );
        tactics[2] = tTest1;
    }
    if ( (wm->ourRobot[2].pos.loc - Vector2D(-1250, -250)).length() < 80 && t == 0)
        c = 7;

    if (c == 7 && t == 0)
    {
        tTest1->setpos( Vector2D(-2250, -250) );
        tactics[2] = tTest1;
    }
    if ( (wm->ourRobot[2].pos.loc - Vector2D(-2250, -250)).length() < 80  && t == 0)
    {
        c = 8;
        t = 1;
    }
//
    if (c == 8 && t == 1)
    {
        tTest2->setpos( Vector2D(-1250, 250) );
        tactics[3] = tTest2;
    }
    if (  (wm->ourRobot[3].pos.loc - Vector2D(-1250, 250)).length() < 80  && t == 1)
        c = 9;

    if (c == 9 && t == 1)
    {
        tTest2->setpos( Vector2D(-1250, 1750) );
        tactics[3] = tTest2;
    }
    if ( (wm->ourRobot[3].pos.loc - Vector2D(-1250, 1750)).length() < 80 && t == 1)
        c = 10;

    if (c == 10 && t == 1)
    {
        tTest2->setpos( Vector2D(-3250, 1750) );
        tactics[3] = tTest2;
    }
    if ( (wm->ourRobot[3].pos.loc - Vector2D(-3250, 1750)).length() < 80 && t == 1)
        c = 11;

    if (c == 11 && t == 1)
    {
        tTest2->setpos( Vector2D(-3250, 1750) );
        tactics[3] = tTest2;
    }
    if ( (wm->ourRobot[3].pos.loc - Vector2D(-3250, 1750)).length() < 80 && t == 1)
        c = 12;

    if (c == 12 && t == 1)
    {
        tTest2->setpos( Vector2D(-3250, -1750) );
        tactics[3] = tTest2;
    }
    if ( (wm->ourRobot[3].pos.loc - Vector2D(-3250, -1750)).length() < 80 && t == 1)
        c = 13;

    if (c == 13 && t == 1)
    {
        tTest2->setpos( Vector2D(-1250, -1750) );
        tactics[3] = tTest2;
    }
    if ( (wm->ourRobot[3].pos.loc - Vector2D(-1250, -1750)).length() < 80 && t == 1)
        c = 14;

    if (c == 14 && t == 1)
    {
        tTest2->setpos( Vector2D(-1250, -250) );
        tactics[3] = tTest2;
    }
    if ( (wm->ourRobot[3].pos.loc - Vector2D(-1250, -250)).length() < 80 && t == 1)
        c = 15;

    if (c == 15 && t == 1)
    {
        tTest2->setpos( Vector2D(-2000, -250) );
        tactics[3] = tTest2;
    }
    if ( (wm->ourRobot[3].pos.loc - Vector2D(-2000, -250)).length() < 80 && t == 1 )
    {
        c = 16;
        t = 2;
    }
//
    if (c == 16 && t == 2)
    {
        tTest3->setpos( Vector2D(-1250, 250) );
        tactics[4] = tTest3;
    }
    if (  (wm->ourRobot[4].pos.loc - Vector2D(-1250, 250)).length() < 80 && t == 2)
        c = 17;

    if (c == 17 && t == 2)
    {
        tTest3->setpos( Vector2D(-1250, 1750) );
        tactics[4] = tTest3;
    }
    if ( (wm->ourRobot[4].pos.loc - Vector2D(-1250, 1750)).length() < 80 && t == 2)
        c = 18;

    if (c == 18 && t == 2)
    {
        tTest3->setpos( Vector2D(-3250, 1750) );
        tactics[4] = tTest3;
    }
    if ( (wm->ourRobot[4].pos.loc - Vector2D(-3250, 1750)).length() < 80 && t == 2)
        c = 19;

    if (c == 19 && t == 2)
    {
        tTest3->setpos( Vector2D(-3250, 1750) );
        tactics[4] = tTest3;
    }
    if ( (wm->ourRobot[4].pos.loc - Vector2D(-3250, 1750)).length() < 80 && t == 2)
        c = 20;

    if (c == 20 && t == 2)
    {
        tTest3->setpos( Vector2D(-3250, -1750) );
        tactics[4] = tTest3;
    }
    if ( (wm->ourRobot[4].pos.loc - Vector2D(-3250, -1750)).length() < 80 && t == 2)
        c = 21;

    if (c == 21 && t == 2)
    {
        tTest3->setpos( Vector2D(-1250, -1750) );
        tactics[4] = tTest3;
    }
    if ( (wm->ourRobot[4].pos.loc - Vector2D(-1250, -1750)).length() < 80 && t == 2)
        c = 22;

    if (c == 22 && t == 2)
    {
        tTest3->setpos( Vector2D(-1250, -250) );
        tactics[4] = tTest3;
    }
    if ( (wm->ourRobot[4].pos.loc - Vector2D(-1250, -250)).length() < 80 && t == 2)
        c = 23;

    if (c == 23 && t == 2)
    {
        tTest3->setpos( Vector2D(-1750, -250) );
        tactics[4] = tTest3;
    }
    if ( (wm->ourRobot[4].pos.loc - Vector2D(-1750, -250)).length() < 80 && t == 2)
    {
        c = 24;
        t = 3;
    }
//
/*
    if (c == 24 && t == 3)
    {
        tTest4->setpos( Vector2D(-250, 250) );
        tactics[3] = tTest4;
    }
    if (  (wm->ourRobot[3].pos.loc - Vector2D(-250, 250)).length() < 50 && t == 3)
        c = 25;

    if (c == 25 && t == 3)
    {
        tTest4->setpos( Vector2D(-250, 2750) );
        tactics[3] = tTest4;
    }
    if ( (wm->ourRobot[3].pos.loc - Vector2D(-250, 2750)).length() < 50 && t == 3)
        c = 26;

    if (c == 26 && t == 3)
    {
        tTest4->setpos( Vector2D(-4250, 2750) );
        tactics[3] = tTest4;
    }
    if ( (wm->ourRobot[3].pos.loc - Vector2D(-4250, 2750)).length() < 50 && t == 3)
        c = 27;

    if (c == 27 && t == 3)
    {
        tTest4->setpos( Vector2D(-4250, 2750) );
        tactics[3] = tTest4;
    }
    if ( (wm->ourRobot[3].pos.loc - Vector2D(-4250, 2750)).length() < 50 && t == 3)
        c = 28;

    if (c == 28 && t == 3)
    {
        tTest4->setpos( Vector2D(-4250, -2750) );
        tactics[3] = tTest4;
    }
    if ( (wm->ourRobot[3].pos.loc - Vector2D(-4250, -2750)).length() < 50 && t == 3)
        c = 29;

    if (c == 29 && t == 3)
    {
        tTest4->setpos( Vector2D(-250, -2750) );
        tactics[3] = tTest4;
    }
    if ( (wm->ourRobot[3].pos.loc - Vector2D(-250, -2750)).length() < 50 && t == 3)
        c = 30;

    if (c == 30 && t == 3)
    {
        tTest4->setpos( Vector2D(-250, -250) );
        tactics[3] = tTest4;
    }
    if ( (wm->ourRobot[3].pos.loc - Vector2D(-250, -250)).length() < 50 && t == 3)
        c = 31;

    if (c == 31 && t == 3)
    {
        tTest4->setpos( Vector2D(-500, -250) );
        tactics[3] = tTest4;
    }
    if ( (wm->ourRobot[3].pos.loc - Vector2D(-500, -250)).length() < 50 && t == 3)
        c = 32;
*/
   // cout << c << endl;

    //tTest1->setpos( Vector2D (-1000, 0) );
    //tactics[2] = tTest1;

    //tTest1->setpos( Vector2D(-1000, 0) );
    //tactics[0] = tTest1;

  //  wm->debug_type=2;
   // wm->debug_pos.append(wm->ball.pos.loc);
//    for(int i=0;i<wm->kn->ActiveAgents().length();i++){
//        tactics[wm->kn->ActiveAgents()[i]] = tTest;
//    }
    //wm->debug_pos.clear();
    //wm->debug_pos.append(Vector2D (0,0));
}
