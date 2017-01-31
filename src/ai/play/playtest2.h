#ifndef PLAYTEST2_H
#define PLAYTEST2_H

#include "play.h"
#include "QDebug"
<<<<<<< HEAD
#include "tactic/tactichalt.h"
=======
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
>>>>>>> 4bde963eede2897a0748e0221474ee6c1450efde

class PlayTest2 : public Play
{
    Q_OBJECT
public:
    explicit PlayTest2(WorldModel *worldmodel, QObject *parent = 0);
    virtual void execute();
    virtual void initRole();
    virtual int enterCondition();

private:
    TacticTest2* tTest;
    virtual void initRole();
    TacticTest2* tTest;
    int Parabola_intersection (Vector2D, Vector2D, double, Vector2D *, Vector2D *);
};

#endif // PLAYTEST2_H
