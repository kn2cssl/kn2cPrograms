#include "man2man.h"

Man2Man::Man2Man()
{
    maxDistance = sqrt(pow(Field::MaxX*2,2)+pow(Field::MaxY*2,2));
}

QList<Man2Man_Struct> Man2Man::findOpp(QList<int> our, QList<int> opp, bool &isMatched)
{
    QList<int> ourPlayers = our;
    QList<int> oppPlayers = opp;

    int graphSize = (ourPlayers.size() > oppPlayers.size() )? ourPlayers.size():oppPlayers.size();

    if( graphSize == ourPlayers.size() )
    {
        int redundant = -1;
        while (oppPlayers.size() != graphSize)
        {
            oppPlayers.append(redundant);
            redundant--;
        }
    }
    else
    {
        int redundant = -1;
        while (ourPlayers.size() != graphSize)
        {
            ourPlayers.append(redundant);
            redundant--;
        }
    }

    QList<int> F3 = distanceToBall(oppPlayers);
    QList<int> F2 = oppScoringChance(oppPlayers);

    QList<int> weights;
    for(int i=0;i<ourPlayers.size();i++)
    {
        for(int j=0;j<oppPlayers.size();j++)
        {
            int weight;
            double Distance =((wm->ourRobot[ourPlayers.at(i)].pos.loc -
                              wm->oppRobot[oppPlayers.at(j)].pos.loc).length() / maxDistance);

            if(ourPlayers.at(i) < 0
                    || wm->ourRobot[ourPlayers.at(i)].Role == AgentRole::DefenderMid
                    || wm->ourRobot[ourPlayers.at(i)].Role == AgentRole::DefenderLeft
                    || wm->ourRobot[ourPlayers.at(i)].Role == AgentRole::DefenderRight)
                weight = 0;
            else
                weight = int( (wm->var[6]*(1-Distance)) + (wm->var[7]*F2.at(j)) + (wm->var[8]*F3.at(j)));

            weights.append(weight);
        }
    }

    MWBM maximum_matching;
    QList<int> matching = maximum_matching.run(weights,graphSize,isMatched);

    QList<Man2Man_Struct> out;

    if(isMatched)
    {
        for(int i=0;i<graphSize;i++)
        {
            Man2Man_Struct tmp;
            tmp.ourI = ourPlayers.at(i);
            tmp.oppI = oppPlayers.at(matching.at(i)%graphSize);
            tmp.weight = weights.at((graphSize*i) + (matching.at(i)%graphSize));

            if( tmp.weight > 0)
                out.append(tmp);
        }
    }

    return out;
}

void Man2Man::setWorldModel(WorldModel *wm)
{
    this->wm = wm;
}

QList<int> Man2Man::distanceToBall(QList<int> opp)
{
    QList<int> out;

    for(int i=0;i<opp.size();i++)
    {
        //        if( opp.at(i) < 0)
        out.append(0);
        //        else
        //            out.append((wm->ball.pos.loc - wm->ourRobot[opp.at(i)].pos.loc).length() / Field::MaxX);
    }

    return out;
}

QList<int> Man2Man::oppScoringChance(QList<int> opp)
{
    QList<int> out;

    for(int i=0;i<opp.size();i++)
    {
        //        Ray2D goalRay()
        //        if( opp.at(i) < 0)
        out.append(0);
        //        else
        //            out.append((wm->ball.pos.loc - wm->ourRobot[opp.at(i)].pos.loc).length() / Field::MaxX);
    }

    return out;
}
