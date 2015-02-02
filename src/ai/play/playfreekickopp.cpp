#include "playfreekickopp.h"

PlayFreeKickOpp::PlayFreeKickOpp(WorldModel *worldmodel, QObject *parent) :
    Play("PlayFreeKickOpp", worldmodel, parent)
{
    numberOfPlayers = 0;

    pressingIsInit = false;
    rolesIsInit = false;
    go2ThePositions = false;

    waitTimer = new QTimer();
    connect(waitTimer,SIGNAL(timeout()),this,SLOT(waitTimer_timout()));

    tGolie = new TacticGoalie(wm);

    tDefenderLeft = new TacticDefender(wm);
    tDefenderRight = new TacticDefender(wm);
    tDefenderMid = new TacticDefender(wm);

    tAttackerLeft = new TacticAttacker(wm);
    tAttackerMid = new TacticAttacker(wm);
    tAttackerRight = new TacticAttacker(wm);
}

int PlayFreeKickOpp::enterCondition()
{
    if(wm->cmgs.theirFreeKick() || wm->cmgs.theirDirectKick())
    {
        if(wm->gs_last != wm->gs)
        {
            rolesIsInit = false;
            go2ThePositions = false;

            waitTimer->start(1000);
        }
        //        else
        //        {
        //            rolesIsInit = conditionChanged();
        //        }
        return 100;
    }
    else
    {
        return 0;
    }
    //        return 200000;
}

void PlayFreeKickOpp::waitTimer_timout()
{
    waitTimer->stop();
    go2ThePositions = true;
}

void PlayFreeKickOpp::initRole()
{
    QList<int> activeAgents=wm->kn->ActiveAgents();
    numberOfPlayers = activeAgents.size();
    activeAgents.removeOne(wm->ref_goalie_our);
    wm->ourRobot[wm->ref_goalie_our].Role = AgentRole::Golie;
    switch (activeAgents.length()) {
    case 1:
        wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::DefenderMid;
        break;
    case 2:
        wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::DefenderRight;
        wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::DefenderLeft;
        break;
    case 3:
        wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::DefenderRight;
        wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::DefenderLeft;
        wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::AttackerMid;
        break;
    case 4:
        wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::DefenderRight;
        wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::DefenderLeft;
        wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::AttackerMid;
        wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::AttackerLeft;
        break;
    case 5:
        switch (numberOfDef) {
        case 2:
            wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::DefenderRight;
            wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::DefenderLeft;
            wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::AttackerMid;
            wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::AttackerRight;
            wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::AttackerLeft;
            break;
        case 3:
            wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::DefenderRight;
            wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::DefenderLeft;
            wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::DefenderMid;
            wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::AttackerMid;
            wm->ourRobot[activeAgents.takeFirst()].Role = AgentRole::AttackerRight;
            break;
        }
        break;
    }
    rolesIsInit = true;
    pressingIsInit = false;
}

