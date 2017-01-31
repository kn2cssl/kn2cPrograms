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
<<<<<<< HEAD

    int Parabola_intersection (Vector2D, Vector2D, double, Vector2D *, Vector2D *);

private:
<<<<<<< HEAD
    TacticTest2* tTest;
    virtual void initRole();
=======
    TacticTest2 *tTest1;

>>>>>>> 5aee4ed9254def077fb748ede91039b2d492a21c
=======

    int Parabola_intersection (Vector2D, Vector2D, double, Vector2D *, Vector2D *);

private:
    TacticTest2 *tTest1;

>>>>>>> 5aee4ed9254def077fb748ede91039b2d492a21c
};

#endif // PLAYTEST2_H
