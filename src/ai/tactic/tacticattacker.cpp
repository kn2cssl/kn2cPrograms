#include "tacticattacker.h"


TacticAttacker::TacticAttacker(WorldModel *worldmodel, QObject *parent) :
    Tactic("TacticAttacker", worldmodel, parent)
{
    numberOfInvalidRanges=0;
    numberOfValidRanges=0;
    canKick=false;

    //--------------------------------
    kicker_canKick = false;
    kicker_firstKick = false;
    kicker_kicked = false;
    kicker_timer = new QTimer();
    connect(kicker_timer,SIGNAL(timeout()),this,SLOT(timerEvent()));
}

RobotCommand TacticAttacker::getCommand()
{
    RobotCommand rc;
    if(!wm->ourRobot[id].isValid) return rc;

    if(wm->ourRobot[id].Role == AgentRole::AttackerLeft)
    {
        rc.maxSpeed = 1.5;

        rc=goBehindBall();

        if(canKick && wm->cmgs.canKickBall())
        {
            rc.kickspeedx=5;
        }

        rc.useNav = true;
        rc.isBallObs = false;
        rc.isKickObs = true;

    }
    else if(wm->ourRobot[id].Status == AgentStatus::Passing)
    {
        rc.maxSpeed = 2;

        if(!kicker_kicked)
        {
            if(!kicker_firstKick)
            {
                rc = goBehindBall();

                if(wm->kn->CanKick(wm->ourRobot[id].pos,wm->ball.pos.loc))
                {
                    kicker_timer->start(300);
                    rc.kickspeedx = 2.5;//50;
                    kicker_firstKick = true;
                }
            }
            else
            {
                rc.fin_pos = wm->ourRobot[id].pos;
            }
        }
        else
        {
            rc.fin_pos = wm->ourRobot[id].pos;
        }

        rc.useNav = true;
        rc.isBallObs = true;
        rc.isKickObs = true;
    }
    else if(wm->ourRobot[id].Status == AgentStatus::RecievingPass)
    {
        canKick=false;
        rc.maxSpeed = 2;

        if(go)
        {
            if(state == 0)
            {
                Vector2D v;
                v = wm->kn->PredictDestination(wm->ourRobot[this->id].pos.loc,
                        wm->ball.pos.loc,rc.maxSpeed,wm->ball.vel.loc);
                Position p = wm->kn->AdjustKickPoint(v, Field::oppGoalCenter);

                rc.fin_pos = p;

                if(wm->kn->IsReadyForKick(wm->ourRobot[id].pos, p, wm->ball.pos.loc))
                {
                    rc.kickspeedx = 5;//150;
                }
            }
            else if(state == 1)
            {
                rc = goBehindBall();
                if(canKick)
                {
                    rc.kickspeedx = 5;
                }
            }
        }
        else
        {
            rc.fin_pos = wm->ourRobot[id].pos;
        }

        rc.useNav = true;
        rc.isBallObs = true;
        rc.isKickObs = true;
    }
    else if(wm->ourRobot[id].Status == AgentStatus::Idle)
    {
        rc.fin_pos = wm->ourRobot[id].pos;
    }

    return rc;
}

void TacticAttacker::findCriticalPlayer()
{
    QList<int> our_agents = wm->kn->ActiveAgents();
    important_opp_agents.clear();
    important_our_agents.clear();

    //---------ActiveOppAgents
    QList<int> opp_agents;
    for(int i=0; i< PLAYERS_MAX_NUM; i++)
        if(wm->oppRobot[i].isValid)
            opp_agents.append(i);
    //---------------------

    QList<int> active_our_agents;
    QList<int> active_opp_agents;

    foreach(int i,our_agents)
    {
        if(wm->ourRobot[i].pos.loc.x>wm->ourRobot[id].pos.loc.x)
        {
            active_our_agents.append(i);
        }
    }

    foreach(int i,opp_agents)
    {
        if(wm->oppRobot[i].pos.loc.x>wm->ourRobot[id].pos.loc.x)
        {
            active_opp_agents.append(i);
        }
    }

    Line2D down(Field::oppGoalPost_R,wm->ball.pos.loc);
    Line2D up(Field::oppGoalPost_L,wm->ball.pos.loc);

    foreach (int i, active_opp_agents)
    {
        double Ymin=wm->ball.pos.loc.y+(-down.a()/down.b())*(wm->oppRobot[i].pos.loc.x-wm->ball.pos.loc.x);
        double Ymax=wm->ball.pos.loc.y+tan(-up.a()/up.b())*(wm->oppRobot[i].pos.loc.x-wm->ball.pos.loc.x);

        if(wm->oppRobot[i].pos.loc.y>Ymin && wm->oppRobot[i].pos.loc.y<Ymax)
        {
            important_opp_agents.append(i);
        }
    }

    foreach (int i, active_our_agents)
    {
        double Ymin=wm->ball.pos.loc.y+(-down.a()/down.b())*(wm->ourRobot[i].pos.loc.x-wm->ball.pos.loc.x);
        double Ymax=wm->ball.pos.loc.y+tan(-up.a()/up.b())*(wm->ourRobot[i].pos.loc.x-wm->ball.pos.loc.x);

        if(wm->ourRobot[i].pos.loc.y>Ymin && wm->ourRobot[i].pos.loc.y<Ymax)
        {
            important_our_agents.append(i);
        }
    }
}

