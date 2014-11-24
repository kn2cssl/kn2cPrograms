#include "tactickicker.h"


TacticKicker::TacticKicker(WorldModel *worldmodel, QObject *parent) :
    Tactic("TacticKicker", worldmodel, parent)
{
    canKick = false;
    firstKick = false;
    kicked = false;
    timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(timerEvent()));
}

RobotCommand TacticKicker::getCommand()
{
    RobotCommand rc;
    if(!wm->ourRobot[id].isValid) return rc;

    rc.maxSpeed = 2;

    if(!kicked)
    {
        if(!firstKick)
        {
            rc = goBehindBall();

            if(wm->kn->CanKick(wm->ourRobot[id].pos,wm->ball.pos.loc))
            {
                timer->start(300);
                rc.kickspeedx = 2.5;//50;
                firstKick = true;
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
    return rc;
}

RobotCommand TacticKicker::goBehindBall()
{
    RobotCommand rc;
    canKick=false;

    rc.maxSpeed = 1;

    int index = findBestPlayerForPass();

    if(index != -1)
    {
        Vector2D target(wm->ourRobot[index].pos.loc.x,wm->ourRobot[index].pos.loc.y);
        Vector2D goal(target.x+500*cos(target.dir().DEG2RAD),target.y+500*sin(target.dir().DEG2RAD));
        rc.fin_pos = wm->kn->AdjustKickPoint(wm->ball.pos.loc,goal);
    }

    return rc;
}

int TacticKicker::findBestPlayerForPass()
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

void TacticKicker::setKickerID(int index)
{
    this->id = index;
}

bool TacticKicker::isFree(int index)
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

void TacticKicker::timerEvent()
{
    timer->stop();
    if(firstKick)
    {
        if( (wm->ball.pos.loc-wm->ourRobot[id].pos.loc).length() > 200 )
        {
            kicked = true;
        }
        else
        {
            firstKick = false;
        }
    }
}
