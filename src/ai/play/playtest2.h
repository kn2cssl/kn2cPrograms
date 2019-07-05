#ifndef PLAYTEST2_H
#define PLAYTEST2_H

#include "play.h"
#include "QDebug"
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

class PlayTest2 : public Play
{
    Q_OBJECT
public:
    explicit PlayTest2(WorldModel *worldmodel, QObject *parent = 0);
    virtual void execute();
    virtual void initRole();
    virtual int enterCondition();
    //virtual Tactic* getTactic(int id);
    int Parabola_intersection (Vector2D, Vector2D, double, Vector2D *, Vector2D *);

private:
    virtual void initRole();
    TacticTest2 *tTest1;
    int Parabola_intersection (Vector2D, Vector2D, double, Vector2D *, Vector2D *);
};

#endif // PLAYTEST2_H
