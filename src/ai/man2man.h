#ifndef MAN2MAN_H
#define MAN2MAN_H

#include "mwbm.h"
#include <QList>
#include "worldmodel.h"

struct Man2Man_Struct
{
    int ourI;
    int oppI;
    int weight;
};

class Man2Man
{
    /*  Factors :
     *  F1 Distance Between Our Robots and Opposite Robot
     *  F2 Opp Scoring Chance
     *  F3 Distance From Ball
     *
     *  */

public:
    Man2Man();
    QList<Man2Man_Struct> findOpp(QList<int> our,QList<int> opp);
    void setWorldModel(WorldModel *wm);
    QList<int> distanceToBall(QList<int>opp);
    QList<int> oppScoringChance(QList<int>opp);
private:
    WorldModel *wm;
    double maxDistance;
};

#endif // MAN2MAN_H



