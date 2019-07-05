#ifndef PLAYSTOP_H
#define PLAYSTOP_H

#include "play.h"
#include "QDebug"
#include "man2man.h"

class PlayStop : public Play
{
    Q_OBJECT
public:
    explicit PlayStop(WorldModel *worldmodel, QObject *parent = 0);
    virtual void execute();
    virtual int enterCondition();

    //virtual Tactic* getTactic(int id);
    //bool collisionwithDefenders(Vector2D center,Vector2D left,Vector2D right);
    //bool oneOfDefendersIsInPenalty(Vector2D leftPos, Vector2D midPos, Vector2D rightPos);

private:
    TacticGoalie *tGoalie;
    TacticDefender *tDefenderLeft;
    TacticDefender *tDefenderRight;
    TacticStop *tStopMid;
    TacticStop *tStopLeft;
    TacticStop *tStopRight;
    TacticAttacker *tAttackerLeft;
    TacticAttacker *tAttackerRight;

    virtual void initRole();
    void setTactics(int index);
    void setPositions();
};

#endif // PLAYSTOP_H