void TacticAttacker::findInvalidRanges()
{
    numberOfInvalidRanges=0;
    uGoal=(atan( (Field::oppGoalPost_L.y-wm->ball.pos.loc.y)/(Field::oppGoalPost_L.x-wm->ball.pos.loc.x)));
    dGoal=(atan( (Field::oppGoalPost_R.y-wm->ball.pos.loc.y)/(Field::oppGoalPost_R.x-wm->ball.pos.loc.x)));
    foreach (int i, important_opp_agents)
    {
        double alpha=asin(ROBOT_RADIUS/wm->ball.pos.loc.dist(wm->oppRobot[i].pos.loc));
        double beta=atan((wm->oppRobot[i].pos.loc.y-wm->ball.pos.loc.y)/(wm->oppRobot[i].pos.loc.x-wm->ball.pos.loc.x));
        angle[numberOfInvalidRanges][1]=beta+alpha;
        angle[numberOfInvalidRanges][0]=beta-alpha;
        numberOfInvalidRanges++;
    }
    foreach (int i, important_our_agents)
    {
        double alpha=asin(ROBOT_RADIUS/wm->ball.pos.loc.dist(wm->ourRobot[i].pos.loc));
        double beta=atan((wm->ourRobot[i].pos.loc.y-wm->ball.pos.loc.y)/(wm->ourRobot[i].pos.loc.x-wm->ball.pos.loc.x));
        angle[numberOfInvalidRanges][1]=beta+alpha;
        angle[numberOfInvalidRanges][0]=beta-alpha;
        numberOfInvalidRanges++;
    }
}

void TacticAttacker::sortInvalidRanges()
{
    for(int i=0;i<numberOfInvalidRanges;i++)
    {
        for(int j=i+1;j<numberOfInvalidRanges;j++)
        {
            if(angle[i][0]>angle[j][0])
            {
                double temp=angle[i][0];
                angle[i][0]=angle[j][0];
                angle[j][0]=temp;
                temp=angle[i][1];
                angle[i][1]=angle[j][1];
                angle[j][1]=temp;
            }
        }
    }
}

void TacticAttacker::findValidRanges()
{
    numberOfValidRanges=0;
    valid_angle[numberOfValidRanges][0]=dGoal;

    for(int i=0;i<numberOfInvalidRanges+1;i++)
    {
        valid_angle[numberOfValidRanges][1]=angle[i][0];
        valid_angle[numberOfValidRanges+1][0]=angle[i][1];
        numberOfValidRanges++;
    }

    valid_angle[numberOfValidRanges-1][1]=uGoal;
}

RobotCommand TacticAttacker::goBehindBall()
{
    RobotCommand rc;
    canKick=false;

    rc.maxSpeed = 2;

    float deg=atan((0-wm->ball.pos.loc.y)/(3025-wm->ball.pos.loc.x));

    if(!wm->kn->ReachedToPos(wm->ourRobot[id].pos, rc.fin_pos, 30, 180))
    {
        rc.fin_pos.loc= {wm->ball.pos.loc.x-110*cos(deg),wm->ball.pos.loc.y-110*sin(deg)};
        rc.fin_pos.dir=atan((0-wm->ball.pos.loc.y)/(3025-wm->ball.pos.loc.x));
    }


    if(!wm->kn->ReachedToPos(wm->ourRobot[id].pos, rc.fin_pos, 20, 2))
    {
        double test=findBestPoint();
        rc.fin_pos.dir=test;
    }
    rc.fin_pos.loc= {wm->ball.pos.loc.x-100*cos(deg),wm->ball.pos.loc.y-100*sin(deg)};

    if(wm->kn->ReachedToPos(wm->ourRobot[id].pos, rc.fin_pos, 10, 4))
    {
        canKick=true;
    }

    return rc;
}

double TacticAttacker::findBestPoint()
{
    findCriticalPlayer();
    findInvalidRanges();
    sortInvalidRanges();
    findValidRanges();
    double maxLength=0;
    int index=-1;
    for(int i=0;i<numberOfValidRanges;i++)
    {
        if(maxLength<valid_angle[i][1]-valid_angle[i][0])
        {
            index=i;
            maxLength=valid_angle[i][1]-valid_angle[i][0];
        }
    }

    return (valid_angle[index][0]+valid_angle[index][1])/2;
}

int TacticAttacker::findBestPlayerForPass()
{
    int index = -1;
    double min = 10000;

    QList<int> ourAgents = wm->kn->ActiveAgents();
    QList<int> freeAgents;

    while( !ourAgents.isEmpty() )
    {
        int index = ourAgents.takeFirst();
        if(isFree(index))
            freeAgents.append(index);
   }

    while ( !freeAgents.isEmpty() )
    {
        int i = freeAgents.takeFirst();
        if(wm->ourRobot[i].isValid && this->id != i && i != wm->ref_goalie_our)
        {
            if(wm->ball.pos.loc.dist(wm->ourRobot[i].pos.loc) < min)
            {
                min = wm->ourRobot[id].pos.loc.dist(wm->ourRobot[i].pos.loc);
                index = i;
            }
        }
    }
    //qDebug()<<"Pass Receiver is "<<index;
    return index;
}

bool TacticAttacker::isFree(int index)
{
    QList<int> oppAgents = wm->kn->ActiveOppAgents();
    bool isFree = true;

    while( !oppAgents.isEmpty() )
    {
        int indexOPP = oppAgents.takeFirst();
        if( (wm->ourRobot[index].pos.loc-wm->oppRobot[indexOPP].pos.loc).length() < DangerDist)
        {
            isFree = false;
        }

        if(!isFree)
            break;
    }
    return isFree;
}

void TacticAttacker::timerEvent()
{
    kicker_timer->stop();
    if(kicker_firstKick)
    {
        if( (wm->ball.pos.loc-wm->ourRobot[id].pos.loc).length() > 200 )
        {
            kicker_kicked = true;
        }
        else
        {
            kicker_firstKick = false;
        }
    }
}
