#ifndef FREEKICKTEST2_H
#define FREEKICKTEST2_H
#include"freekick_base.h"
class freeKickTest2 : public freeKick_base
{
public:
    explicit freeKickTest2(WorldModel *worldmodel, QObject *parent = 0);
    virtual void execute();
    virtual int enterCondition(Level level);
    virtual void resetValues();

private:
    void setPositions();
    bool checkDistances();
    int maxOppThreshold();
    int minOppThreshold();
    int recieverID;
    Position rightPos, leftPos;

};

#endif // FREEKICKTEST2_H
