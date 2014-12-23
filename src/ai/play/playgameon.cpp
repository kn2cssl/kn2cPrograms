#include "playgameon.h"

PlayGameOn::PlayGameOn(WorldModel *worldmodel, QObject *parent) :
    Play("PlayGameOn", worldmodel, parent)
{
    //    firstTimeInit = false; // Should Checked!!!!!

    //    freeKickStart = false;// Should Checked!!!!!

    //    numberOfPlayer = 0;// Should Checked!!!!!

    tGolie = new TacticGoalie(wm);

    //    numberOfDef = NUMOFDEFENDERS; // Should Checked!!!!!
    tDefenderLeft = new TacticDefender(wm);
    tDefenderRight = new TacticDefender(wm);
    tDefenderMid = new TacticDefender(wm);

    tAttackerLeft = new TacticAttacker(wm);
    tAttackerMid = new TacticAttacker(wm);
    tAttackerRight = new TacticAttacker(wm);
}

int PlayGameOn::enterCondition()
{
    if( wm->cmgs.gameOn() )
        return 100;
    else
        return 0;
    return 0;
    //    return 20000;
}

void PlayGameOn::setTactics(int index)
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
    }

    if(wm->ourRobot[index].Status == AgentStatus::RecievingPass)
    {
        wm->ourRobot[index].Status = AgentStatus::FollowingBall;
    }
    else if(wm->ourRobot[index].Status == AgentStatus::Kicking)
    {
        wm->ourRobot[index].Status = AgentStatus::Idle;
    }
    //    {
    //        wm->ourRobot[index].Status = AgentStatus::Idle;
    //    }
}

void PlayGameOn::initPressing()
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
}

void PlayGameOn::initRole()
{
    if( wm->gs_last == STATE_Free_kick_Our || wm->gs_last == STATE_Indirect_Free_kick_Our )
    {
        //return ;
    }
    else if( wm->gs_last == STATE_Free_kick_Opp || wm->gs_last == STATE_Indirect_Free_kick_Opp )
    {
        initPressing();
    }
    else if( wm->gs == STATE_Start)
    {

        QList<int> nearestPlayers2Ball = wm->kn->findNearestTo(wm->ball.pos.loc);
        QList<int> ourRobots_temp = wm->kn->ActiveAgents();

        if( (wm->ourRobot[nearestPlayers2Ball.at(0)].pos.loc-wm->ball.pos.loc).length() < 300)
        {
            wm->ourRobot[nearestPlayers2Ball.at(0)].Status = AgentStatus::FollowingBall;
            ourRobots_temp.removeOne(nearestPlayers2Ball.takeFirst());
            while( !ourRobots_temp.isEmpty() )
            {
                wm->ourRobot[ourRobots_temp.takeFirst()].Status = AgentStatus::Idle;
            }
        }
        else
        {
            Ray2D ballRay(wm->ball.pos.loc,wm->ball.vel.loc.dir());

            QList<int> ourRobots;

            for(int i=0;i<ourRobots_temp.size();i++)
            {
                if(ballRay.inRightDir(wm->ourRobot[ourRobots_temp.at(i)].pos.loc,90))
                {
                    ourRobots.append(ourRobots_temp.at(i));
                }
                else
                {
                    wm->ourRobot[ourRobots_temp.at(i)].Status = AgentStatus::Idle;
                }
            }

            int min_i = -1;
            double min_p = 5000;
            for(int i=0;i<ourRobots.size();i++)
            {
                if( ballRay.line().dist(wm->ourRobot[ourRobots.at(i)].pos.loc) < min_p)
                {
                    min_i = ourRobots.at(i);
                    min_p = ballRay.line().dist(wm->ourRobot[ourRobots.at(i)].pos.loc);
                }
            }

            if(min_i != -1)
            {
                wm->ourRobot[min_i].Status = AgentStatus::FollowingBall;
                ourRobots.removeOne(min_i);
            }

            while( !ourRobots.isEmpty() )
                wm->ourRobot[ourRobots.takeFirst()].Status = AgentStatus::Idle;
        }
    }
}

void PlayGameOn::execute()
{
    QList<int> activeAgents = wm->kn->ActiveAgents();

    //just for some tests-----------------------------------
    //    QList<int> activeAgents2 = wm->kn->ActiveAgents();

    //    wm->ourRobot[wm->ref_goalie_our].Role = AgentRole::Golie;
    //    activeAgents2.removeOne(wm->ref_goalie_our);

    //    wm->ourRobot[activeAgents2.takeFirst()].Role = AgentRole::DefenderLeft;
    //    wm->ourRobot[activeAgents2.takeFirst()].Role = AgentRole::DefenderRight;

    //    wm->ourRobot[activeAgents2.takeFirst()].Role = AgentRole::AttackerLeft;
    //    wm->ourRobot[activeAgents2.takeFirst()].Role = AgentRole::AttackerMid;
    //    wm->ourRobot[activeAgents2.takeFirst()].Role = AgentRole::AttackerRight;
    //-------------------------------------------------

    initRole();

    while( activeAgents.size() > 0 )
    {
        setTactics(activeAgents.takeFirst());
    }
}
