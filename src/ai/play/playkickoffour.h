#ifndef PLAYKICKOFFOUR_H
#define PLAYKICKOFFOUR_H

#include "play.h"

class PlayKickoffOur : public Play
{
    Q_OBJECT
public:
    explicit PlayKickoffOur(WorldModel *worldmodel, QObject *parent = 0);
    virtual void execute();
    //virtual Tactic* getTactic(int id);
    virtual int enterCondition();

private:
    int numberOfDef;
    TacticGoalie*   tGolie;
    TacticFixedPos* tFixedPosM;
    TacticFixedPos* tFixedPosL;
    TacticFixedPos* tFixedPosR;
    TacticDefender* tDefenderL;
    TacticDefender* tDefenderR;
    TacticDefender* tDefenderM;

    virtual void initRole();
};
#endif // PLAYKICKOFFOUR_H
