#include "playtest2.h"

PlayTest2::PlayTest2(WorldModel *worldmodel, QObject *parent) :
    Play("PlayTest2", worldmodel, parent)
{
    tTest1 = new TacticTest2(wm);
}

int PlayTest2::enterCondition()
{
    return 0;
}

int PlayTest2::Parabola_intersection(Vector2D site1, Vector2D site2, double l, Vector2D *v1, Vector2D *v2)
{
    double a1, b1, c1;
    double a2, b2, c2;
    double a, b, c;
    double delta;

    a1 = 0.5 / (site1.y - l);
    b1 = site1.x / (l - site1.y);
    c1 = ( 0.5 * (site1.y + l) ) + ( 0.5 * site1.x * site1.x / (site1.y -l) );
    //cout << a1 << "||" << b1 << "||" << c1 << endl;

    a2 = 0.5 / (site2.y - l);
    b2 = site2.x / (l - site2.y);
    c2 = ( 0.5 * (site2.y + l) ) + ( 0.5 * site2.x * site2.x / (site2.y -l) );
    //cout << a2 << "||" << b2 << "||" << c2 << endl;

    a = a1 - a2;
    b = b1 - b2;
    c = c1 - c2;
    //cout << a << "||" << b << "||" << c << endl;

    delta = b * b - 4 * a * c;

    if (a == 0)
    {
        if (b == 0)
            return 0;
        else
        {
            v1->x = (-1) * c / b;
            v1->y = a1 * v1->x * v1->x + b1 * v1->x + c1;

            return 1;
        }
    }
    else
    {
        if (delta > 0)
        {
            v1->x = ( (-1) * b - sqrt(delta) ) / (2 * a);
            v1->y = a1 * v1->x * v1->x + b1 * v1->x + c1;
            v2->x = ( (-1) * b + sqrt(delta) ) / (2 * a);
            v2->y = a1 * v2->x * v2->x + b1 * v2->x + c1;

            return 2;
        }
        else if (delta == 0)
        {
            v1->x = ((-1) * b) / (2 * a);
            v1->y = a1 * v1->x * v1->x + b1 * v1->x + c1;

            return 1;
        }
        else
            return 0;
    }
}

void PlayTest2::initRole()
{

}


