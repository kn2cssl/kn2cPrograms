#include "playfreekickopp.h"

PlayFreeKickOpp::PlayFreeKickOpp(WorldModel *worldmodel, QObject *parent) :
    Play("PlayFreeKickOpp", worldmodel, parent)
{
    numberOfPlayers = 0;

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

            waitTimer->start(500);
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
}

void PlayFreeKickOpp::pressing()
{
    QList<int> oppPlayers = wm->kn->ActiveOppAgents();
    oppPlayers.removeOne(wm->ref_goalie_opp);

    QList<int> ourPlayers = wm->kn->findAttackers();

    for(int i=0;i<oppPlayers.size();i++)
    {
        if( wm->kn->IsInsideSecureArea(wm->oppRobot[oppPlayers.at(i)].pos.loc,wm->ball.pos.loc) )
            oppPlayers.removeAt(i);
    }

    Marking defence;
    defence.setWorldModel(wm);
    bool isMatched;
    QList<Marking_Struct> m2m = defence.findMarking(ourPlayers,oppPlayers,isMatched);
    if( isMatched )
    {
        for(int i=0;i<m2m.size();i++)
        {
            setPlayer2Keep(m2m.at(i).ourI,m2m.at(i).oppI);
            ourPlayers.removeOne(m2m.at(i).ourI);
        }
    }

    while ( ourPlayers.size() > 0 )
    {
        wm->ourRobot[ourPlayers.takeFirst()].Status = AgentStatus::Idle;
    }

    wm->marking = m2m;

    if( wm->cmgs.theirDirectKick() )
    {
        wm->ourRobot[tDefenderLeft->getID()].Status = AgentStatus::BlockingBall;
        wm->ourRobot[tDefenderMid->getID()].Status = AgentStatus::BlockingBall;
        wm->ourRobot[tDefenderRight->getID()].Status = AgentStatus::BlockingBall;
    }
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

    TacticAttacker* atck;
    Position pos;

    switch (wm->ourRobot[index].Role) {
    case AgentRole::AttackerMid:
        atck = tAttackerMid;
        finalPos.x=wm->ball.pos.loc.x-ALLOW_NEAR_BALL_RANGE*cos(alfa);
        finalPos.y=wm->ball.pos.loc.y+ALLOW_NEAR_BALL_RANGE*sin(alfa);
        pos.loc = finalPos;
        pos.dir = (wm->ball.pos.loc - finalPos).dir().radian();
        atck->setIdlePosition(pos);
        break;
    case AgentRole::AttackerRight:
        atck = tAttackerRight;
        alfa+=AngleDeg::PI/10;
        finalPos.x=wm->ball.pos.loc.x-ALLOW_NEAR_BALL_RANGE*cos(alfa);
        finalPos.y=wm->ball.pos.loc.y+ALLOW_NEAR_BALL_RANGE*sin(alfa);
        pos.loc = finalPos;
        pos.dir = (wm->ball.pos.loc - finalPos).dir().radian();
        atck->setIdlePosition(pos);
        break;
    case AgentRole::AttackerLeft:
        atck = tAttackerLeft;
        alfa-=AngleDeg::PI/10;
        finalPos.x=wm->ball.pos.loc.x-ALLOW_NEAR_BALL_RANGE*cos(alfa);
        finalPos.y=wm->ball.pos.loc.y+ALLOW_NEAR_BALL_RANGE*sin(alfa);
        pos.loc = finalPos;
        pos.dir = (wm->ball.pos.loc - finalPos).dir().radian();
        atck->setIdlePosition(pos);
        break;
    default:
        break;
    }
}

void PlayFreeKickOpp::setPlayer2Keep(int ourR, int oppR)
{
    wm->ourRobot[ourR].Status = AgentStatus::BlockingRobot;

    switch (wm->ourRobot[ourR].Role)
    {
    case AgentRole::AttackerMid:
        tAttackerMid->setPlayerToKeep(oppR);
        break;
    case AgentRole::AttackerRight:
        tAttackerRight->setPlayerToKeep(oppR);
        break;
    case AgentRole::AttackerLeft:
        tAttackerLeft->setPlayerToKeep(oppR);
        break;
    default:
        break;
    }
}
void PlayFreeKickOpp::execute()
{
    if(go2ThePositions)
    {
        QList<int> activeAgents=wm->kn->ActiveAgents();

        if( !rolesIsInit )
            initRole();
        else
            pressing();

        for(int i=0;i<activeAgents.size();i++)
        {
            setTactics(activeAgents.at(i));
            setPositions(activeAgents.at(i));
        }
    }
}
