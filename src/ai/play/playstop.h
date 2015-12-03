#ifndef PLAYSTOP_H
#define PLAYSTOP_H

#include "play.h"
#include "positioning.h"
#include "QDebug"

class PlayStop : public Play
{
    Q_OBJECT
public:
    explicit PlayStop(WorldModel *worldmodel, QObject *parent = 0);
    virtual void execute();
    //virtual Tactic* getTactic(int id);
    virtual int enterCondition();
    bool collisionwithDefenders(Vector2D center,Vector2D left,Vector2D right);
    bool oneOfDefendersIsInPenalty(Vector2D leftPos, Vector2D midPos, Vector2D rightPos);

private:
    TacticGoalie*   tGolie;
    TacticDefender* tDefenderLeft;
    TacticDefender* tDefenderRight;
    TacticStop* tStopMid;
    TacticStop* tStopLeft;
    TacticStop* tStopRight;

    virtual void initRole();
    void setTactics(int index);
    void setPositions();
    QList<Vector2D> generatePositions();
};

#endif // PLAYSTOP_H