void PlayFreeKickOpp::initPressing()
{
    QList<int> oppAgents = wm->kn->ActiveOppAgents();
    oppAgents.removeOne(wm->ref_goalie_opp);

    for(int i=0;i<oppAgents.size();i++)
    {
        if( wm->kn->IsInsideSecureArea(wm->oppRobot[oppAgents.at(i)].pos.loc,wm->ball.pos.loc) )
        {
            oppAgents.removeAt(i);
        }
    }

    for(int i=0;i<oppAgents.size();i++)
    {
        for(int j=0;j<oppAgents.size();j++)
        {
            double distanceI = (wm->oppRobot[oppAgents.at(i)].pos.loc - Field::ourGoalCenter).length();
            double distanceJ = (wm->oppRobot[oppAgents.at(j)].pos.loc - Field::ourGoalCenter).length();
            if(distanceI > distanceJ)
                oppAgents.swap(i,j);
        }
    }

    if(!oppAgents.isEmpty())
    {
        tAttackerMid->setPlayerToKeep(oppAgents.takeLast());
        wm->ourRobot[tAttackerMid->getID()].Status = AgentStatus::BlockingRobot;
    }
    else
    {
        wm->ourRobot[tAttackerMid->getID()].Status = AgentStatus::Idle;
    }

    if(!oppAgents.isEmpty())
    {
        tAttackerLeft->setPlayerToKeep(oppAgents.takeLast());
        wm->ourRobot[tAttackerLeft->getID()].Status = AgentStatus::BlockingRobot;
    }
    else
    {
        wm->ourRobot[tAttackerLeft->getID()].Status = AgentStatus::Idle;
    }

    if(!oppAgents.isEmpty())
    {
        tAttackerRight->setPlayerToKeep(oppAgents.takeLast());
        wm->ourRobot[tAttackerRight->getID()].Status = AgentStatus::BlockingRobot;
    }
    else
    {
        wm->ourRobot[tAttackerRight->getID()].Status = AgentStatus::Idle;
    }

    if( wm->cmgs.theirDirectKick() && numberOfDef==2 )
    {
        if( wm->ourRobot[tDefenderRight->getID()].isValid )
            wm->ourRobot[tDefenderRight->getID()].Status = AgentStatus::BlockingBall;

        if( wm->ourRobot[tDefenderLeft->getID()].isValid )
            wm->ourRobot[tDefenderLeft->getID()].Status = AgentStatus::BlockingBall;
    }

    pressingIsInit = true;
}

void PlayFreeKickOpp::setTactics(int index)
{
    switch (wm->ourRobot[index].Role) {
    case AgentRole::Golie:
        tactics[index] = tGolie;
        break;
    case AgentRole::DefenderMid:
        tactics[index] = tDefenderMid;
        break;
    case AgentRole::DefenderLeft:
        tactics[index] = tDefenderLeft;
        break;
    case AgentRole::DefenderRight:
        tactics[index] = tDefenderRight;
        break;
    case AgentRole::AttackerMid:
        tactics[index] = tAttackerMid;
        break;
    case AgentRole::AttackerRight:
        tactics[index] = tAttackerRight;
        break;
    case AgentRole::AttackerLeft:
        tactics[index] = tAttackerLeft;
        break;
    default:
        break;
    }
}

void PlayFreeKickOpp::setPositions(int index)
{
    Vector2D finalPos;
    double m;
    double alfa;
    m=-(Field::ourGoalCenter.y-wm->ball.pos.loc.y)/(Field::ourGoalCenter.x-wm->ball.pos.loc.x);
    alfa=atan(m);

    if(alfa>75.0*3.14/180)
    {
        alfa=120.0*3.14/180;
    }

    if(alfa<-75.0*3.14/180)
    {
        alfa=-120.0*3.14/180;
    }

    TacticAttacker *atck;

    switch (wm->ourRobot[index].Role) {
    case AgentRole::AttackerMid:
        atck = tAttackerMid;
        break;
    case AgentRole::AttackerRight:
        atck = tAttackerRight;
        alfa+=AngleDeg::PI/10;
        break;
    case AgentRole::AttackerLeft:
        atck = tAttackerLeft;
        alfa-=AngleDeg::PI/10;
        break;
    default:
        break;
    }
    finalPos.x=wm->ball.pos.loc.x-ALLOW_NEAR_BALL_RANGE*cos(alfa);
    finalPos.y=wm->ball.pos.loc.y+ALLOW_NEAR_BALL_RANGE*sin(alfa);

    atck->setIdlePosition(finalPos);
}
void PlayFreeKickOpp::execute()
{
    if(go2ThePositions)
    {
        QList<int> activeAgents=wm->kn->ActiveAgents();

        if( rolesIsInit && !pressingIsInit )
            initPressing();

        if( !rolesIsInit )
            initRole();

        for(int i=0;i<activeAgents.size();i++)
        {
            setTactics(activeAgents.at(i));
            setPositions(activeAgents.at(i));
        }
    }

}
