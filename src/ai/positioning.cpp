#include "positioning.h"

Positioning::Positioning()
{
    maxDistance = sqrt(pow(Field::MaxX*2,2)+pow(Field::MaxY*2,2));
}

QList<Positioning_Struct> Positioning::find_positions(QList<int> ours, bool &isMatched)
{
    qDebug()<<"ours size : "<<ours.size();

    QList<Vector2D> static_points;
    static_points.append(Field::oppGoalCenter);
    static_points.append(Vector2D(0,0));
    static_points.append(Vector2D(0,Field::MaxY));
    static_points.append(Vector2D(0,Field::MinY));
    static_points.append(Field::upperRightCorner);
    static_points.append(Field::bottomRightCorner);

    QList<Vector2D> opp_pos;
    QList<int> opp = wm->kn->ActiveOppAgents();

    for(int i=0;i<opp.size();i++)
        opp_pos.append(wm->oppRobot[opp.at(i)].pos.loc);

    while ( opp.size() < 2*ours.size() )
    {
        opp_pos.append(static_points.takeFirst());
    }

    Voronoi_Diagram VD;
    VD.setWorldModel(wm);
    QList<Vector2D> candiates = VD.calculate(opp_pos);

    qDebug()<<"candiates size : "<<candiates.size();

    QList<double> F2 = distance2OppGoal(candiates);
    QList<double> F3 = goalOpportunity(candiates);
    QList<double> F4 = distance2NearestOpp(candiates);

    QList<int> weights;
    for(int i=0;i<ours.size();i++)
    {
        for(int j=0;j<candiates.size();j++)
        {
            double distance = ( wm->ourRobot[ours.at(i)].pos.loc - candiates.at(j) ).length() / maxDistance;
            int tmp = (int)( (wm->pos_coef[1]* (1-distance)) + (wm->pos_coef[2]* (1-F2.at(j)))
                    + (wm->pos_coef[3]* F3.at(j)) + (wm->pos_coef[4]* F4.at(j)) );
            weights.append( tmp );
        }
    }

    MWBM maximum_matching;
    QList<int> matching = maximum_matching.run(weights,ours.size(),candiates.size(),isMatched);

    QList<Positioning_Struct> out;

    if(isMatched)
    {
        for(int i=0;i<ours.size();i++)
        {
            Positioning_Struct tmp;
            if( ours.at(i) >=0  && (matching.at(i) - ours.size())>=0 )
            {
                tmp.ourI = ours.at(i);
                tmp.loc = candiates.at(matching.at(i) - ours.size());
                out.append(tmp);
            }
        }
    }

    return out;
}

void Positioning::setWorldModel(WorldModel *wm)
{
    this->wm = wm;
}

QList<double> Positioning::distance2OppGoal(QList<Vector2D> candidates)
{
    QList<double> out;

    for( int i=0;i<candidates.size();i++)
    {
        out.append( (candidates.at(i) - Field::oppGoalCenter).length() / maxDistance );
    }

    return out;
}

QList<double> Positioning::goalOpportunity(QList<Vector2D> candidates)
{
    QList<double> out;

    for( int i=0;i<candidates.size();i++)
    {
        out.append( 0 );
    }

    return out;
}

QList<double> Positioning::distance2NearestOpp(QList<Vector2D> candidates)
{
    QList<double> out;

    for( int i=0;i<candidates.size();i++)
    {
        QList<int> opp = wm->kn->findNearestOppositeTo(candidates.at(i));
        out.append( (candidates.at(i) - wm->oppRobot[opp.at(0)].pos.loc ).length() / maxDistance);
    }

    return out;
}