void PlayTest2::execute()
{

    //QList <int> order;
    Vector2D t[3][2];

    QList <int> activeopp = wm->kn->ActiveOppAgents();

    int s = 1;

    for (int i = 0; i < activeopp.size() - 1; i++)
        for (int j = 0; j < activeopp.size() - 1; j++)
            if (wm->oppRobot[ activeopp.at(j) ].pos.loc.x > wm->oppRobot[ activeopp.at(j+1) ].pos.loc.x)
                activeopp.move(j, j + 1);

    for (double l = 3000; l >= -6000; l = l - 0.5)
    {
        QList <int> order;

        for (int i = 0; i < activeopp.size() ; i++)
            if (wm->oppRobot[ activeopp.at(i) ].pos.loc.y > l)
                order.append( activeopp.at(i) );

//G

/*
        if (l == -1200)
        {
            Parabola_intersection(wm->oppRobot[ order.at(0) ].pos.loc, wm->oppRobot[ order.at(2) ].pos.loc, l,
                    &t[0][0], &t[0][1]);
            Parabola_intersection(wm->oppRobot[ order.at(0) ].pos.loc, wm->oppRobot[ order.at(1) ].pos.loc, l,
                    &t[1][0], &t[1][1]);
            Parabola_intersection(wm->oppRobot[ order.at(1) ].pos.loc, wm->oppRobot[ order.at(2) ].pos.loc, l,
                    &t[2][0], &t[2][1]);

            cout << "t[0][0].x = " << t[0][0].x << "||" << "t[0][0].y = " << t[0][0].y << endl;
            cout << "t[0][1].x = " << t[0][1].x << "||" << "t[0][1].y = " << t[0][1].y << endl;
            cout << "t[1][0].x = " << t[1][0].x << "||" << "t[1][0].y = " << t[1][0].y << endl;
            cout << "t[1][1].x = " << t[1][1].x << "||" << "t[1][1].y = " << t[1][1].y << endl;
            cout << "t[2][0].x = " << t[2][0].x << "||" << "t[2][0].y = " << t[2][0].y << endl;
            cout << "t[2][1].x = " << t[2][1].x << "||" << "t[2][1].y = " << t[2][1].y << endl;

            for (int j = 0; j < 3; j++)
                for (int k = 0; k < 3 && k!=j; k++)
                    for (int m = 0; m < 2; m++)
                    {
                        if ( t[j][m].dist(t[k][0]) < 100 && t[j][m].x != 0 && t[j][m].y != 0)
                        {
                            wm->debug_pos.append(t[j][m]);
                            cout << t[j][m].x << "**" << t[j][m].y << endl;
                            cout << l << endl;
                        }
                        if ( t[j][m].dist(t[k][1]) < 100 && t[j][m].x != 0 && t[j][m].y != 0)
                        {
                            wm->debug_pos.append(t[j][m]);
                            cout << t[j][m].x << "**" << t[j][m].y << endl;
                            cout << l << endl;
                        }
                    }
        }
*/



        if (order.size() > 2)
        {
/*
            for (int i = 0; i < order.size() - 2; i++)
            {
                Parabola_intersection(wm->oppRobot[ order.at(i) ].pos.loc, wm->oppRobot[ order.at(i+2) ].pos.loc, l,
                        &t[0][0], &t[0][1]);
                Parabola_intersection(wm->oppRobot[ order.at(i) ].pos.loc, wm->oppRobot[ order.at(i+1) ].pos.loc, l,
                        &t[1][0], &t[1][1]);
                Parabola_intersection(wm->oppRobot[ order.at(i+1) ].pos.loc, wm->oppRobot[ order.at(i+2) ].pos.loc, l,
                        &t[2][0], &t[2][1]);
*/
            for (int a = 0; a < order.size()-2; a++)
                for (int b = a+1; b < order.size()-1; b++)
                    for (int c = b+1; c < order.size(); c++)
            {
                Parabola_intersection(wm->oppRobot[ order.at(a) ].pos.loc, wm->oppRobot[ order.at(b) ].pos.loc, l,
                                &t[0][0], &t[0][1]);
                Parabola_intersection(wm->oppRobot[ order.at(b) ].pos.loc, wm->oppRobot[ order.at(c) ].pos.loc, l,
                                &t[1][0], &t[1][1]);
                Parabola_intersection(wm->oppRobot[ order.at(a) ].pos.loc, wm->oppRobot[ order.at(c) ].pos.loc, l,
                                &t[2][0], &t[2][1]);
/*
                for (int j = 0; j < 3; j++)
                    for (int k = 0; k < 2; k++)
                        wm->debug_pos.append(t[j][k]);
*/

                for (int j = 0; j < 3; j++)
                    for (int k = 0; k < 3 && k!=j; k++)
                        for (int m = 0; m < 2; m++)
                        {
                            if ( t[j][m].dist(t[k][0]) < 8 && t[j][m].x != 0 && t[j][m].y != 0)
                            {
                                s = 1;
                                for (int i = 0; i < order.size(); i++)
                                    if ( i != a && i != b && i != c)
                                        if ( t[j][m].dist(wm->oppRobot[ order.at(i) ].pos.loc) < t[j][m].dist(wm->oppRobot[ order.at(a) ].pos.loc))
                                            s = 0;
                                if (s == 1)
                                    wm->debug_pos.append(t[j][m]);
                                //cout << t[j][m].x << "**" << t[j][m].y << endl;
                                //cout << l << endl;
                            }
                            if ( t[j][m].dist(t[k][1]) < 8 && t[j][m].x != 0 && t[j][m].y != 0)
                            {
                                s = 1;
                                for (int i = 0; i < order.size(); i++)
                                    if ( i != a && i != b && i != c)
                                        if ( t[j][m].dist(wm->oppRobot[ order.at(i) ].pos.loc) < t[j][m].dist(wm->oppRobot[ order.at(a) ].pos.loc))
                                            s = 0;
                                if (s == 1)
                                    wm->debug_pos.append(t[j][m]);
                                //cout << t[j][m].x << "**" << t[j][m].y << endl;
                                //cout << l << endl;
                            }
                        }

            }
        }

//10 --> 49
//5  --> 24
//2  --> 10
//1  --> 4 line --> 10 dot
//0.5 --> 2 line --> 6 --> 4
//0.2 --> 1 --> 1

    }

    //wm->debug_pos.clear();

/*
    Vector2D first, second;
    double a1, b1, c1;
    double l = -1450;

    Vector2D site1 = wm->oppRobot[1].pos.loc;
    a1 = 0.5 / (site1.y - l);
    b1 = site1.x / (l - site1.y);
    c1 = ( 0.5 * (site1.y + l) ) + ( 0.5 * site1.x * site1.x / (site1.y -l) );
    for (int x = -4500; x <= 4500; x++)
    {
        first.x = x;
        first.y = a1 * x * x + b1 * x + c1;
        wm->debug_pos.append(first);
    }

    site1 = wm->oppRobot[4].pos.loc;
    a1 = 0.5 / (site1.y - l);
    b1 = site1.x / (l - site1.y);
    c1 = ( 0.5 * (site1.y + l) ) + ( 0.5 * site1.x * site1.x / (site1.y -l) );
    for (int x = -4500; x <= 4500; x++)
    {
        first.x = x;
        first.y = a1 * x * x + b1 * x + c1;
        wm->debug_pos.append(first);
    }

    site1 = wm->oppRobot[5].pos.loc;
    a1 = 0.5 / (site1.y - l);
    b1 = site1.x / (l - site1.y);
    c1 = ( 0.5 * (site1.y + l) ) + ( 0.5 * site1.x * site1.x / (site1.y -l) );
    for (int x = -4500; x <= 4500; x++)
    {
        first.x = x;
        first.y = a1 * x * x + b1 * x + c1;
        wm->debug_pos.append(first);
    }

    Vector2D lp;
    lp.y = l;
    for (int x = -4500; x <= 4500; x++)
    {
        lp.x = x;
        wm->debug_pos.append(lp);
    }
*/

    /*
    Vector2D a = {-1000,1000}, b = {0,1000}, c, d;
    double l = 0;
    Parabola_intersection(a, b, l, &c, &d);
    cout << "c.x:" << c.x << "||||" << "c.y:" << c.y << endl;
    cout << "d.x:" << d.x << "||||" << "d.y:" << d.y << endl;
    */

    //tactics[2] = tTest1;
}

