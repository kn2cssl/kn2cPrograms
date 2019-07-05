#ifndef FREEKICKTEST1_H
#define FREEKICKTEST1_H

#include "freekick_base.h"

class freekicktest1 : public freeKick_base
{
public:
    explicit freekicktest1(WorldModel *worldmodel, QObject *parent = 0);
    virtual void execute();
    virtual int enterCondition(Level level);
    virtual void resetValues();

private:
    void setPositions();
    bool checkDistances();

    int recieverID;
    Position rightPos, leftPos;
};

#endif // FREEKICKTEST1_H
