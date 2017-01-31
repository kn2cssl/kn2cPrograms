#include "playtest2.h"

PlayTest2::PlayTest2(WorldModel *worldmodel, QObject *parent) :
    Play("PlayTest2", worldmodel, parent)
{
    tTest = new TacticTest2(wm);
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
    if(wm->gs == STATE_Stop){
        tactics[wm->ref_goalie_our] = tTest;
        //step1
        if(wm->kn->ActiveAgents().size() == 3){
            tactics[wm->kn->ActiveAgents()[0]] = tTest;
            tactics[wm->kn->ActiveAgents()[1]] = tTest;
            tactics[wm->kn->ActiveAgents()[2]] = tTest;
        }
        if(wm->kn->ActiveAgents().size() == 4){
            tactics[wm->kn->ActiveAgents()[0]] = tTest;
            tactics[wm->kn->ActiveAgents()[1]] = tTest;
            tactics[wm->kn->ActiveAgents()[2]] = tTest;
            tactics[wm->kn->ActiveAgents()[3]] = tTest;
        }
        if(wm->kn->ActiveAgents().size() == 5){
            tactics[wm->kn->ActiveAgents()[0]] = tTest;
            tactics[wm->kn->ActiveAgents()[1]] = tTest;
            tactics[wm->kn->ActiveAgents()[2]] = tTest;
            tactics[wm->kn->ActiveAgents()[3]] = tTest;
            tactics[wm->kn->ActiveAgents()[4]] = tTest;
        }
        if(wm->kn->ActiveAgents().size() == 6){
            tactics[wm->kn->ActiveAgents()[0]] = tTest;
            tactics[wm->kn->ActiveAgents()[1]] = tTest;
            tactics[wm->kn->ActiveAgents()[2]] = tTest;
            tactics[wm->kn->ActiveAgents()[3]] = tTest;
            tactics[wm->kn->ActiveAgents()[4]] = tTest;
            tactics[wm->kn->ActiveAgents()[5]] = tTest;
        }
    }
    if(wm->gs == STATE_Halt){
        for(int i = 0 ; i < wm->kn->ActiveAgents().size() ; i++){
            tactics[i] = new TacticHalt(wm);
        }
    }
    if(wm->gs == STATE_Free_kick_Opp){
        tactics[wm->ref_goalie_our] = tTest;
    }
    if(wm->gs == STATE_Free_kick_Our){
        tactics[0] = (Tactic*) (new TacticTest(wm));
    }
    for(int i=0;i<wm->kn->ActiveAgents().length();i++){
        tactics[wm->kn->ActiveAgents()[i]] = tTest;
    }
    wm->debug_pos.clear();
//    if(wm->ball.isValid){
//        wm->debug_pos.append(wm->ball.pos.loc);
//        qDebug()<<"x :"<<wm->ball.pos.loc.x;
//        qDebug()<<"y :"<<wm->ball.pos.loc.y<<"\n\n";
//    }
}

//Vector2D PlayTest2::generatePos(int radius,double alpha){
//    return Vector2D(wm->ball.pos.loc.x + radius*std::sin()
//}
