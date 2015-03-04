#include "positioning.h"

Positioning::Positioning()
{
    maxDistance = sqrt(pow(Field::MaxX*2,2)+pow(Field::MaxY*2,2));
}

QList<Positioning_Struct> Positioning::find_positions(QList<int> ours, bool &isMatched)
{
    QList<Vector2D> static_points;

    static_points.append(Vector2D(0,0));
    static_points.append(Vector2D(0,Field::MaxY));
    static_points.append(Vector2D(0,Field::MinY));
    static_points.append(Field::upperRightCorner);
    static_points.append(Field::bottomRightCorner);
    static_points.append(Field::oppGoalPost_L);
    static_points.append(Field::oppGoalPost_R);

    QList<Vector2D> opp_pos;
    QList<int> opp = wm->kn->ActiveOppAgents();

    for(int i=0;i<opp.size();i++)
        opp_pos.append(wm->oppRobot[opp.at(i)].pos.loc);

    QList<Vector2D> candiates;
    while( candiates.size() < ours.size() )
    {
        candiates.clear();

        Voronoi_Diagram VD;
        VD.setWorldModel(wm);
        candiates = VD.calculate(opp_pos);

        int numberOfPoints = 0;
        while( numberOfPoints < candiates.size() )
        {
            if( wm->kn->IsInsideOppGolieArea(candiates.at(numberOfPoints)) )
                candiates.removeAt(numberOfPoints);
            else
                numberOfPoints++;
        }

        int i = 0;
        while ( i < candiates.size() )
        {
            int j = i+1;
            while ( j < candiates.size() )
            {
                if((candiates.at(i) - candiates.at(j)).length() < 100 )
                {
                    Vector2D tmp = (candiates.at(i) + candiates.at(j))/2;

                    candiates.removeAt(i);
                    candiates.removeAt(j-1);

                    candiates.insert(i,tmp);
                }
                else
                    j++;
            }
            i++;
        }

        Triangle2D criticalTri(wm->ball.pos.loc , Field::oppGoalPost_L , Field::oppGoalPost_R);

        numberOfPoints = 0;

        while( numberOfPoints < candiates.size() )
        {
            if( criticalTri.contains(candiates.at(numberOfPoints)) )
                candiates.removeAt(numberOfPoints);
            else
                numberOfPoints++;
        }

        if( candiates.size() < ours.size() )
            opp_pos.push_back(static_points.takeFirst());
    }

    QList<double> F2 = distance2OppGoal(candiates);
    QList<double> F3 = goalOpportunity(candiates);
    QList<double> F4 = distance2NearestOpp(candiates);

    QList<int> weights;
    for(int i=0;i<ours.size();i++)
    {
        for(int j=0;j<candiates.size();j++)
        {
            double distance = ( wm->ourRobot[ours.at(i)].pos.loc - candiates.at(j) ).length() / maxDistance;

            double f2;
            //            if( F2.at(j) < 0.1 )
            //                f2 = F2.at(j);
            //            else
            f2 = 1-F2.at(j);

            int tmp = (int)( (wm->pos_coef[1]* (1-distance)) + (wm->pos_coef[2]* f2 )
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

QList<Positioning_Struct> Positioning::kickPositions(QList<int> ours, bool &isMatched)
{

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
        double factor = wm->kn->scoringChance(candidates.at(i));
        //qDebug()<<"fac : "<<factor/100.0;
        out.append( factor /100.0 );
    }

    return out;
}

QList<double> Positioning::distance2NearestOpp(QList<Vector2D> candidates)
{
    QList<double> out;

    for( int i=0;i<candidates.size();i++)
    {
        QList<int> opp = wm->kn->findNearestOppositeTo(candidates.at(i));
        if( opp.size() > 0 )
            out.append( (candidates.at(i) - wm->oppRobot[opp.at(0)].pos.loc ).length() / maxDistance);
        else
            out.append(1);
    }

    return out;
}
