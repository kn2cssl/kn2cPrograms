#ifndef PLAYFORMATIONS_H
#define PLAYFORMATIONS_H

#include "play.h"
#define TEAMLEADER 0
#define NUMOFFORMATION 4
#define FORMATIONTYPE 2

class PlayFormations : public Play
{
    Q_OBJECT
public:
    explicit PlayFormations(WorldModel *worldmodel, QObject *parent = 0);
    virtual void execute();
    //virtual Tactic* getTactic(int id);
    virtual int enterCondition();

protected:
    virtual void initRole();

private:
    TacticFormation* tFormation[NUMOFFORMATION];
    TacticTest* tTest;
    int firstCounter, secondCounter;
};

#endif // PLAYFORMATIONS_H
