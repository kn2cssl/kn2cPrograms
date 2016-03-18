#include "man2man.h"

Marking::Marking()
{
    maxDistance = sqrt(pow(Field::MaxX*2,2)+pow(Field::MaxY*2,2));
}

QList<Marking_Struct> Marking::findMarking(QList<int> our, QList<int> opp, bool &isMatched)
{
    QList<int> ourPlayers = our;
    QList<int> oppPlayers = opp;

    while ( oppPlayers.size() < ourPlayers.size() )
    {
        ourPlayers.removeFirst();
    }

    QList<double> F2 = distanceToGoal(oppPlayers);
    QList<double> F3 = oppScoringChance(oppPlayers);
    // QList<double> F5 = distanceToBall(oppPlayers);

    QList<int> dangerousOpposite;
    for(int i=0; i < oppPlayers.size(); i++)
    {
        if( F3.at(i) > DangerousProb || wm->kn->IsInsideOurField(wm->oppRobot[oppPlayers.at(i)].pos.loc) )
            dangerousOpposite.append(oppPlayers.at(i));
    }

    if( dangerousOpposite.size() > ourPlayers.size() )
    {
        if( (wm->ball.pos.loc - Field::ourGoalPost_L).length2() <  (wm->ball.pos.loc - Field::ourGoalPost_R).length2() )
            ourPlayers.append(wm->kn->findOurRightDefender());
        else
            ourPlayers.append(wm->kn->findOurLeftDefender());
    }


    QList<int> weights;
    for(int i=0;i<ourPlayers.size();i++)
    {
        for(int j=0;j<oppPlayers.size();j++)
        {
            double Distance =((wm->ourRobot[ourPlayers.at(i)].pos.loc -
                              wm->oppRobot[oppPlayers.at(j)].pos.loc).length() / (maxDistance*2));
            double F4 = formationDistance(ourPlayers.at(i));
            int weight = (int)( (wm->mark_coef[1]*(1-Distance)) + (wm->mark_coef[2]*(1-F2.at(j)))
                    + (wm->mark_coef[3]*(F3.at(j)))
                    + (wm->mark_coef[4]*F4) );

            //            qDebug()<<"-----"<<ourPlayers.at(i)<<" , "<<oppPlayers.at(j)<<"----";
            //            qDebug()<<"F1 : "<< (wm->mark_coef[1]*(1-Distance));
            //            qDebug()<<"F2 : "<< (wm->mark_coef[2]*(1-F2.at(j)));
            //            qDebug()<<"F3 : "<< (wm->mark_coef[3]*(F3.at(j)));
            //            qDebug()<<"F4 : "<< (wm->mark_coef[4]*F4);

            weights.append(weight);
        }
    }

    MWBM maximum_matching;
    QList<int> matching = maximum_matching.run(weights,ourPlayers.size(),oppPlayers.size(),isMatched);

    QList<Marking_Struct> out;

    if(isMatched)
    {
        for(int i=0;i<ourPlayers.size();i++)
        {
            Marking_Struct tmp;
            tmp.ourI = ourPlayers.at(i);
            tmp.oppI = oppPlayers.at(matching.at(i) - ourPlayers.size());
            out.append(tmp);
        }
    }

    return out;
}

void Marking::setWorldModel(WorldModel *wm)
{
    this->wm = wm;
}

QList<double> Marking::distanceToBall(QList<int> opp)
{
    QList<double> out;

    for(int i=0;i<opp.size();i++)
    {
        if( opp.at(i) < 0)
            out.append(0);
        else
            out.append((wm->ball.pos.loc - wm->oppRobot[opp.at(i)].pos.loc).length() / maxDistance);
    }

    return out;
}

QList<double> Marking::distanceToGoal(QList<int> opp)
{
    QList<double> out;

    for(int i=0;i<opp.size();i++)
    {
        if( opp.at(i) < 0)
            out.append(0);
        else
            out.append((Field::ourGoalCenter - wm->oppRobot[opp.at(i)].pos.loc).length() / maxDistance);
    }

    return out;
}

double Marking::formationDistance(int our)
{
    if( wm->ourRobot[our].Role == AgentRole::DefenderMid   ||
            wm->ourRobot[our].Role == AgentRole::DefenderRight ||
            wm->ourRobot[our].Role == AgentRole::DefenderLeft
            )
    {
        return 1;
    }
    return 2;
}

QList<double> Marking::oppScoringChance(QList<int> opp)
{
    QList<double> out;

    for(int i=0;i<opp.size();i++)
    {
        double chance = wm->kn->oppScoringChance(wm->oppRobot[opp.at(i)].pos.loc) / 100.0;
        out.append(chance);
    }

    return out;
}
