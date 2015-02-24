#include "man2man.h"

Marking::Marking()
{
    maxDistance = sqrt(pow(Field::MaxX*2,2)+pow(Field::MaxY*2,2));
}

QList<Marking_Struct> Marking::findMarking(QList<int> our, QList<int> opp, bool &isMatched)
{
    QList<int> ourPlayers = our;
    QList<int> oppPlayers = opp;

//    int graphSize = (ourPlayers.size() < oppPlayers.size() )? ourPlayers.size():oppPlayers.size();

//    if( graphSize == ourPlayers.size() )
//    {
//        QList<int> farest = wm->kn->findNearestOppositeTo(oppPlayers,Field::oppGoalCenter);
//        while (oppPlayers.size() != graphSize)
//        {
//            oppPlayers.removeOne(farest.at(0));
//        }
//    }
//    else
//    {
//        QList<int> ours = wm->kn->findNearestTo(ourPlayers,Field::ourGoalCenter);
//        while (ourPlayers.size() != graphSize)
//        {
//            ourPlayers.removeOne(ours.at(0));
//        }
//    }

    QList<double> F2 = distanceToGoal(oppPlayers);
    QList<double> F3 = oppScoringChance(oppPlayers);
    QList<double> F5 = distanceToBall(oppPlayers);

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

            weights.append(weight);
        }
    }

    QString ss;
    for(int i=0;i<weights.size();i++)
    {
        if( i%5 == 0)
            ss.append("\n");
        ss.append(QString::number(weights.at(i)));
        ss.append(" , ");
    }
    qDebug()<<ss;

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
        return 0;
    }
    return 2;
}

QList<double> Marking::oppScoringChance(QList<int> opp)
{
    QList<double> out;

    for(int i=0;i<opp.size();i++)
    {
        //        Ray2D goalRay()
        //        if( opp.at(i) < 0)
        out.append(0);
        //        else
        //            out.append((wm->ball.pos.loc - wm->oppRobot[opp.at(i)].pos.loc).length() / Field::MaxX);
    }

    return out;
}
