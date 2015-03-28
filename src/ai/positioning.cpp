#include "positioning.h"

Positioning::Positioning()
{
    staticIsFinished = false;
    maxDistance = sqrt(pow(Field::MaxX*2,2)+pow(Field::MaxY*2,2));
}

QList<Positioning_Struct> Positioning::find_positions(QList<int> ours, bool &isMatched)
{
    staticIsFinished = false;

    QList<Vector2D> static_points;

    static_points.append(Field::oppGoalPost_L);
    static_points.append(Field::oppGoalPost_R);

    static_points.append(Field::upperRightCorner);
    static_points.append(Field::bottomRightCorner);

    static_points.append(Vector2D(0,0));
    static_points.append(Vector2D(0,Field::MaxY));
    static_points.append(Vector2D(0,Field::MinY));

    QList<Vector2D> opp_pos;
    QList<int> opp = wm->kn->ActiveOppAgents();

    for(int i=0;i<opp.size();i++)
        opp_pos.append(wm->oppRobot[opp.at(i)].pos.loc);

    QList<Vector2D> candiates;
    while( candiates.size() < ours.size() )
    {
        if( !staticIsFinished )
        {
            candiates.clear();

            Voronoi_Diagram VD;
            VD.setWorldModel(wm);
            candiates = VD.calculate(opp_pos);
        }
        else
        {
            candiates.push_back(Vector2D(0,0.8*Field::MaxY));
            candiates.push_back(Vector2D(0,0.8*Field::MinY));
            candiates.push_back(Vector2D(0.6*Field::MaxX,0.8*Field::MaxY));
            candiates.push_back(Vector2D(0.6*Field::MaxX,0.8*Field::MinY));
        }

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
                if((candiates.at(i) - candiates.at(j)).length() < 500 )
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

        double m1 = (wm->ball.pos.loc.y - Field::oppGoalPost_L.y) / (wm->ball.pos.loc.x - Field::oppGoalPost_L.x);
        double m2 = (wm->ball.pos.loc.y - Field::oppGoalPost_R.y) / (wm->ball.pos.loc.x - Field::oppGoalPost_R.x);

        double tetha1 = atan(m1);
        double tetha2 = atan(m2);

        double dy1 = (ROBOT_RADIUS+30.0) / cos(tetha1);
        double dy2 = (ROBOT_RADIUS+30.0) / cos(tetha2);

        Vector2D p1 = Vector2D(Field::oppGoalPost_L.x,Field::oppGoalPost_L.y+dy1);
        Vector2D p2 = Vector2D(Field::oppGoalPost_R.x,Field::oppGoalPost_R.y-dy2);

        Line2D l1(p1,AngleDeg::rad2deg(tetha1));
        Line2D l2(p2,AngleDeg::rad2deg(tetha2));

        Vector2D p3 = l1.intersection(l2);

        Triangle2D criticalTri(p1 , p2 , p3);

        wm->selected.clear();
        wm->selected.append(p1);
        wm->selected.append(p2);
        wm->selected.append(p3);

        numberOfPoints = 0;
        while( numberOfPoints < candiates.size() )
        {
            if( criticalTri.contains(candiates.at(numberOfPoints)) )
                candiates.removeAt(numberOfPoints);
            else
                numberOfPoints++;
        }

        numberOfPoints = 0;
        while( numberOfPoints < candiates.size() )
        {
            if( wm->kn->IsNearOurGoal(candiates.at(numberOfPoints)) )
                candiates.removeAt(numberOfPoints);
            else
                numberOfPoints++;
        }


        if( candiates.size() < ours.size() && !static_points.isEmpty() )
            opp_pos.push_back(static_points.takeFirst());
        else
        {
            if( static_points.isEmpty() )
                staticIsFinished = true;
        }
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

QList<Positioning_Struct> Positioning::kickPositions(QList<int> ours, Vector2D target, bool &isMatched)
{
    staticIsFinished = false;

    QList<Vector2D> static_points;

    static_points.append(Field::oppGoalPost_L);
    static_points.append(Field::oppGoalPost_R);

    static_points.append(Field::upperRightCorner);
    static_points.append(Field::bottomRightCorner);

    static_points.append(Vector2D(0,0));
    static_points.append(Vector2D(0,Field::MaxY));
    static_points.append(Vector2D(0,Field::MinY));

    QList<Vector2D> opp_pos;
    QList<int> opp = wm->kn->ActiveOppAgents();

    for(int i=0;i<opp.size();i++)
        opp_pos.append(wm->oppRobot[opp.at(i)].pos.loc);

    QList<Vector2D> candiates;
    while( candiates.size() < ours.size() )
    {
        if( !staticIsFinished )
        {
            candiates.clear();

            Voronoi_Diagram VD;
            VD.setWorldModel(wm);
            candiates = VD.calculate(opp_pos);
        }
        else
        {
            candiates.push_back(Vector2D(0,0.8*Field::MaxY));
            candiates.push_back(Vector2D(0,0.8*Field::MinY));
            candiates.push_back(Vector2D(0.6*Field::MaxX,0.8*Field::MaxY));
            candiates.push_back(Vector2D(0.6*Field::MaxX,0.8*Field::MinY));
        }

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

        double m1 = (target.y - Field::oppGoalPost_L.y) / (target.x - Field::oppGoalPost_L.x);
        double m2 = (target.y - Field::oppGoalPost_R.y) / (target.x - Field::oppGoalPost_R.x);

        double tetha1 = atan(m1);
        double tetha2 = atan(m2);

        double dy1 = (ROBOT_RADIUS+30.0) / cos(tetha1);
        double dy2 = (ROBOT_RADIUS+30.0) / cos(tetha2);

        Vector2D p1 = Vector2D(Field::oppGoalPost_L.x,Field::oppGoalPost_L.y+dy1);
        Vector2D p2 = Vector2D(Field::oppGoalPost_R.x,Field::oppGoalPost_R.y-dy2);

        Line2D l1(p1,AngleDeg::rad2deg(tetha1));
        Line2D l2(p2,AngleDeg::rad2deg(tetha2));

        Vector2D p3 = l1.intersection(l2);

        Triangle2D criticalTri(p1 , p2 , p3);

        wm->selected.clear();
        wm->selected.append(p1);
        wm->selected.append(p2);
        wm->selected.append(p3);

        numberOfPoints = 0;
        while( numberOfPoints < candiates.size() )
        {
            if( criticalTri.contains(candiates.at(numberOfPoints)) )
                candiates.removeAt(numberOfPoints);
            else
                numberOfPoints++;
        }

        numberOfPoints = 0;
        while( numberOfPoints < candiates.size() )
        {
            if( wm->kn->IsNearOurGoal(candiates.at(numberOfPoints)) )
                candiates.removeAt(numberOfPoints);
            else
                numberOfPoints++;
        }

        numberOfPoints = 0;
        while( numberOfPoints < candiates.size() )
        {
            if( wm->kn->IsInsideSecureArea(candiates.at(numberOfPoints), wm->ball.pos.loc) )
                candiates.removeAt(numberOfPoints);
            else
                numberOfPoints++;
        }

        if( candiates.size() < ours.size() && !static_points.isEmpty() )
            opp_pos.push_back(static_points.takeFirst());
        else
        {
            if( static_points.isEmpty() )
                staticIsFinished = true;
        }
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
