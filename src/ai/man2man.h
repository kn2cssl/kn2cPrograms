#ifndef Marking_H
#define Marking_H

#include "mwbm.h"
#include <QList>
#include "worldmodel.h"

#define DangerousProb 0.5

class Marking
{
    /*  Factors :
     *  F1 Distance Between Our Robots and Opposite Robot
     *  F2 Distance From opp robot to our goal
     *  F3 Opp Scoring Chance
     *  F4 Distance From Formation Position
     *  F5 Distance From Ball
     *
     *  */

public:
    Marking();
    QList<Marking_Struct> findMarking(QList<int> our, QList<int> opp, bool &isMatched);
    void setWorldModel(WorldModel *wm);
    QList<double> distanceToBall(QList<int> opp);
    QList<double> distanceToGoal(QList<int> opp);
    double formationDistance(int our);
    QList<double> oppScoringChance(QList<int> opp);
private:
    WorldModel *wm;
    double maxDistance;
    int forwardedDefenderID;
};

#endif // Marking_H



