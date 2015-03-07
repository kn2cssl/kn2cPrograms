#ifndef POSITIONING_H
#define POSITIONING_H

#include "mwbm.h"
#include <QList>
#include "worldmodel.h"
#include <geom/voronoi_diagram.h>


class Positioning
{
    /*  Factors :
     *  F1 Distance From Current Position
     *  F2 Distance From opp goal
     *  F3 Our Scoring Chance
     *  F4 Distance Between the Point and Nearest Opposite Robot
     * */

public:
    Positioning();
    QList<Positioning_Struct> find_positions(QList<int> ours , bool &isMatched);
    QList<Positioning_Struct> kickPositions(QList<int> ours , bool &isMatched);
    void setWorldModel(WorldModel *wm);

private:
    QList<double> distance2OppGoal(QList<Vector2D> candidates);
    QList<double> goalOpportunity(QList<Vector2D> candidates);
    QList<double> distance2NearestOpp(QList<Vector2D> candidates);

    WorldModel *wm;
    double maxDistance;
    bool staticIsFinished;
};

#endif // POSITIONING_H
